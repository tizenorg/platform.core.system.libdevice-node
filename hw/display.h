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


#ifndef __HW_DISPLAY_H__
#define __HW_DISPLAY_H__

#include <hw/common.h>

/**
 * The id of this device
 */
#define DISPLAY_HARDWARE_DEVICE_ID	"display"

/**
 * The version of this device
 */
#define DISPLAY_HARDWARE_DEVICE_VERSION	MAKE_VERSION(0,2)

enum display_state {
	DISPLAY_ON,       /* In use */
	DISPLAY_STANDBY,  /* Blanked, low power */
	DISPLAY_SUSPEND,  /* Blanked, lower power */
	DISPLAY_OFF,      /* Shut off, awaiting activity */
};

enum display_image_effect {
	DISPLAY_IMAGE_EFFECT_STANDARD,     /* No effect */
	DISPLAY_IMAGE_EFFECT_NEGATIVE,     /* Total inversion */
	DISPLAY_IMAGE_EFFECT_GRAYSCALE,    /* Shades of gray and no color */
	DISPLAY_IMAGE_EFFECT_PICTURE,      /* Picture effect */
	DISPLAY_IMAGE_EFFECT_VIDEO,        /* Video effect */
	DISPLAY_IMAGE_EFFECT_MOVIE,        /* Movie effect */
	DISPLAY_IMAGE_EFFECT_BROWSER,      /* Browser effect */
	DISPLAY_IMAGE_EFFECT_WARM,         /* Warm effect */
	DISPLAY_IMAGE_EFFECT_COLD,         /* Cold effect */
	DISPLAY_IMAGE_EFFECT_NATURAL,      /* Natural effect */
};

enum display_panel_mode {
	DISPLAY_PANEL_MODE_STANDARD,      /* Standard mode */
	DISPLAY_PANEL_MODE_OUTDOOR,       /* Outdoor mode */
	DISPLAY_PANEL_MODE_CONTENTS,      /* Contents adaptive brightness control mode */
	DISPLAY_PANEL_MODE_LOWPOWER,      /* Low power mode */
};

struct display_device {
	struct hw_common common;

	/* Display brightness */
	int (*get_brightness)(int *brightness);
	int (*get_max_brightness)(int *brightness);
	int (*set_brightness)(int brightness);
	int (*set_max_brightness)(int brightness);

	/* Control display state */
	int (*get_state)(enum display_state *state);
	int (*set_state)(enum display_state state);

	/* Control image effect */
	int (*get_image_effect)(enum display_image_effect *effect);
	int (*set_image_effect)(enum display_image_effect effect);

	/* Control panel mode mode */
	int (*get_panel_mode)(enum display_panel_mode *mode);
	int (*set_panel_mode)(enum display_panel_mode mode);
};

#endif
