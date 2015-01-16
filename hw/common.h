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


#ifndef __HW_COMMON_H__
#define __HW_COMMON_H__

#include <stdint.h>

#define MAKE_TAG_CONSTANT(A,B,C,D)	(((A) << 24) | ((B) << 16) | ((C) << 8) | (D))
#define HARDWARE_INFO_TAG	MAKE_TAG_CONSTANT('T','H','I','T')

struct hw_common;
struct hw_info {
	/* unique_id must be initialized to HARDWARE_INFO_TAG */
	uint32_t magic;
	/* HAL version */
	uint16_t hal_version;
	/* device version */
	uint16_t device_version;
	/* device id */
	const char *id;
	/* device name */
	const char *name;
	/* author name */
	const char *author;
	/* module's dso */
	void *dso;
	/* reserved for future use */
	uint32_t reserved[8];
	/* open device */
	int (*open)(struct hw_info *info,
			const char *id, struct hw_common **common);
	/* close device */
	int (*close)(struct hw_common *common);
};

struct hw_common {
	/* indicate to this device information structure */
	struct hw_info *info;
};

#define MAKE_VERSION(maj,min) \
	((((maj) & 0xff) << 8) | ((min) & 0xff))

/**
 * Version of the struct hw_info
 */
#define HARDWARE_INFO_VERSION	MAKE_VERSION(1,0)

/**
 * Name of the hardware info symbolic (Tizen Hardware Info)
 */
#define HARDWARE_INFO_SYM		TizenHwInfo

/**
 * Name of the hardware info symbolic as a string
 */
#define HARDWARE_INFO_SYM_AS_STR	"TizenHwInfo"

int hw_get_info(const char *id, const struct hw_info **info);

#endif
