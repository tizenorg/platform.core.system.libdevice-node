/*
 * libdevice-node
 *
 * Copyright (c) 2016 Samsung Electronics Co., Ltd.
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


#ifndef __HW_USB_CLIENT_H__
#define __HW_USB_CLIENT_H__

#include <hw/common.h>
#include <stdbool.h>

/**
 * The id of this device
 */
#define USB_CLIENT_HARDWARE_DEVICE_ID	"usb_client"

/**
 * The version of this device
 */
#define USB_CLIENT_HARDWARE_DEVICE_VERSION	MAKE_VERSION(0,1)

typedef enum {
	USB_GADGET_NONE			= 0,
	USB_GADGET_MTP			= 1 << 0,
	USB_GADGET_ACM			= 1 << 1,
	USB_GADGET_SDB			= 1 << 2,
	USB_GADGET_RNDIS		= 1 << 3,
	USB_GADGET_DIAG			= 1 << 4,
	USB_GADGET_CONN_GADGET	= 1 << 5,
	USB_GADGET_DM			= 1 << 6,
	USB_GADGET_RMNET		= 1 << 7,
} usb_gadget_e;

static const struct _usb_modes {
	usb_gadget_e mode;
	const char *mode_str;
} usb_modes[] = {
	{ USB_GADGET_NONE,			"none"			},
	{ USB_GADGET_SDB,			"sdb"			},
	{ USB_GADGET_MTP,			"mtp"			},
	{ USB_GADGET_ACM,			"acm"			},
	{ USB_GADGET_RNDIS,			"rndis"			},
	{ USB_GADGET_DIAG,			"diag"			},
	{ USB_GADGET_RMNET,			"rmnet"			},
	{ USB_GADGET_DM,			"dm"			},
	{ USB_GADGET_CONN_GADGET,	"conn_gadget"	},
};

struct usb_client_device {
	struct hw_common common;

	/* Get current gadgets loaded */
	unsigned int (*get_current_gadgets)(void);

	/* Notice if the gadget-composite is availble */
	bool (*gadgets_supported)(unsigned int gadgets);

	bool (*gadgets_enabled)(void);

	/* Initialize gadgets */
	int (*init_gadgets)(unsigned int gadgets);

	/* Deinitialize gadgets */
	int (*deinit_gadgets)(void);

	/* Enable gadgets */
	int (*enable_gadgets)(unsigned int gadgets);

	/* Disable gadgets */
	int (*disable_gadgets)(void);
};

#endif
