/*
 * deviced
 *
 * Copyright (c) 2012 - 2013 Samsung Electronics Co., Ltd.
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


#ifndef __HAL_COMMON_H__
#define __HAL_COMMON_H__

#define MAKE_TAG_CONSTANT(A,B,C,D)	(((A) << 24) | ((B) << 16) | ((C) << 8) | (D))
#define TIZEN_HARDWARE_DEVICE_TAG	MAKE_TAG_CONSTANT('T','H','D','T')

struct hw_device_t {
	/* unique_id must be initialized to TIZEN_HARDWARE_DEVICE_TAG */
	uint32_t uniqe_id;
	/* device HAL version */
	uint16_t device_hal_version;
	/* device api version */
	uint16_t device_api_version;
	/* device name */
	const char *name;
	/* module's dso */
	void *dso;
	/* reserved for future use */
	uint32_t reserved[4];
	/* open device */
	int (*open)(struct hw_device_t *device);
};

/**
 * Name of the hal_device_info (Tizen Hal Device)
 */
#define HAL_DEVICE_INFO_SYM		TOD

/**
 * Name of the hal_device_info as a string
 */
#define HAL_DEVICE_INFO_SYM_AS_STR	"TOD"

int hw_get_module(const char *id, const struct hw_device_t **device);

#endif
