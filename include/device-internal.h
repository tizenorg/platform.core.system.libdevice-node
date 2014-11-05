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


#ifndef __DEVICE_INTERNAL_H__
#define __DEVICE_INTERNAL_H__

#include "device-node.h"

#ifndef __CONSTRUCTOR__
#define __CONSTRUCTOR__ __attribute__ ((constructor))
#endif

#ifndef __DESTRUCTOR__
#define __DESTRUCTOR__ __attribute__ ((destructor))
#endif

#define FEATURE_DEVICE_NODE_DLOG
#ifdef FEATURE_DEVICE_NODE_DLOG
#define LOG_TAG "DEVICE_NODE"
#include <dlog.h>
#define _I(fmt, args...)        SLOGI(fmt, ##args)
#define _D(fmt, args...)        SLOGD(fmt, ##args)
#define _E(fmt, args...)        SLOGE(fmt, ##args)
#else
#define _I(x, ...)              do { } while (0)
#define _D(x, ...)              do { } while (0)
#define _E(x, ...)              do { } while (0)
#endif

#define DEVMAN_PLUGIN_PATH  "/usr/lib/libslp_devman_plugin.so"

#ifndef PLUGIN_DEFINE
#define PLUGIN_DEFINE
#define PLUGIN_SYS(node)	plugin_intf->OEM_sys_##node
#define PLUGIN_GET(node)	plugin_intf->OEM_sys_get_##node
#define PLUGIN_SET(node)	plugin_intf->OEM_sys_set_##node
#endif

struct device {
	enum device_type type;
	char *name;
	int (*set_prop) (int property, int val);
	int (*get_prop) (int property, int *val);
};

void add_device(enum device_type *devtype);
void remove_device(enum device_type *devtype);

extern const OEM_sys_devman_plugin_interface *plugin_intf;
extern const OEM_sys_devman_plugin_interface default_plugin;

#endif		/* __DEVICE_INTERNAL_H__ */
