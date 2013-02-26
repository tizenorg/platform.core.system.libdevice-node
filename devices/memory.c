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

static int memory_get_prop(int prop, int *val)
{
	switch (prop) {
	case PROP_MEMORY_NODE:
		return PLUGIN_GET(memnotify_node)((char*)val);
	case PROP_MEMORY_VICTIM_TASK:
		return PLUGIN_GET(memnotify_victim_task)(val);
	}

	return -1;
}

static int memory_set_prop(int prop, int val)
{
	switch (prop) {
	case PROP_MEMORY_THRESHOLD_LV1:
		return PLUGIN_SET(memnotify_threshold_lv1)(val);
	case PROP_MEMORY_THRESHOLD_LV2:
		return PLUGIN_SET(memnotify_threshold_lv2)(val);
	}

	return -1;
}

static const struct device memory = {
	.name     = "memory",
	.set_prop = memory_set_prop,
	.get_prop = memory_get_prop,
	.type     = DEVICE_TYPE_MEMORY,
};

static void __CONSTRUCTOR__ module_init(void)
{
	add_device(&(memory.type));
}

static void __DESTRUCTOR__ module_fini(void)
{
	remove_device(&(memory.type));
}
