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

/** @defgroup battery battery
* @{
* @ingroup services
*  
* @brief battery service implementation.
* @details
* This module implements the battery service with characteristics : battery_level, battery_state and the aggregate of level and state.
*
* The level, in percent, is computed using @ref lib_battery_level by the function @ref update_battery.
* 
*/
#include <stdint.h>

#ifndef BATTERY_H__
#define BATTERY_H__

//Defines the battery level percentage change required to send value over the air.
#define BATTERY_LVL_CHANGE_THRESHOLD 1

/**BATTERY DATA BUFFER SIZE: Set to 0 to disable data buffering. If 0, battery data will be discarded when there is
* no data credit. If non 0, data will be inserted in FIFO buffer and sent whenever data credit is available.
*/
#define BATTERY_DATA_BUFF_SIZE 0

//Constants for voltage divider coupled to ADC. ADC and voltage divider is used for battery voltage measurement.
#define REFERNCE_VOLTAGE_MVOLT 1100           //Selected reference voltage of the ADC in millivolts
#define R1_RESISTANCE_KOHM 6490               //Value of R1 resistor in the coupled voltage divider
#define R2_RESISTANCE_KOHM 822                //Value of R2 resistor in the coupled voltage divider
#define BATTERY_AIN_PIN 0                     //Analog input pin to measure, pin A0 = 0, pin A1 = 1, etc
#define OFFSET_ERROR_CALIBRATION_FACTOR 2.15	//Factor to correct offset error of the ADC. Modify if needed.
#define GAIN_ERROR_CALIBRATION_FACTOR 0.9864	//Factor to correct gain error of the ADC. Modify if needed.

/** @brief Initializes the battery data buffers.
 */
void init_battery_data_buffers();

/** @brief Insert data into the battery data buffer if it is not full.
 *  @details Returns SUCCESS if data is inserted, otherwise BUFFER_FULL.
 */
uint8_t insert_data_into_battery_buffer(uint8_t battery_percent_level);

/** @brief Sends data over the air if there is any data in the battery data buffer.
 *  @details Returns SUCCESS if data is sent, otherwise BUFFER_EMPTY.
 */
uint8_t send_data_from_battery_buffer(aci_state_t * aci_state);

/** @brief Function to check the battery.
 *  @details This function checks the battery's current level. Call this function periodically to monitor the battery.
 *  @param percent_level Measured battery level in percent.
 */
void update_battery(aci_state_t *aci_stat, uint8_t percent_level);


/** @brief Battery's pipe_status event handler.
 *  @details Call this function on @c PipeStatusEvent.
 */
void battery_on_pipe_status(aci_state_t *aci_stat);

/** @brief Battery's connect event handler.
 *  @details Call this function on @c ConnectedEvent.
 *  @param percent_level Measured battery level in percent.
 */
void battery_on_connect(uint8_t percent_level);

/** @brief Battery's disconnect event handler.
 *  @details Call this function on @c DisconnectedEvent.
 *  @param percent_level Measured battery level in percent.
 */
void battery_on_disconnect(uint8_t percent_level);

/** @brief Samples battery voltage and returns battery level as percentage.
 *  @details Uses the internal ADC to sample the battery voltage. Uses the internal 1.1V VBG voltage
 *  as reference for the AIN input voltage. Performs offset and gain error calibration. Returns
 *  battery level percentage
 */
uint8_t measure_battery(aci_state_t *aci_state);

/** @brief Prints out battery measurement data
 *  @details Prints out on the serial connection: 
 *  Timestamp for ADC sample (milliseconds)
 *  10 bit ADC output value
 *  Voltage on the sampled analog input pin (millivolts)
 *  Supply voltage (millivolts)
 *  Battery level (percentage) 
 */
void print_battery_measurement_data(void);

/** @brief Returns simulated battery level value
 *  @details Returns simulated battery level value in 
 *  percentage. The value is periodically incremented
 *  and decremented.
 */
uint8_t get_simulated_battery_value(void);


#endif //BATTERY_H__

//@}
