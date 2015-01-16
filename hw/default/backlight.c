/*
 * device-node
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


#include <stdio.h>
#include <errno.h>

#include <hw/backlight.h>
#include "device-internal.h"

static int backlight_set_state(struct backlight_state_t *state)
{
	/* TODO: Need to implement */
	return 0;
}

static int backlight_open(struct hw_info_t *info,
		struct hw_common_t **common)
{
	struct backlight_device_t *backlight_dev;

	if (!info || !*common)
		return -EINVAL;

	backlight_dev = calloc(1, sizeof(struct backlight_device_t));
	if (!backlight_dev)
		return -ENOMEM;

	backlight_dev->common.info = info;
	backlight_dev->set_state = backlight_set_state;

	*common = (struct hw_common_t*)backlight_dev;

	return 0;	
}

struct hw_info_t HARDWARE_INFO_SYM = {
	.unique_id = HARDWARE_INFO_TAG,
	.hal_version = HARDWARE_INFO_VERSION,
	.device_version = BACKLIGHT_HARDWARE_DEVICE_VERSION,
	.id = BACKLIGHT_HARDWARE_DEVICE_ID,
	.name = "Default Backlight",
	.author = "Jiyoung Yun <jy910.yun@samsung.com>",
	.open = backlight_open,
};
