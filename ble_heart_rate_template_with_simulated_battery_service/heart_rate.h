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

/* Attention! 
*  To maintain compliance with Nordic Semiconductor ASA's Bluetooth profile 
*  qualification listings, this section of source code must not be modified.
*/

#ifndef heart_rate_H
#define heart_rate_H

/** @file heart_rate.h
 * @brief This file gives the API to the Heart Rate Sensor Service. 
 */
 
/** @defgroup heart_rate_service heart_rate_service
* @{
* @ingroup services
*  
* @brief heart_rate_service : heart_rate measurement structure and flags.
* 
*/

/** HEART RATE Maximum number of byte per packet.*/
#define HR_MAX_PAYLOAD 19


/** HEART RATE Flags */
/**HEART RATE FLAGS bit 0: Heart Rate Value Format bit, if 0 then Heart Rate on 8 bits; if 1 then Heart Rate on 16 bits.*/
#define HEART_RATE_FLAGS_MEAS_SIZE_BIT                           0x01     
/**HEART RATE FLAGS bit 1: Sensor Contact Status bit support.*/
#define HEART_RATE_FLAGS_T_SENSOR_CONTACT_STATUS                 0x02     
/**HEART RATE FLAGS bit 2: Sensor Contact Status bits.*/
#define HEART_RATE_FLAGS_T_SENSOR_CONTACT_SUPPORT                0x04     
/**HEART RATE FLAGS bit 3: Energy Expended Status bit.*/
#define HEART_RATE_FLAGS_ENERGY_EXPENDED_STATUS_BIT              0x08     
/**HEART RATE FLAGS bit 4: RR-Interval Support bit.*/
#define HEART_RATE_FLAGS_RR_INTERVAL_SUPPORT_BIT                 0x10     
/**HEART RATE FLAGS bit 5: RESERVED FOR FUTURE USE.*/
#define HEART_RATE_FLAGS_RESERVED2_BIT                           0x20     
/**HEART RATE FLAGS bit 6: RESERVED FOR FUTURE USE.*/
#define HEART_RATE_FLAGS_RESERVED3_BIT                           0x40     
/**HEART RATE FLAGS bit 7: RESERVED FOR FUTURE USE.*/
#define HEART_RATE_FLAGS_RESERVED4_BIT                           0x80     

/** Possible Heart Rate Control Point Opcodes */
typedef enum hrcp_op_codes_t{
  HRCP_OPCODE_NULL                     = 0x00, /**<Reserved for future use (Operator:N/A)*/
  HRCP_OPCODE_RESET_ENERY_EXPENDED     = 0x01  /**<Resets the value of the Energy Expended field in the Heart Rate Measurement characteristic to 0*/ 
} hrcp_op_codes_t;

/**Attribute Protocol Application Error codes*/
typedef enum
{
  HRCP_ERR_OK                          = 0x00, /**<No error in control point command.*/
  HRCP_ERR_CONTROL_POINT_NOT_SUPPORTED = 0x80  /**<The received Heart Rate Control Point value is not supported.*/
} hrcp_error_codes_t;

/** @brief Function to initialize heart_rate service.
 */
void heart_rate_init(void);

/** @brief Function to indicate that the sensor contact is supported.
 */
void heart_rate_set_support_contact_bit(void);

/** @brief Function to indicate that the sensor contact is NOT supported.
 */
void heart_rate_clear_support_contact_bit(void);

/** @brief Function to indicate skin contact.
 */
void heart_rate_set_contact_status_bit(void);

/** @brief Function to indicate NO skin contact.
 */
void heart_rate_clear_contact_status_bit(void);

/** @brief Function to send a heart rate measurement (8 bits).
 *  @param meas_hr Measured heart_rate to send.
 *  @return : True when the ACI command is successfully placed in the ACI command queue
  */
bool heart_rate_send_hr(uint8_t meas_hr);

/** @brief Function to send a heart rate measurement (16 bits).
 *  @param meas_hr Measured heart_rate to send.
 *  @return : True when the ACI command is successfully placed in the ACI command queue
 */
