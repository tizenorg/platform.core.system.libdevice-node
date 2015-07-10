/*
 * libdevice-node
 *
 * Copyright (c) 2015 Samsung Electronics Co., Ltd.
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


#ifndef __HW_BATTERY_H__
#define __HW_BATTERY_H__

#include <hw/common.h>

/**
 * The id of this device
 */
#define BATTERY_HARDWARE_DEVICE_ID	"battery"

/**
 * The version of this device
 */
#define BATTERY_HARDWARE_DEVICE_VERSION	MAKE_VERSION(0,1)

/**
 * The battery status type
 */
#define BATTERY_STATUS_UNKNOWN          "Unknown"
#define BATTERY_STATUS_CHARGING         "Charging"
#define BATTERY_STATUS_DISCHARGING      "Discharging"
#define BATTERY_STATUS_NOT_CHARGING     "Not charging"
#define BATTERY_STATUS_FULL             "Full"

/**
 * The battery health type
 */
#define BATTERY_HEALTH_GOOD             "Good"
#define BATTERY_HEALTH_OVERHEAT         "Overheat"
#define BATTERY_HEALTH_DEAD             "Dead"
#define BATTERY_HEALTH_OVER_VOLTAGE     "Over voltage"
#define BATTERY_HEALTH_UNSPEC_FAILURE   "Unspecified failure"
#define BATTERY_HEALTH_COLD             "Cold"
#define BATTERY_HEALTH_WATCHDOG_TIMER_EXPIRE "Watchdog timer expire"
#define BATTERY_HEALTH_SAFETY_TIMER_EXPIRE   "Safety timer expire"

/**
 * The battery online type
 */
#define BATTERY_ONLINE_UNKNOWN           "0"
#define BATTERY_ONLINE_BATTERY           "1"
#define BATTERY_ONLINE_UPS               "2"
#define BATTERY_ONLINE_MAINS             "3"
#define BATTERY_ONLINE_USB               "4"

enum battery_property {
	BATTERY_PROP_STATUS,            /* Operating status (This corresponds to BATTERY_STATUS_* values) */
	BATTERY_PROP_HEALTH,            /* Health (This corresponds to BATTERY_HEALTH_* values) */
	BATTERY_PROP_PRESENT,           /* CF pin state (0:abnormal(open), 1:normal(close)) */
	BATTERY_PROP_VOLTAGE_NOW,       /* Voltage instantaneous values */
	BATTERY_PROP_CAPACITY,          /* Capacity in *percents*, from 0 to 100 */
	BATTERY_PROP_ONLINE,            /* Power supply source types (This corresponds to BATTERY_ONLINE_* values) */
	BATTERY_PROP_TEMP,              /* Temperatures of the power supply */
	BATTERY_PROP_CURRENT_NOW,       /* Current instantaneous values */
};

struct battery_device {
	struct hw_common common;

	/* Get property */
	const char *(*get_property)(enum battery_property);
};

#endif
