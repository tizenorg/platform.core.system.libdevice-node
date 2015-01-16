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
enum backlight_mode_e {
	BACKLIGHT_MANUAL,	/* Manual setting */
	BACKLIGHT_SENSOR,	/* Worked by sensor */
};

/**
 * The state of this device
 */
struct backlight_state_t {
	/**
	 * The range of brightness is 0 to 100.
	 * If you want to keep the current brightness when you change
	 * to BACKLIGHT_MANUAL from BACKLIGHT_SENSOR, you can set -1.
	 * It will keep the current brightness.
	 * When you change to BACKLIGHT_SENSOR from BACKLIGHT_MANUAL,
	 * you don't need to set brighntess.
	 * It wil be changed automitically by light sensor data.
	 */
	int brightness;
	/** refer to enum lights_mode */
	enum backlight_mode_e mode;
};

struct backlight_device_t {
	struct hw_common_t common;

	int (*set_state)(struct backlight_state_t *state);
};

#endif
