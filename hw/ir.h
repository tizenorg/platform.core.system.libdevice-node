/*
 * libdevice-node
 *
 * Copyright (c) 2016 Samsung Electronics Co., Ltd.
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


#ifndef __HW_IR_H__
#define __HW_IR_H__

#include <hw/common.h>

/**
 * The id of this device
 */
#define IR_HARDWARE_DEVICE_ID	"ir"

/**
 * The version of this device
 */
#define IR_HARDWARE_DEVICE_VERSION	MAKE_VERSION(0,1)

struct ir_device {
	struct hw_common common;

	/* Control ir state */
	int (*transmit)(int *frequency_pattern, int size);
};

#endif
