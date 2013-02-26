/*
 * device-node
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
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
#include "device-internal.h"

static int vibrator_get_prop(int prop, int *val)
{
	switch (prop) {
	case PROP_VIBRATOR_LEVEL:
		return PLUGIN_GET(haptic_vibetones_level)(val);
	case PROP_VIBRATOR_LEVEL_MAX:
		return PLUGIN_GET(haptic_vibetones_level_max)(val);
	}

	return -1;
}

static int vibrator_set_prop(int prop, int val)
{
	switch (prop) {
	case PROP_VIBRATOR_ENABLE:
		return PLUGIN_SET(haptic_vibetones_enable)(val);
	case PROP_VIBRATOR_LEVEL:
		return PLUGIN_SET(haptic_vibetones_level)(val);
	case PROP_VIBRATOR_ONESHOT:
		return PLUGIN_SET(haptic_vibetones_oneshot)(val);
	}

	return -1;
}

static const struct device vibrator = {
	.name     = "vibrator",
	.set_prop = vibrator_set_prop,
	.get_prop = vibrator_get_prop,
	.type     = DEVICE_TYPE_VIBRATOR,
};

static void __CONSTRUCTOR__ module_init(void)
{
	add_device(&(vibrator.type));
}

static void __DESTRUCTOR__ module_fini(void)
{
	remove_device(&(vibrator.type));
}
