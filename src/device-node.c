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


#include <string.h>
#include <glib.h>
#include <dlfcn.h>
#include <errno.h>
#include "device-internal.h"

//#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#define container_of(ptr, type, member) ({            \
		 const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
		 (type *)( (char *)__mptr - offsetof(type,member) );})

static GList *dev_head;
static void *dlopen_handle;
const OEM_sys_devman_plugin_interface *plugin_intf;

void add_device(const enum device_type *devtype)
{
	dev_head = g_list_append(dev_head, (enum device_type*)devtype);
}

void remove_device(const enum device_type *devtype)
{
	dev_head = g_list_remove(dev_head, (enum device_type*)devtype);
}

static enum device_type *find_device(enum device_type devtype)
{
	GList *elem;
	enum device_type *type;

	for (elem = dev_head; elem; elem = elem->next) {
		type = elem->data;
		if (*type == devtype)
			return type;
	}

	return NULL;
}

API int device_get_property(enum device_type devtype, int property, int *value)
{
	struct device *dev;
	enum device_type *type;
	int r;

	type = find_device(devtype);
	if (type == NULL) {
		_E("devtype cannot find");
		errno = EPERM;
		return -1;
	}

	dev = container_of(type, struct device, type);
	if (dev == NULL) {
		_E("device cannot find");
		errno = EPERM;
		return -1;
	}

	if (dev->get_prop == NULL) {
		_E("devtype doesn't have getter function");
		errno = EPERM;
		return -1;
	}

	r = dev->get_prop(property, value);
	if (r == -ENODEV) {
		_E("Not support driver");
		errno = ENODEV;
		return -1;
	} else if (r == -1) {
		_E("get_prop of %s(%d) return failes", dev->name, property);
		errno = EPERM;
		return -1;
	}

	errno = 0;
	return 0;
}

API int device_set_property(enum device_type devtype, int property, int value)
{
	enum device_type *type;
	struct device *dev;
	int r;

	type = find_device(devtype);
	if (type == NULL) {
		_E("devtype cannot find");
		errno = EPERM;
		return -1;
	}

	dev = container_of(type, struct device, type);
	if (dev == NULL) {
		_E("device cannot find");
		errno = EPERM;
		return -1;
	}

	if (dev->set_prop == NULL) {
		_E("devtype doesn't have setter function");
		errno = EPERM;
		return -1;
	}

	r = dev->set_prop(property, value);
	if (r == -ENODEV) {
		_E("Not support driver");
		errno = ENODEV;
		return -1;
	} else if (r == -1) {
		_E("set_prop of %s(%d) return failes", dev->name, property);
		errno = EPERM;
		return -1;
	}

	errno = 0;
	return 0;
}

static void __CONSTRUCTOR__ module_init(void)
{
	const OEM_sys_devman_plugin_interface *(*OEM_sys_get_devman_plugin_interface) ();
	char *error;

	dlopen_handle = dlopen(DEVMAN_PLUGIN_PATH, RTLD_NOW);
	if (!dlopen_handle) {
		_E("dlopen() failed");
		goto ERROR;
	}

	OEM_sys_get_devman_plugin_interface = dlsym(dlopen_handle, "OEM_sys_get_devman_plugin_interface");
	if ((error = dlerror()) != NULL) {
		_E("dlsym() failed: %s", error);
		goto ERROR;
	}

	plugin_intf = OEM_sys_get_devman_plugin_interface();
	if (!plugin_intf) {
		_E("get_devman_plugin_interface() failed");
		goto ERROR;
	}

	return;

ERROR:
	plugin_intf = &default_plugin;

	if (dlopen_handle)
		dlclose(dlopen_handle);
}

static void __DESTRUCTOR__ module_fini(void)
{
	if (dlopen_handle)
		dlclose(dlopen_handle);
}
