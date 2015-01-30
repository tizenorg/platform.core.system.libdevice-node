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


#ifndef __HW_LED_H__
#define __HW_LED_H__

#include <hw/common.h>

/**
 * The id of this device
 */
#define LED_HARDWARE_DEVICE_ID	"led"

/**
 * The version of this device
 */
#define LED_HARDWARE_DEVICE_VERSION	MAKE_VERSION(1,0)

/**
 * The id of led devices
 */
#define LED_ID_CAMERA_BACK		"camera_back"
#define LED_ID_CAMERA_FRONT		"camera_front"
#define LED_ID_NOTIFICATION		"notification"
#define LED_ID_TOUCH_KEY		"touch_key"

enum led_type {
	LED_TYPE_MANUAL,
	LED_TYPE_BLINK,
};

struct led_state {
	/* Led type */
	enum led_type type;
	/**
	 * The first byte means opaque and the other 3 bytes are RGB values.
	 * You can use opaque byte as a led brightness value.
	 * If the first byte is 0x00, led will be turned off.
	 * Anything else will be worked as on. The max value is 0xFF.
	 */
	unsigned int color;
	/* Turn on time in milliseconds */
	int duty_on;
	/* Turn off time in milliseconds */
	int duty_off;
};

struct led_device {
	struct hw_common common;

	/**
	 * Set led state
	 */
	int (*set_state)(struct led_state *state);
};

#endif
