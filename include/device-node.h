/*
 * device-node
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef __DEVICE_NODE_H__
#define __DEVICE_NODE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "devman_plugin_intf.h"

#ifndef API
#define API __attribute__ ((visibility("default")))
#endif

/**
 * @file        device-node.h
 * @ingroup     FRAMEWORK/SYSTEM
 * @brief       This file contains the API for the status of devices
 * @author      TIZEN
 * @date        2013-02-15
 * @version     0.1
 */

/**
 * @addtogroup DEVICE_NODE
 * @{
 */

/**
 * @par Description:
 * 	device type enum
 */
enum device_type
{
	DEVICE_TYPE_DISPLAY,            /**< display */
	DEVICE_TYPE_VIBRATOR,           /**< vibrator */
	DEVICE_TYPE_EXTCON,             /**< extcon - Micro USB, 3.5 pi jack etc */
	DEVICE_TYPE_LED,                /**< LED */
	DEVICE_TYPE_POWER,              /**< battery, PMIC, etc about power */
	DEVICE_TYPE_MEMORY,             /**< memory */
	DEVICE_TYPE_CPU,                /**< cpu */
	DEVICE_TYPE_PROCESS,            /**< process */
	DEVICE_TYPE_MAX,
};

/**
 * @par Description:
 * 	DEVICE_TYPE_DISPLAY property for generic APIs
 */
enum {
	PROP_DISPLAY_DISPLAY_COUNT,
	PROP_DISPLAY_BRIGHTNESS,
	PROP_DISPLAY_ACL_CONTROL,
	PROP_DISPLAY_ONOFF,
	PROP_DISPLAY_BRIGHTNESS_BY_LUX,
	PROP_DISPLAY_FRAME_RATE,
	PROP_DISPLAY_IMAGE_ENHANCE_MODE,
	PROP_DISPLAY_IMAGE_ENHANCE_SCENARIO,
	PROP_DISPLAY_IMAGE_ENHANCE_TONE,
	PROP_DISPLAY_IMAGE_ENHANCE_OUTDOOR,
	PROP_DISPLAY_IMAGE_ENHANCE_TUNE,
	PROP_DISPLAY_IMAGE_ENHANCE_INFO,
};

/**
 * @par Description:
 * DEVICE_TYPE_HAPTIC property for generic APIs
 */
enum {
	PROP_VIBRATOR_LEVEL_MAX,
	PROP_VIBRATOR_LEVEL,
	PROP_VIBRATOR_ENABLE,
	PROP_VIBRATOR_ONESHOT,
};

/**
 * @par Description:
 * 	DEVICE_TYPE_JACK property for generic APIs
 */
enum {
	PROP_EXTCON_TA_ONLINE,        /**< Travel Adapter(Charger) */
	PROP_EXTCON_EARJACK_ONLINE,   /**< Earjack */
	PROP_EXTCON_EARKEY_ONLINE,    /**< Earkey */
	PROP_EXTCON_HDMI_ONLINE,      /**< HDMI */
	PROP_EXTCON_USB_ONLINE,       /**< USB connection */
	PROP_EXTCON_CRADLE_ONLINE,    /**< Cradle connection */
	PROP_EXTCON_TVOUT_ONLINE,     /**< analog tvout */
	PROP_EXTCON_KEYBOARD_ONLINE,  /**< Microphone */
	PROP_EXTCON_HDMI_SUPPORT,     /**< Support HDMI*/
	PROP_EXTCON_UART_PATH,
	PROP_EXTCON_USB_PATH,
};

/**
 * @par Description:
 *  DEVICE_TYPE_LED property for generic APIs
 */
enum {
	PROP_LED_BRIGHTNESS,
	PROP_LED_MAX_BRIGHTNESS,
};

/**
 * @par Description:
 * 	DEVICE_TYPE_POWER property for generic APIs
 */
enum {
	PROP_POWER_CAPACITY,                    /**< Current remaining battery */
	PROP_POWER_CAPACITY_RAW,                /**< Current remaining battery expressed 1/10000 */
	PROP_POWER_CHARGE_FULL,                 /**< Battery is full-charged.*/
	PROP_POWER_CHARGE_NOW,                  /**< Battery is being charged now */
	PROP_POWER_STATE,
	PROP_POWER_WAKEUP_COUNT,
	PROP_POWER_PRESENT,
	PROP_POWER_HEALTH,                      /**< Battery status about cahrge */
	PROP_POWER_INSUSPEND_CHARGING_SUPPORT,
};

/**
 * @par Description:
 * 	DEVICE_TYPE_MEMORY property for generic APIs
 */
enum {
	PROP_MEMORY_NODE,
	PROP_MEMORY_VICTIM_TASK,
	PROP_MEMORY_THRESHOLD_LV1,
	PROP_MEMORY_THRESHOLD_LV2,
};

/**
 * @par Description:
 * 	DEVICE_TYPE_CPU property for generic APIs
 */
enum {
	PROP_CPU_CPUINFO_MAX_FREQ,
	PROP_CPU_CPUINFO_MIN_FREQ,
	PROP_CPU_SCALING_MAX_FREQ,
	PROP_CPU_SCALING_MIN_FREQ,
};

/**
 * @par Description:
 * 	DEVICE_TYPE_PROCESS property for generic APIs
 */
enum {
	PROP_PROCESS_NODE,
	PROP_PROCESS_MP_PNP,
	PROP_PROCESS_MP_VIP,
};

/**
 * @fn int device_get_property(enum device_type devtype, int property, int *value)
 * @par Description:
 * 	This generic API is used to get the property values of supported devices.\n
 * 	If the caller process does not have permission, it returns failure.
 * @param[in] devtype device type that you want to get the value
 * @param[in] property value property that you want to get the value
 * @param[out] *value current value of device property
 * @return 0 on success, -1 if failed
 * @see device_set_property()
 * @par Example:
 * @code
 * 	...
 * 	if( device_get_property(DEVICE_TYPE_POWER, PROP_POWER_CAPACITY, &val) < 0 )
 * 		printf("Fail to get property\n");
 * 	else
 * 		printf("Property is %d\n", val);
 * 	...
 * @endcode
 */
int device_get_property(enum device_type devtype, int property, int *value);

/**
 * @fn int device_set_property(enum device_type devtype, int property, int value)
 * @par Description:
 * 	This generic API is used to set the property values of supported devices.\n
 * 	If the caller process does not have permission, it returns failure.
 * @param[in] devtype device type that you want to set the value
 * @param[in] property value property that you want to set the value
 * @param[in] value value that you want to set
 * @return 0 on success, -1 if failed
 * @see device_get_property()
 * @par Example
 * @code
 *	...
 *	if( device_set_property(DEVICE_TYPE_DISPLAY, PROP_DISPLAY_BRIGHTNESS, val) < 0 )
 *		printf("Fail to set property\n");
 *	else
 *		printf("Property is set %d\n", val);
 *	...
 * @endcode
 */
int device_set_property(enum device_type devtype, int property, int value);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif
#endif
