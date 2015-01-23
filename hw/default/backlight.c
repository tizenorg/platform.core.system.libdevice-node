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
#include <stdlib.h>
#include <errno.h>
#include <linux/limits.h>

#include <hw/backlight.h>
#include "device-internal.h"
#include "shared.h"

#define BACKLIGHT_NODE	"/sys/class/leds/led1:heart"

static int get_max_brightness(void)
{
	char buf[PATH_MAX];
	int r, max;

	snprintf(buf, sizeof(buf), "%s/max_brightness", BACKLIGHT_NODE);

	r = sys_get_int(buf, &max);
	if (r < 0) {
		_E("fail to get max brightness : %s", strerror(r));
		return r;
	}

	return max;
}

static int set_brightness(int brt)
{
	char buf[PATH_MAX];
	static int max = -1;
	int v, r;

	if (brt < 0 || brt > 100)
		return -EINVAL;

	if (max < 0) {
		max = get_max_brightness();
		if (max < 0)
			return -EPERM;
	}

	snprintf(buf, sizeof(buf), "%s/brightness", BACKLIGHT_NODE);

	v = brt/100.f*max;
	r = sys_set_int(buf, v);
	if (r < 0)
		return r;

	return 0;
}

static int backlight_set_state(struct backlight_state_t *state)
{
	/* TODO: Need to implement */
	int v, r;

	if (!state || state->brightness < 0)
		return -EINVAL;

	return set_brightness(state->brightness);
}

static int backlight_open(struct hw_info_t *info,
		const char *id, struct hw_common_t **common)
{
	struct backlight_device_t *backlight_dev;

	if (!info || !common)
		return -EINVAL;

	backlight_dev = calloc(1, sizeof(struct backlight_device_t));
	if (!backlight_dev)
		return -ENOMEM;

	backlight_dev->common.info = info;
	backlight_dev->set_state = backlight_set_state;

	*common = (struct hw_common_t*)backlight_dev;

	return 0;
}

static int backlight_close(struct hw_common_t *common)
{
	if (!common)
		return -EINVAL;

	free(common);
	return 0;
}

EXPORT
struct hw_info_t HARDWARE_INFO_SYM = {
	.unique_id = HARDWARE_INFO_TAG,
	.hal_version = HARDWARE_INFO_VERSION,
	.device_version = BACKLIGHT_HARDWARE_DEVICE_VERSION,
	.id = BACKLIGHT_HARDWARE_DEVICE_ID,
	.name = "Default Backlight",
	.author = "Jiyoung Yun <jy910.yun@samsung.com>",
	.open = backlight_open,
	.close = backlight_close,
};
