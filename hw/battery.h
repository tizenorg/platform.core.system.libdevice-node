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

#define POWER_SOURCE_NONE     "none"
#define POWER_SOURCE_AC       "ac"
#define POWER_SOURCE_USB      "usb"
#define POWER_SOURCE_WIRELESS "wireless"

/**
 * The version of this device
 */
#define BATTERY_HARDWARE_DEVICE_VERSION	MAKE_VERSION(0,1)

struct battery_info {
	char *name;
	char *status;
	char *health;
	char *power_source;

	int online;
	int present;
	int capacity;

	int current_now;
	int current_average;
};

typedef void (*BatteryUpdated)(struct battery_info *info, void *data);

struct battery_device {
	struct hw_common common;

	/* Register battery event */
	int (*register_changed_event)(BatteryUpdated updated_cb, void *data);
	void (*unregister_changed_event)(BatteryUpdated updated_cb);

	/* Get current states */
	int (*get_current_state)(BatteryUpdated updated_cb, void *data);
};

#endif
