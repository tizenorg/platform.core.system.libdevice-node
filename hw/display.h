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
#define DISPLAY_HARDWARE_DEVICE_VERSION	MAKE_VERSION(0,1)

enum display_state {
	DISPLAY_ON,       /* In use */
	DISPLAY_STANDBY,  /* Blanked, low power */
	DISPLAY_SUSPEND,  /* Blanked, lower power */
	DISPLAY_OFF,      /* Shut off, awaiting activity */
};

enum display_image_quality {
	DISPLAY_IMAGE_QUALITY_STANDARD,     /* No effect */
	DISPLAY_IMAGE_QUALITY_NEGATIVE,     /* Total inversion */
	DISPLAY_IMAGE_QUALITY_GRAYSCALE,    /* Shades of gray and no color */
	DISPLAY_IMAGE_QUALITY_PICTURE,      /* Picture effect */
	DISPLAY_IMAGE_QUALITY_VIDEO,        /* Video effect */
	DISPLAY_IMAGE_QUALITY_MOVIE,        /* Movie effect */
	DISPLAY_IMAGE_QUALITY_BROWSER,      /* Browser effect */
	DISPLAY_IMAGE_QUALITY_WARM,         /* Warm effect */
	DISPLAY_IMAGE_QUALITY_COLD,         /* Cold effect */
	DISPLAY_IMAGE_QUALITY_NATURAL,      /* Natural effect */
};

enum display_panel_effect {
	DISPLAY_PANEL_EFFECT_STANDARD,      /* No effect */
	DISPLAY_PANEL_EFFECT_OUTDOOR,       /* Outdoor effect */
	DISPLAY_PANEL_EFFECT_CONTENTS,      /* Contents adaptive brightness control */
	DISPLAY_PANEL_EFFECT_LOWPOWER,      /* Low power effect */
};

struct display_device {
	struct hw_common common;

	/* The brightness value is 0 to 100. */
	int (*get_brightness)(int *brightness);
	int (*set_brightness)(int brightness);

	/* Control display state */
	int (*get_state)(enum display_state *state);
	int (*set_state)(enum display_state state);

	/* Control image quality */
	int (*get_image_quality)(enum display_image_quality *mode);
	int (*set_image_quality)(enum display_image_quality mode);

	/* Control panel effect mode */
	int (*get_panel_effect)(enum display_panel_effect *mode);
	int (*set_panel_effect)(enum display_panel_effect mode);
};

#endif
