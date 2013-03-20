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
#include <vconf.h>
#include "device-internal.h"

#define PROPERTY_MASK			0x0F
#define PROPERTY_PROP(val)		((val) & PROPERTY_MASK)
#define PROPERTY_INDEX(val)		((val) >> 4)

static int display_get_prop(int __prop, int *val)
{
	int prop = PROPERTY_PROP(__prop);
	int index = PROPERTY_INDEX(__prop);
	int lux = index;
	int ps_stat;
	int ps_disp_stat;
	int disp_cnt;
	int r;

	r = PLUGIN_GET(display_count)(&disp_cnt);
	if (r < 0) {
		DEVERR("Get display count failed");
		return -1;
	}

	if (prop != PROP_DISPLAY_BRIGHTNESS_BY_LUX) {
		if (index >= disp_cnt) {
			DEVERR("Invalid Argument: index(%d) > max(%d)", index, disp_cnt);
			return -1;
		}
	}

	switch (prop) {
	case PROP_DISPLAY_DISPLAY_COUNT:
		*val = disp_cnt;
		return 0;
	case PROP_DISPLAY_BRIGHTNESS:
		/* check power saving */
		vconf_get_bool(VCONFKEY_SETAPPL_PWRSV_SYSMODE_STATUS, &ps_stat);
		if (ps_stat == 1)
			vconf_get_bool(VCONFKEY_SETAPPL_PWRSV_CUSTMODE_DISPLAY, &ps_disp_stat);
		if (ps_disp_stat != 1)
			ps_disp_stat = 0;
		return PLUGIN_GET(backlight_brightness)(index, val, ps_disp_stat);
	case PROP_DISPLAY_ACL_CONTROL:
		return PLUGIN_GET(backlight_acl_control)(index, val);
	case PROP_DISPLAY_ONOFF:
		return PLUGIN_GET(lcd_power)(index, val);
	case PROP_DISPLAY_BRIGHTNESS_BY_LUX:
		return PLUGIN_GET(backlight_brightness_by_lux)(lux, val);
	case PROP_DISPLAY_IMAGE_ENHANCE_MODE:
		return PLUGIN_GET(image_enhance_mode)(val);
	case PROP_DISPLAY_IMAGE_ENHANCE_SCENARIO:
		return PLUGIN_GET(image_enhance_scenario)(val);
	case PROP_DISPLAY_IMAGE_ENHANCE_TONE:
		return PLUGIN_GET(image_enhance_tone)(val);
	case PROP_DISPLAY_IMAGE_ENHANCE_OUTDOOR:
		return PLUGIN_GET(image_enhance_outdoor)(val);
	case PROP_DISPLAY_IMAGE_ENHANCE_INFO:
		return PLUGIN_SYS(image_enhance_info)(val);
	}

	return -1;
}

static int display_set_prop(int __prop, int val)
{
	int prop = PROPERTY_PROP(__prop);
	int index = PROPERTY_INDEX(__prop);
	int ps_stat;
	int ps_disp_stat;
	int disp_cnt;
	int r;

	r = PLUGIN_GET(display_count)(&disp_cnt);
	if (r < 0) {
		DEVERR("Get display count failed");
		return -1;
	}

	if (index >= disp_cnt) {
		DEVERR("Invalid Argument: index(%d) > max(%d)", index, disp_cnt);
		return -1;
	}

	switch (prop) {
	case PROP_DISPLAY_BRIGHTNESS:
		/* check power saving */
		vconf_get_bool(VCONFKEY_SETAPPL_PWRSV_SYSMODE_STATUS, &ps_stat);
		if (ps_stat == 1)
			vconf_get_bool(VCONFKEY_SETAPPL_PWRSV_CUSTMODE_DISPLAY, &ps_disp_stat);
		if (ps_disp_stat != 1)
			ps_disp_stat = 0;
		return PLUGIN_SET(backlight_brightness)(index, val, ps_disp_stat);
	case PROP_DISPLAY_ACL_CONTROL:
		return PLUGIN_SET(backlight_acl_control)(index, val);
	case PROP_DISPLAY_ONOFF:
		return PLUGIN_SET(lcd_power)(index, val);
	case PROP_DISPLAY_FRAME_RATE:
		return PLUGIN_SET(display_frame_rate)(val);
	case PROP_DISPLAY_IMAGE_ENHANCE_MODE:
		return PLUGIN_SET(image_enhance_mode)(val);
	case PROP_DISPLAY_IMAGE_ENHANCE_SCENARIO:
		return PLUGIN_SET(image_enhance_scenario)(val);
	case PROP_DISPLAY_IMAGE_ENHANCE_TONE:
		return PLUGIN_SET(image_enhance_tone)(val);
	case PROP_DISPLAY_IMAGE_ENHANCE_OUTDOOR:
		return PLUGIN_SET(image_enhance_outdoor)(val);
	}

	return -1;
}

static const struct device display = {
	.name     = "display",
	.set_prop = display_set_prop,
	.get_prop = display_get_prop,
	.type     = DEVICE_TYPE_DISPLAY,
};

static void __CONSTRUCTOR__ module_init(void)
{
	add_device(&(display.type));
}

static void __DESTRUCTOR__ module_fini(void)
{
	remove_device(&(display.type));
}
