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


#ifndef __HW_BACKLIGHT_H__
#define __HW_BACKLIGHT_H__

#include <hw/common.h>

/**
 * The id of this device
 */
#define BACKLIGHT_HARDWARE_DEVICE_ID	"backlight"

/**
 * The version of this device
 */
#define BACKLIGHT_HARDWARE_DEVICE_VERSION	MAKE_VERSION(1,0)

/**
 * The mode of backlight
 */
enum backlight_mode {
	BACKLIGHT_MANUAL,	/* Manual setting */
	BACKLIGHT_SENSOR,	/* Worked by sensor */
};

struct backlight_device {
	struct hw_common common;

	/**
	 * The brightness value is 0 to 100.
	 */
	int (*get_brightness)(int *brightness);
	int (*set_brightness)(int brightness);

	/**
	 * The backlight mode can be BACKLIGHT_MANUAL and BACKLIGHT_SENSOR.
	 */
	int (*get_mode)(enum backlight_mode *mode);
	int (*set_mode)(enum backlight_mode mode);
};

#endif
