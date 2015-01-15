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
#include <stdint.h>
#include "device-internal.h"

static int led_get_prop(int prop, int *val)
{
	switch (prop) {
	case PROP_LED_MAX_BRIGHTNESS:
		return PLUGIN_GET(leds_torch_max_brightness, val);
	case PROP_LED_BRIGHTNESS:
		return PLUGIN_GET(leds_torch_brightness, val);
	case PROP_LED_HARDKEY:
		return PLUGIN_GET(hardkey_backlight, val);
	}

	return -1;
}

static int led_set_prop(int prop, int val)
{
	switch (prop) {
	case PROP_LED_BRIGHTNESS:
		return PLUGIN_SET(leds_torch_brightness, val);
	case PROP_LED_IR_COMMAND:
		return PLUGIN_SET(irled_control, (char*)(intptr_t)val);
	case PROP_LED_HARDKEY:
		return PLUGIN_SET(hardkey_backlight, val);
	}

	return -1;
}

static const struct device led = {
	.name     = "led",
	.set_prop = led_set_prop,
	.get_prop = led_get_prop,
	.type     = DEVICE_TYPE_LED,
};

static void __CONSTRUCTOR__ module_init(void)
{
	add_device(&(led.type));
}

static void __DESTRUCTOR__ module_fini(void)
{
	remove_device(&(led.type));
}
