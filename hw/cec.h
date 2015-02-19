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

#ifndef __HW_CEC_H__
#define __HW_CEC_H__

#include <hw/common.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * The id of this device
 */
#define CEC_HARDWARE_DEVICE_ID	"cec"

/**
 * The version of this device
 */
#define CEC_HARDWARE_DEVICE_VERSION	MAKE_VERSION(1,0)

/* Maximum length of the CEC message */
#define CEC_MAX_LENGTH		15 /* 16 including the automatically added
				    * address byte. */
#define MAX_NUM_OF_HDMI_PORTS	16
#define CEC_MAX_NUM_LOG_ADDR	4
#define CEC_DEFAULT_TIMEOUT	1000

/*  cec_version: list of CEC versions */
enum cec_version {
	CEC_VER_UNKNOWN,
	CEC_VER_1_0,
	CEC_VER_1_1,
	CEC_VER_1_2,
	CEC_VER_1_3,
	CEC_VER_1_3A,
	CEC_VER_1_3B,
	CEC_VER_1_3C,
	CEC_VER_1_4,
	CEC_VER_1_4B,
	CEC_VER_2_0,
};

enum cec_device_type {
	/* Used internally for error handling */
	CEC_DEVICE_TYPE_EMPTY,
	CEC_DEVICE_TYPE_TV,
	CEC_DEVICE_TYPE_RECORD,
	CEC_DEVICE_TYPE_TUNER,
	CEC_DEVICE_TYPE_PLAYBACK,
	CEC_DEVICE_TYPE_AUDIOSYSTEM,
	CEC_DEVICE_TYPE_SWITCH,
	CEC_DEVICE_TYPE_VIDEOPROC,
};

/* cec_error: list of CEC framework errors */
enum cec_error {
	CEC_OK /* Success */,
	CEC_TIMEOUT /* Timeout occured */,
	CEC_NO_ADDR_LEFT /* No more logical addresses left */,
	CEC_ERROR,
};

/* hdmi_port_info: Information about a HDMI port */
struct hdmi_port_info {
	uint8_t port_number;
};

/* cec_info: a structure used to get information about the CEC device */
struct cec_info {
	/* version: The supported CEC version */
	enum cec_version version;
	/* vendor_id: The vendor ID of the CEC interface */
	uint32_t vendor_id;
	/* ports_num: Number of HDMI ports available in the system */
	unsigned int ports_num;
	/* ports_info: Structure with information about HDMI ports  */
	struct hdmi_port_info ports_info[MAX_NUM_OF_HDMI_PORTS];
};

/* cec_msg: a structure used to store message that were received or are to be
 * sent */
struct cec_buffer {
	/* dst: The address of the destination device */
	uint8_t dst;
	/* src: The address of the source device */
	uint8_t src;
	/* len: The length of the payload of the message */
	uint8_t len;
	/* The payload of the message */
	uint8_t payload[CEC_MAX_LENGTH];
};

struct cec_device;
/* cec_device: a structure used to keep context of the current used CEC device */
struct cec_device {
	struct hw_common common;
	/* caps: pointer to store the capabilities for internal use */
	void *caps;
	/* handle: this is used to keep the file handle to the CEC device */
	int handle;
	int initialised;
	int enabled;
	uint32_t log_addr[CEC_MAX_NUM_LOG_ADDR];
	uint32_t log_addr_type_int[CEC_MAX_NUM_LOG_ADDR];
	enum cec_device_type dev_type[CEC_MAX_NUM_LOG_ADDR];
	uint32_t dev_type_int[CEC_MAX_NUM_LOG_ADDR];
	int num_log_addr;

	/* cec_open:	Open a CEC device
	 * @device:	pointer to a structure that will hold the state of the device
	 * @path:	path to the CEC device
	 * Returns:	on success CEC_OK, on error returns an negative error code
	 */
	int (*cec_open)(struct cec_device *device, char *path);
	/* cec_close:	Close a CEC device
	 * @device:	pointer to a structure that holds the state of the device
	 * Returns:	on success CEC_OK, on error returns an negative error code
	 */
	int (*cec_close)(struct cec_device *device);
	/* cec_info:	Returns information about the CEC device
	 * @device:	pointer to a structure that holds the state of the device
	 * @info:	pointer to a info structure that will hold the information about
	 *		the CEC device
	 * Returns:	on success CEC_OK, on error returns an negative error code
	 */
	int (*cec_get_info)(struct cec_device *device, struct cec_info *info);
	/* cec_is_connected: Return information about whether a device is connected to
	 * the port
	 * @device:	pointer to a structure that holds the state of the device
	 * Returns:	when a device is connected to the port returns CEC_CONNECTED,
	 *		CEC_DISCONNECTED when there is no device connected, on error
	 *		returns an negative error code
	 */
	int (*cec_is_connected)(struct cec_device *device);
	/* cec_send_message: Send a message over the CEC bus
	 * @device:	pointer to a structure that holds the state of the device
	 * @msg:	the message do be sent over the CEC bus
	 * Returns:	CEC_OK on success
	 *		CEC_REPLY on successful send and reply receive
	 *		CEC_REPLY_TIMEOUT when waiting for reply timed out
	 *		CEC_TIMEOUT when a timeout occurred while sending the message
	 *		negative error code on other error
	 */
	int (*cec_send_message)(struct cec_device *device, struct cec_buffer *msg);
	/* cec_receive_message: Receive a message over the CEC bus
	 * @device:	pointer to a structure that holds the state of the device
	 * @msg:	a structure used to store the message received over the CEC bus
	 * Returns:	CEC_OK on success
	 *		CEC_TIMEOUT when a timeout occurred while waiting for message
	 *		negative error code on error
	 * Remarks:	when waiting for a reply, the reply is stored in the msg struct
	 */
	int (*cec_receive_message)(struct cec_device *device, struct cec_buffer *msg);
	/* cec_add_logical_addr: Add a new logical address to the CEC device
	 * @device:	pointer to a structure that holds the state of the device
	 * @type:	the type of the device that is to be added, please note that
	 *		this indicated the type and not the address that will be
	 *		assigned
	 * Returns:	CEC_OK on success
	 *		CEC_TIMEOUT when a timeout occurred while waiting for message
	 *		CEC_NO_ADDR_LEFT when all addresses related to the chosen device
	 *		type are already taken
	 *		negative error code on error
	 */
	int (*cec_add_logical_addr)(struct cec_device *device, enum cec_device_type type, uint8_t *addr);
	/* cec_clear_logical_addrs: Clear the logical addresses that were assigned to
	 * the device
	 * @device:	pointer to a structure that holds the state of the device
	 * Returns:	CEC_OK on success
	 *		CEC_TIMEOUT when a timeout occurred while waiting for message
	 *		negative error code on error
	 */
	int (*cec_clear_logical_addrs)(struct cec_device *device);
	/* cec_get_physical_addr: Get the physical addr of the CEC device
	 * @device:	pointer to a structure that holds the state of the device
	 * @phys_addr:	pointer to a uint16_t which will hold the physicall address
	 * Returns:	CEC_OK on success
	 *		CEC_TIMEOUT when a timeout occurred while waiting for message
	 *		negative error code on error
	 */
	int (*cec_get_physical_addr)(struct cec_device *device, uint16_t *phys_addr);
};

#endif /* __HW_CEC_H__ */
