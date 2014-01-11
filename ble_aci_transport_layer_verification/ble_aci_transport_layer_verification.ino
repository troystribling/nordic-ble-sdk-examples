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
 * echo project to verify the SPI/ACI connectivity
 */

/** @defgroup my_project my_project
@{
@ingroup projects
@brief Echo project to loop data from the mcu to the nRF800 and back

@details
This project is a test project to verify the SPI/ACI.
The data in the ACI echo command send and the data
received in the ACI echo event should be the same.


 */

#define DEBUG_ENABLE CODED_TRACES
#include <SPI.h>
#include <avr/pgmspace.h>
#include <ble_system.h>
#include <lib_aci.h>

// aci_struct that will contain
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


static uint8_t echo_data[] = { 0x00, 0xaa, 0x55, 0xff, 0x77, 0x55, 0x33, 0x22, 0x11, 0x44, 0x66, 0x88, 0x99, 0xbb, 0xdd, 0xcc, 0x00, 0xaa, 0x55, 0xff };
static uint8_t aci_echo_cmd = 0;

#define NUM_ECHO_CMDS 3

void setup(void)
{
  Serial.begin(9600);
  Serial.println(F("Arduino setup"));

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

  hal_aci_tl_init(&(aci_state.aci_pins));
  Serial.println(F("nRF8001 Reset done"));
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
              Serial.println(F("Evt Device Started: Setup"));
              lib_aci_test(ACI_TEST_MODE_DTM_UART);
              break;
            case ACI_DEVICE_STANDBY:
              Serial.println(F("Evt Device Started: Standby"));
              break;
            case ACI_DEVICE_TEST:
            {
              uint8_t i = 0;
              Serial.println(F("Evt Device Started: Test"));
              Serial.println(F("Started infinite Echo test"));
              Serial.println(F("Repeat the test with all bytes in echo_data inverted."));
              Serial.println(F("Waiting 4 seconds before the test starts...."));
              delay(4000);
              for(i=0; i<NUM_ECHO_CMDS; i++)
              {
                lib_aci_echo_msg(sizeof(echo_data), &echo_data[0]);
                aci_echo_cmd++;
              }
            }
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
          Serial.print(F("ACI Command 0x"));
          Serial.println(aci_evt->params.cmd_rsp.cmd_opcode, HEX);
          Serial.println(F("Evt Cmd respone: Error. Arduino is in an while(1); loop"));
          while (1);
        }
        break;
      case ACI_EVT_ECHO:
        if (0 != memcmp(&echo_data[0], &(aci_evt->params.echo.echo_data[0]), sizeof(echo_data)))
        {
          Serial.println(F("Error: Echo loop test failed. Verify the SPI connectivity on the PCB."));
        }
        else
        {
          Serial.println(F("Echo OK"));
        }
        if (NUM_ECHO_CMDS == aci_echo_cmd)
        {
          uint8_t i = 0;
          aci_echo_cmd = 0;
          for(i=0; i<NUM_ECHO_CMDS; i++)
          {
            lib_aci_echo_msg(sizeof(echo_data), &echo_data[0]);
            aci_echo_cmd++;
          }
        }
        break;
   }
  }
  else
  {
    // No event in the ACI Event queue
    // Arduino can go to sleep now
    // Wakeup from sleep from the RDYN line
  }
}

