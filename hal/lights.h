/*
 * deviced
 *
 * Copyright (c) 2012 - 2013 Samsung Electronics Co., Ltd.
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


#ifndef __HAL_LIGHTS_H__
#define __HAL_LIGHTS_H__

#include <hardware/common.h>

/**
 * The id of this device
 */
#define LIGHTS_HARDWARE_DEVICE_ID	"lights"

/**
 * The mode of lights
 */
enum lights_mode {
	LIGHTS_MANUAL,	/* Manual setting */
	LIGHTS_SENSOR,	/* Worked by sensor */
};

/**
 * The state of this device
 */
struct lights_state_t {
	/** The range of brightness is 0 to 100 */
	int brightness;
	/** refer to enum lights_mode */
	enum lights_mode mode;
};

struct lights_device_t {
	struct hw_device_t common;
	
	int (*set_state)(struct lights_state_t *state);
};

#endif
