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


#include <stdio.h>
#include "device-internal.h"

static int process_get_prop(int prop, int *val)
{
	switch (prop) {
	case PROP_PROCESS_NODE:
		return PLUGIN_GET(process_monitor_node)((char*)val);
	}

	return -1;
}

static int process_set_prop(int prop, int val)
{
	switch (prop) {
	case PROP_PROCESS_MP_PNP:
		return PLUGIN_SET(process_monitor_mp_pnp)(val);
	case PROP_PROCESS_MP_VIP:
		return PLUGIN_SET(process_monitor_mp_vip)(val);
	}

	return -1;
}

static const struct device process = {
	.name     = "process",
	.set_prop = process_set_prop,
	.get_prop = process_get_prop,
	.type     = DEVICE_TYPE_PROCESS,
};

static void __CONSTRUCTOR__ module_init(void)
{
	add_device(&(process.type));
}

static void __DESTRUCTOR__ module_fini(void)
{
	remove_device(&(process.type));
}
