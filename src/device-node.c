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

#define DEVMAN_PLUGIN_PATH  "/usr/lib/libslp_devman_plugin.so"
#define DEFAULT_PLUGIN_PATH  "/usr/lib/libdevice-node-generic.so"

//#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#define container_of(ptr, type, member) ({            \
		 const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
		 (type *)( (char *)__mptr - offsetof(type,member) );})

static GList *dev_head;
static void *oem_handle;
static void *default_handle;
const OEM_sys_devman_plugin_interface *oem_intf;
const OEM_sys_devman_plugin_interface *default_intf;

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
	enum device_type *type = NULL;

	for (elem = dev_head; elem; elem = elem->next) {
		type = elem->data;
		if (*type == devtype)
			break;
	}

	return type;
}

API int device_get_property(enum device_type devtype, int property, int *value)
{
	struct device *dev;
	enum device_type *type;
	int r;

	type = find_device(devtype);
	if (type == NULL) {
		_E("fail to find device(%d)", devtype);
		errno = EPERM;
		return -errno;
	}

	dev = container_of(type, struct device, type);
	if (dev == NULL) {
		_E("fail to find device(%d)", devtype);
		errno = EPERM;
		return -errno;
	}

	if (dev->get_prop == NULL) {
		_E("not support getter function(%s)", dev->name);
		errno = EPERM;
		return -errno;
	}

	r = dev->get_prop(property, value);
	if (r < 0) {
		_E("fail to get property(%s:%d) : %s", dev->name, property, strerror(-r));
		errno = -r;
		return r;
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
		_E("fail to find device(%d)", devtype);
		errno = EPERM;
		return -errno;
	}

	dev = container_of(type, struct device, type);
	if (dev == NULL) {
		_E("fail to find device(%d)", devtype);
		errno = EPERM;
		return -errno;
	}

	if (dev->set_prop == NULL) {
		_E("not support setter function(%s)", dev->name);
		errno = EPERM;
		return -errno;
	}

	r = dev->set_prop(property, value);
	if (r < 0) {
		_E("fail to set property(%s:%d) : %s", dev->name, property, strerror(-r));
		errno = -r;
		return r;
	}

	errno = 0;
	return 0;
}

static const OEM_sys_devman_plugin_interface *get_plugin_intf(const char *path, void **phandle)
{
	const OEM_sys_devman_plugin_interface *(*OEM_sys_get_devman_plugin_interface) ();
	const OEM_sys_devman_plugin_interface *plugin;
	void *handle;
	char *error;

	handle = dlopen(path, RTLD_NOW);
	if ((error = dlerror()) != NULL) {
		_E("dlopen(%s) failed: %s", path, error);
		return NULL;
	}

	OEM_sys_get_devman_plugin_interface = dlsym(handle, "OEM_sys_get_devman_plugin_interface");
	if ((error = dlerror()) != NULL) {
		_E("dlsym() failed: %s", error);
		dlclose(handle);
		return NULL;
	}

	plugin = OEM_sys_get_devman_plugin_interface();
	if (!plugin) {
		_E("get_devman_plugin_interface() failed");
		dlclose(handle);
		return NULL;
	}

	*phandle = handle;
	return plugin;
}

static void __CONSTRUCTOR__ module_init(void)
{
	oem_intf = get_plugin_intf(DEVMAN_PLUGIN_PATH, &oem_handle);
	if (!oem_intf)
		_E("failed to get OEM plugin");

	default_intf = get_plugin_intf(DEFAULT_PLUGIN_PATH, &default_handle);
	if (!default_intf)
		_E("failed to get default plugin");
}

static void __DESTRUCTOR__ module_fini(void)
{
	if (oem_handle)
		dlclose(oem_handle);

	if (default_handle)
		dlclose(default_handle);
}
