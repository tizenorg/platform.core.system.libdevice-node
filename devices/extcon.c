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

static int extcon_get_prop(int prop, int *val)
{
	switch (prop) {
	case PROP_EXTCON_TA_ONLINE:
		return PLUGIN_GET(jack_charger_online)(val);
	case PROP_EXTCON_EARJACK_ONLINE:
		return PLUGIN_GET(jack_earjack_online)(val);
	case PROP_EXTCON_EARKEY_ONLINE:
		return PLUGIN_GET(jack_earkey_online)(val);
	case PROP_EXTCON_HDMI_ONLINE:
		return PLUGIN_GET(jack_hdmi_online)(val);
	case PROP_EXTCON_USB_ONLINE:
		return PLUGIN_GET(jack_usb_online)(val);
	case PROP_EXTCON_CRADLE_ONLINE:
		return PLUGIN_GET(jack_cradle_online)(val);
	case PROP_EXTCON_TVOUT_ONLINE:
		return PLUGIN_GET(jack_tvout_online)(val);
	case PROP_EXTCON_KEYBOARD_ONLINE:
		return PLUGIN_GET(jack_keyboard_online)(val);
	case PROP_EXTCON_HDMI_SUPPORT:
		return PLUGIN_GET(hdmi_support)(val);
	case PROP_EXTCON_UART_PATH:
		return PLUGIN_GET(uart_path)(val);
	case PROP_EXTCON_USB_PATH:
		return PLUGIN_GET(usb_path)(val);
	}

	return -1;
}

static int extcon_set_prop(int prop, int val)
{
	int r;

	switch (prop) {
	case PROP_EXTCON_UART_PATH:
		r = PLUGIN_SET(uart_path)(val);
		if (r == 0) {
			if (val == PATH_CP)
				system("/usr/bin/save_blenv uartpath CP");
			else
				system("/usr/bin/save_blenv uartpath AP");
		}
		return r;
	case PROP_EXTCON_USB_PATH:
		r = PLUGIN_SET(usb_path)(val);
		if (r == 0) {
			if (val == PATH_CP)
				system("/usr/bin/save_blenv usbpath CP");
			else
				system("/usr/bin/save_blenv usbpath AP");
		}
		return r;
	}

	return -1;
}


static const struct device extcon = {
	.name     = "extcon",
	.set_prop = extcon_set_prop,
	.get_prop = extcon_get_prop,
	.type     = DEVICE_TYPE_EXTCON,
};

static void __CONSTRUCTOR__ module_init(void)
{
	add_device(&(extcon.type));
}

static void __DESTRUCTOR__ module_fini(void)
{
	remove_device(&(extcon.type));
}
