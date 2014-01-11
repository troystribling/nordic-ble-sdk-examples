/*Copyright (c) 2013, Nordic Semiconductor ASA
 *All rights reserved.
 *
 *Redistribution and use in source and binary forms, with or without modification,
 *are permitted provided that the following conditions are met:
 *
 *  Redistributions of source code must retain the above copyright notice, this
 *  list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright notice, this
 *  list of conditions and the following disclaimer in the documentation and/or
 *  other materials provided with the distribution.
 *
 *  Neither the name of Nordic Semiconductor ASA nor the names of its
 *  contributors may be used to endorse or promote products derived from
 *  this software without specific prior written permission.
 *
 *THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 *ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * My project template
 */

/** @defgroup my_project my_project
@{
@ingroup projects
@brief Empty project that can be used as a template for new projects.

@details
This project is a firmware template for new projects. 
The project will run correctly in its current state, but does nothing. 
With this project you have a starting point for adding your own application functionality.

The following instructions describe the steps to be made on the Windows PC:

 -# Install the Master Control Panel on your computer. Connect the Master Emulator 
    (nRF2739) and make sure the hardware drivers are installed.
    
 */
#include <SPI.h>
#include <avr/pgmspace.h>
#undef PROGMEM
#define PROGMEM __attribute__(( section(".progmem.data") )) 

#include <ble_system.h>
#include <lib_aci.h>
#include <aci_setup.h>

/**
Put the nRF8001 setup in the RAM of the nRF8001.
*/
#include "services.h"
/**
Include the services_lock.h to put the setup in the OTP memory of the nRF8001.
This would mean that the setup cannot be changed once put in.
However this removes the need to do the setup of the nRF8001 on every reset.
*/


#ifdef SERVICES_PIPE_TYPE_MAPPING_CONTENT
    static services_pipe_type_mapping_t
        services_pipe_type_mapping[NUMBER_OF_PIPES] = SERVICES_PIPE_TYPE_MAPPING_CONTENT;
#else
    #define NUMBER_OF_PIPES 0
    static services_pipe_type_mapping_t * services_pipe_type_mapping = NULL;
#endif
static hal_aci_data_t setup_msgs[NB_SETUP_MESSAGES] PROGMEM = SETUP_MESSAGES_CONTENT;

//@todo have an aci_struct that will contain 
// total initial credits
// current credit
// current state of the aci (setup/standby/active/sleep)
// open remote pipe pending
// close remote pipe pending
// Current pipe available bitmap
// Current pipe closed bitmap
// Current connection interval, slave latency and link supervision timeout
// Current State of the the GATT client (Service Discovery)
// Status of the bond (R) Peer address
static struct aci_state_t aci_state;
static hal_aci_evt_t aci_data;
//static hal_aci_data_t aci_cmd;




void setup(void)
{ 
  Serial.begin(115200);
  Serial.println(F("Arduino setup"));
  
  /**
  Point ACI data structures to the the setup data that the nRFgo studio generated for the nRF8001
  */   
  if (NULL != services_pipe_type_mapping)
  {
    aci_state.aci_setup_info.services_pipe_type_mapping = &services_pipe_type_mapping[0];
  }
  else
  {
    aci_state.aci_setup_info.services_pipe_type_mapping = NULL;
  }
  aci_state.aci_setup_info.number_of_pipes    = NUMBER_OF_PIPES;
  aci_state.aci_setup_info.setup_msgs         = setup_msgs;
  aci_state.aci_setup_info.num_setup_msgs     = NB_SETUP_MESSAGES;
  
  /*
  Tell the ACI library, the MCU to nRF8001 pin connections.
  The Active pin is optional and can be marked UNUSED
  */	  	
  aci_state.aci_pins.board_name = REDBEARLAB_SHIELD_V1_1; //See board.h for details
  aci_state.aci_pins.reqn_pin   = 9;
  aci_state.aci_pins.rdyn_pin   = 8;
  aci_state.aci_pins.mosi_pin   = MOSI;
  aci_state.aci_pins.miso_pin   = MISO;
  aci_state.aci_pins.sck_pin    = SCK;

  aci_state.aci_pins.spi_clock_divider     = SPI_CLOCK_DIV8;
	  
  aci_state.aci_pins.reset_pin             = UNUSED;
  aci_state.aci_pins.active_pin            = UNUSED;
  aci_state.aci_pins.optional_chip_sel_pin = UNUSED;
	  
  aci_state.aci_pins.interface_is_interrupt	  = false;
  aci_state.aci_pins.interrupt_number	      = 1;

  /* We initialize the data structures required to setup the nRF8001
  */
  lib_aci_init(&aci_state);
  
  lib_aci_debug_print(true);
  
  /*
  The Bluetooth low energy Arduino shield v1.1 requires about 100ms to reset.
  This is not required for the nRF2740, nRF2741 modules
  */
  delay(100);
  
  /*
  Send the soft reset command to the nRF8001 to get the nRF8001 to a known state.
  */
  lib_aci_radio_reset();
  
  while (1)
  {
    /*Wait for the command response of the radio reset command.
    as the nRF8001 will be in either SETUP or STANDBY after the ACI Reset Radio is processed
	*/	
    if (true == lib_aci_event_get(&aci_state, &aci_data))
    {
      aci_evt_t * aci_evt;      
      aci_evt = &aci_data.evt;
	  
      if (ACI_EVT_CMD_RSP == aci_evt->evt_opcode)
      {
            if (ACI_STATUS_ERROR_DEVICE_STATE_INVALID == aci_evt->params.cmd_rsp.cmd_status) //in SETUP
            {
              Serial.println(F("Do setup"));
              if (ACI_STATUS_TRANSACTION_COMPLETE != do_aci_setup(&aci_state))
              {
                Serial.println(F("Error in ACI Setup"));
              }              
            }
            else if (ACI_STATUS_SUCCESS == aci_evt->params.cmd_rsp.cmd_status) //We are now in STANDBY
            {
              /*Looking for an phone by sending radio advertisements
              When an phone connects to us we will get an ACI_EVT_CONNECTED event from the nRF8001
			  */
              lib_aci_connect(180/* in seconds */, 0x0050 /* advertising interval 50ms*/);
              Serial.println(F("Advertising started"));              
            }
          break;
      }
      else
      {
        Serial.println(F("Discard any other ACI Events"));
      }
	  
    }
  }
}