bool heart_rate_send_hr_16bits(uint16_t meas_hr);

/** @brief Function to send a heart rate measurement (8 bits) with expended energy.
 *  @param meas_hr Measured heart_rate to send.
 *  @param expended_energy Measured expended energy.
 *  @return : True when the ACI command is successfully placed in the ACI command queue
 */
bool heart_rate_send_hr_expended_energy(uint8_t meas_hr, uint16_t expended_energy, bool is_freshest_sample);

/** @brief Function to send a heart rate measurement (16 bits) with expended energy.
 *  @param meas_hr Measured heart_rate to send.
 *  @param expended_energy Measured expended energy.
 *  @return : True when the ACI command is successfully placed in the ACI command queue
 */
bool heart_rate_send_hr_16bits_expended_energy(uint16_t meas_hr, uint16_t expended_energy, bool is_freshest_sample);

/** @brief Function to send a heart rate measurement (8 bits) with rr_intervals
 *  @param meas_hr Measured heart_rate to send.
 *  @param p_rr_intervals Pointer to rr_intervals values.
 *  @param nb_intervals Number of rr_intervals.
 *  @return : True when the ACI command is successfully placed in the ACI command queue
 */
bool heart_rate_send_hr_rr_interval(uint8_t meas_hr, uint16_t *p_rr_intervals, uint8_t nb_intervals, bool is_freshest_sample);

/** @brief Function to send a heart rate measurement (16 bits) with rr_intervals
 *  @param meas_hr Measured heart_rate to send.
 *  @param p_rr_intervals Pointer to rr_intervals values.
 *  @param nb_intervals Number of rr_intervals.
 *  @return : True when the ACI command is successfully placed in the ACI command queue
 */
bool heart_rate_send_hr_16bits_rr_interval(uint16_t meas_hr, uint16_t *p_rr_intervals, uint8_t nb_intervals, bool is_freshest_sample);

/** @brief Function to send a heart rate measurement (8 bits) with expended energy with rr_intervals
 *  @param meas_hr Measured heart_rate to send.
 *  @param expended_energy Measured expended energy.
 *  @param p_rr_intervals Pointer to rr_intervals values.
 *  @param nb_intervals Number of rr_intervals.
 *  @return : True when the ACI command is successfully placed in the ACI command queue
 */
bool heart_rate_send_hr_expended_energy_rr_interval(uint8_t meas_hr, uint16_t expended_energy, uint16_t *p_rr_intervals, uint8_t nb_intervals, bool is_freshest_sample);

/** @brief Function to send a heart rate measurement (16 bits) with expended energy with rr_intervals
 *  @param meas_hr measured heart_rate to send.
 *  @param expended_energy Measured expended energy.
 *  @param p_rr_intervals Pointer to rr_intervals values.
 *  @param nb_intervals Number of rr_intervals.
 *  @return : True when the ACI command is successfully placed in the ACI command queue
 */
bool heart_rate_send_hr_16bits_expended_energy_rr_interval(uint16_t meas_hr, uint16_t expended_energy, uint16_t *p_rr_intervals, uint8_t nb_intervals, bool is_freshest_sample);

/** @brief Function to check received data
 *  @details Call this function each time data is received (on @c ACI_EVT_DATA_RECEIVED on the control point pipe ).
 *  If the control point is received with the bits indicating to reset Expended Energy, then 
 *  hook_for_resetting_energy_expended will be called.
 *  @param pipe_num Pipe number.
 *  @param buffer The received message.
 */
void heart_rate_pipes_updated_evt_rcvd(aci_state_t *aci_stat, uint8_t pipe_num, uint8_t *buffer);

#ifdef PIPE_HEART_RATE_HEART_RATE_CONTROL_POINT_RX_ACK
/** @brief The hook function that must be implemented in the application. This 
    function will be called when the control point is received with the bits 
    indicating to reset Expended Energy. The service sends acknowledgement to 
    the master before calling this hook function. 
 */
extern void hook_for_resetting_energy_expended(void);
#endif


/** @} */

#endif // heart_rate_H
