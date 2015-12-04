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


#ifndef __HW_TOUCHSCREEN_H__
#define __HW_TOUCHSCREEN_H__

#include <hw/common.h>

/**
 * The id of this device
 */
#define TOUCHSCREEN_HARDWARE_DEVICE_ID	"touchscreen"

/**
 * The version of this device
 */
#define TOUCHSCREEN_HARDWARE_DEVICE_VERSION	MAKE_VERSION(0,1)

enum touchscreen_state {
	TOUCHSCREEN_OFF,     /* Disable touchscreen */
	TOUCHSCREEN_ON,      /* Enable touchscreen */
};

struct touchscreen_device {
	struct hw_common common;

	/* Control touchscreen state */
	int (*get_state)(enum touchscreen_state *state);
	int (*set_state)(enum touchscreen_state state);
};

#endif