void loop()
{
  // We enter the if statement only when there is a ACI event available to be processed
  if (lib_aci_event_get(&aci_state, &aci_data))
  {
    aci_evt_t * aci_evt;
    
    aci_evt = &aci_data.evt;    
    switch(aci_evt->evt_opcode)
    {
        /**
        As soon as you reset the nRF8001 you will get an ACI Device Started Event
        */
        case ACI_EVT_DEVICE_STARTED:
        {          
          aci_state.data_credit_available = aci_evt->params.device_started.credit_available;
          switch(aci_evt->params.device_started.device_mode)
          {
            case ACI_DEVICE_SETUP:
            /**
            When the device is in the setup mode
            */
            Serial.println(F("Evt Device Started: Setup"));
            if (ACI_STATUS_TRANSACTION_COMPLETE != do_aci_setup(&aci_state))
            {
              Serial.println(F("Error in ACI Setup"));
            }
            break;
            
            case ACI_DEVICE_STANDBY:
              Serial.println(F("Evt Device Started: Standby"));
              lib_aci_connect(180/* in seconds */, 0x0100 /* advertising interval 100ms*/);
              Serial.println(F("Advertising started"));
              break;
          }
        }
        break; //ACI Device Started Event
      case ACI_EVT_CMD_RSP:
        //If an ACI command response event comes with an error -> stop
        if (ACI_STATUS_SUCCESS != aci_evt->params.cmd_rsp.cmd_status)
        {
          //ACI ReadDynamicData and ACI WriteDynamicData will have status codes of
          //TRANSACTION_CONTINUE and TRANSACTION_COMPLETE
          //all other ACI commands will have status code of ACI_STATUS_SCUCCESS for a successful command
          Serial.print(F("ACI Command "));
          Serial.println(aci_evt->params.cmd_rsp.cmd_opcode, HEX);
          Serial.println(F("Evt Cmd respone: Error. Arduino is in an while(1); loop"));
          while (1);
        }
        break;
      case ACI_EVT_CONNECTED:
        Serial.println(F("Evt Connected"));
        break;
      case ACI_EVT_PIPE_STATUS:
        Serial.println(F("Evt Pipe Status"));
        break;
      case ACI_EVT_DISCONNECTED:
        Serial.println(F("Evt Disconnected/Advertising timed out"));
        lib_aci_connect(180/* in seconds */, 0x0100 /* advertising interval 100ms*/);
        Serial.println(F("Advertising started"));        
        break;
      case ACI_EVT_PIPE_ERROR:
        //See the appendix in the nRF8001 Product Specication for details on the error codes
        Serial.print(F("ACI Evt Pipe Error: Pipe #:"));
        Serial.print(aci_evt->params.pipe_error.pipe_number, DEC);
        Serial.print(F("  Pipe Error Code: 0x"));
        Serial.println(aci_evt->params.pipe_error.error_code, HEX);
                
        //Increment the credit available as the data packet was not sent.
        //The pipe error also represents the Attribute protocol Error Response sent from the peer and that should not be counted 
        //for the credit.
        if (ACI_STATUS_ERROR_PEER_ATT_ERROR != aci_evt->params.pipe_error.error_code)
        {
          aci_state.data_credit_available++;
        }
        break;        
      case ACI_EVT_DATA_RECEIVED:
        Serial.print(F("Pipe #: 0x"));
        Serial.print(aci_evt->params.data_received.rx_data.pipe_number, HEX);
        {
          int i=0;
          Serial.print(F(" Data(Hex) : "));
          for(i=0; i<aci_evt->len - 2; i++)
          {
            Serial.print(aci_evt->params.data_received.rx_data.aci_data[i], HEX);
            Serial.print(F(" "));
          }
        }
        Serial.println(F(""));
        break;      
    }
  }
  else
  {
    //Serial.println(F("No ACI Events available"));
    // No event in the ACI Event queue
    // Arduino can go to sleep now
    // Wakeup from sleep from the RDYN line
  }
}

