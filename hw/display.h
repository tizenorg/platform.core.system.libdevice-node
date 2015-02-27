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


#ifndef __HW_DISPLAY_H__
#define __HW_DISPLAY_H__

#include <hw/common.h>

/**
 * The id of this device
 */
#define DISPLAY_HARDWARE_DEVICE_ID	"display"

/**
 * The version of this device
 */
#define DISPLAY_HARDWARE_DEVICE_VERSION	MAKE_VERSION(1,0)

/**
 * The mode of display
 */
enum display_mode {
	DISPLAY_MANUAL,	/* Manual setting */
	DISPLAY_SENSOR,	/* Worked by sensor */
};

enum display_power {
	DISPLAY_POWER_ON,
	DISPLAY_POWER_STANDBY,
	DISPLAY_POWER_SUSPEND,
	DISPLAY_POWER_OFF,
};

struct display_device {
	struct hw_common common;

	/**
	 * The brightness value is 0 to 100.
	 */
	int (*get_brightness)(int *brightness);
	/**
	 * reset is false, hardware can be return the brightness using previous brightness
	 * if not, it returns the brightness value without previous lux setting.
	 */
	int (*get_brightness_by_lux)(int lux, int reset,
			int level, int **level_array);
	int (*set_brightness)(int brightness);

	/* Control display power */
	int (*get_power)(enum display_power *state);
	int (*set_power)(enum display_power state);

	/* Control framerate */
	int (*set_framerate)(int val);

	/* Control ambient mode */
	int (*get_ambient_mode)(int *val);
	int (*set_ambient_mode)(int val);
};

#endif
