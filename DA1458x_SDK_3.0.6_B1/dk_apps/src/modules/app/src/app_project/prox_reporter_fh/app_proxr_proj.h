/**
****************************************************************************************
*
* @file app_proxr_proj.h
*
* @brief Proximity Project application header file.
*
* Copyright (C) 2012. Dialog Semiconductor Ltd, unpublished work. This computer 
 * program includes Confidential, Proprietary Information and is a Trade Secret of 
 * Dialog Semiconductor Ltd.  All use, disclosure, and/or reproduction is prohibited 
 * unless authorized in writing. All Rights Reserved.
*
* <bluetooth.support@diasemi.com> and contributors.
*
****************************************************************************************
*/

#ifndef APP_PROXR_PROJ_H_
#define APP_PROXR_PROJ_H_

/**
 ****************************************************************************************
 * @addtogroup APP
 * @ingroup RICOW
 *
 * @brief Accelerometer Application entry point.
 *
 * @{
 ****************************************************************************************
 */


/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwble_config.h"
#include "app_task.h"                  // application task
#include "gapc_task.h"                  // gap functions and messages
#include "gapm_task.h"                  // gap functions and messages
#include "app.h"                       // application definitions
#include "co_error.h"                  // error code definitions
#include "smpc_task.h"                  // error code definitions
                  

#if (BLE_PROX_REPORTER)
#include "app_proxr.h"
#include "app_proxr_task.h"
#endif 

#if (BLE_BATT_SERVER)
#include "app_batt.h"
#include "app_batt_task.h"
#endif

#if (BLE_FINDME_TARGET) || (BLE_FINDME_LOCATOR)
#include "app_findme.h"
#include "app_findme_task.h"
#endif

#if (BLE_DIS_SERVER)
#include "app_dis.h"
#include "app_dis_task.h"
#endif

#if (BLE_SAMPLE128)
#include "sample128.h"
#include "sample128_task.h"
extern uint8_t sample128_placeholder;
extern uint8_t sample128_LED;
extern uint8_t Sample_LED_Blink;
extern uint8_t Flag_Adv;
extern my_newer1_addChar sample128_my_new;
extern my_newer2_addChar sample128_2_new;
extern uint8_t PM2_5[characristic2_length];
extern uint16_t PM2_5_val;
extern uint8_t uart_buf[5];
extern uint8_t uart_bufcnt,uart_buf_flag;
extern uint8_t PM2_5Cnt;
extern uint8_t Prameter[11];
extern uint8_t flag_Connect,flag_Connect_kind,flag_PM25;
extern uint8_t flag_WakeUp_Function;
extern uint8_t flag_Uart2_Init;
#endif
/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */

/**
 * Default Advertising data
 * --------------------------------------------------------------------------------------
 * x02 - Length
 * x01 - Flags
 * x06 - LE General Discoverable Mode + BR/EDR Not Supported
 * --------------------------------------------------------------------------------------
 * x03 - Length
 * x03 - Complete list of 16-bit UUIDs available
 * x09\x18 - Health Thermometer Service UUID
 *   or
 * x00\xFF - Nebulization Service UUID
 * --------------------------------------------------------------------------------------
 */

#if BLE_PROX_REPORTER
#define APP_DEVICE_NAME "DA14580 PXR"
#else
#define APP_DEVICE_NAME "DA14580"
#endif

#if (BLE_SPOTA_RECEIVER)
    #define APP_ADV_DATA        "\x09\x03\x03\x18\x02\x18\x04\x18\xF5\xFE"
    #define APP_ADV_DATA_LEN    (8+2)
#else
    #define APP_ADV_DATA        "\x07\x03\x03\x18\x02\x18\x04\x18"
	#define APP_ADV_DATA_LEN    (8)
#endif // #if (BLE_SPOTA_RECEIVER)

/**
 * Default Scan response data
 * --------------------------------------------------------------------------------------
 * x09                             - Length
 * xFF                             - Vendor specific advertising type
 * x00\x60\x52\x57\x2D\x42\x4C\x45 - "RW-BLE"
 * --------------------------------------------------------------------------------------
 */
#define APP_SCNRSP_DATA         "\x09\xFF\x00\x60\x52\x57\x2D\x42\x4C\x45"
#define APP_SCNRSP_DATA_LENGTH  (10)


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */


void app_button_enable(void);

/**
 ****************************************************************************************
 * @brief Advertise timer handler. Set device in deep sleep mode
 *
 * @return int.
 ****************************************************************************************
*/

int app_adv_timer_handler(ke_msg_id_t const msgid,
                                   void const *param,
                                   ke_task_id_t const dest_id,
                                   ke_task_id_t const src_id);

/**
 ****************************************************************************************
 * @brief Handles APP_WAKEUP_MSG sent when device exits deep sleep. Trigerred by button press.
 * 
 * @return int.
 ****************************************************************************************
*/

int app_wakeup_handler(ke_msg_id_t const msgid,
									void *param,
									ke_task_id_t const dest_id,
									ke_task_id_t const src_id);
									
void app_sample128_init(void);

/**
 ****************************************************************************************
 * @brief Add a Device Information Service instance in the DB
 ****************************************************************************************
 */
void app_sample128_create_db_send(void);


/**
 ****************************************************************************************
 * @brief Enable the Device Information Service
 ****************************************************************************************
 */
void app_sample128_enable(void);
/**
****************************************************************************************
* @brief Handles sample128 profile database creation confirmation.
* @return If the message was consumed or not.
****************************************************************************************
*/
int sample128_create_db_cfm_handler(ke_msg_id_t const msgid,
																			 struct sample128_create_db_cfm const *param,
																			 ke_task_id_t const dest_id,
																			 ke_task_id_t const src_id);
/**
****************************************************************************************
* @brief Handles disable indication from the sample128 profile.
* @return If the message was consumed or not.
****************************************************************************************
*/
int sample128_disable_ind_handler(ke_msg_id_t const msgid,
																			 struct sample128_disable_ind const *param,
																			 ke_task_id_t const dest_id,
																			 ke_task_id_t const src_id);
/**
****************************************************************************************
* @brief Handles write of 1st characteristic event indication from sample128 profile
* @return If the message was consumed or not.
****************************************************************************************
*/
int sample128_val_ind_handler(ke_msg_id_t const msgid,
																			 struct sample128_val_ind const *param,
																			 ke_task_id_t const dest_id,
																			 ke_task_id_t const src_id);
int sample128_C2_val_ind_handler(ke_msg_id_t const msgid,
																struct sample128_C2_val_ind const *param,
																ke_task_id_t const dest_id,
																ke_task_id_t const src_id);																			
/**
****************************************************************************************
* @brief Handles timer timeout
* @return If the message was consumed or not.
****************************************************************************************
*/																			 
int sample128_timer_handler(ke_msg_id_t const msgid,
													 struct gapm_cmp_evt const *param,
													 ke_task_id_t const dest_id,
													 ke_task_id_t const src_id);
void sample128_C2_val_Change(void);																							 
unsigned char CharToHex(unsigned char bHex);
unsigned char HexToChar(unsigned char bChar);

/// @} APP

#endif //APP_PROXR_PROJ_H_
