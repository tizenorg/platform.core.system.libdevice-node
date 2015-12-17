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


#ifndef __HW_EXTERNAL_CONNECTION_H__
#define __HW_EXTERNAL_CONNECTION_H__

#include <hw/common.h>

/**
 * The id of this device
 */
#define EXTERNAL_CONNECTION_HARDWARE_DEVICE_ID	"external_connection"

#define EXTERNAL_CONNECTION_USB       "USB"
#define EXTERNAL_CONNECTION_USB_HOST  "USB-HOST"
#define EXTERNAL_CONNECTION_TA        "TA"
#define EXTERNAL_CONNECTION_HDMI      "HDMI"
#define EXTERNAL_CONNECTION_DOCK      "Dock"
#define EXTERNAL_CONNECTION_MIC       "Microphone"
#define EXTERNAL_CONNECTION_HEADPHONE "Headphone"

/**
 * The version of this device
 */
#define EXTERNAL_CONNECTION_HARDWARE_DEVICE_VERSION	MAKE_VERSION(0,1)

struct connection_info {
	char *name;
	char *state;
	int flags;
};

typedef void (*ConnectionUpdated)(struct connection_info *info, void *data);

struct external_connection_device {
	struct hw_common common;

	/* Register external_connection event */
	int (*register_changed_event)(ConnectionUpdated updated_cb, void *data);
	void (*unregister_changed_event)(ConnectionUpdated updated_cb);

	/* Get current states */
	int (*get_current_state)(ConnectionUpdated updated_cb, void *data);
};

#endif
