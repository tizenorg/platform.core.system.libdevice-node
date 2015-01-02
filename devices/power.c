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

static int power_get_prop(int prop, int *val)
{
	switch (prop) {
	case PROP_POWER_CAPACITY:
		return PLUGIN_GET(battery_capacity, val);
	case PROP_POWER_CAPACITY_RAW:
		return PLUGIN_GET(battery_capacity_raw, val);
	case PROP_POWER_CHARGE_FULL:
		return PLUGIN_GET(battery_charge_full, val);
	case PROP_POWER_CHARGE_NOW:
		return PLUGIN_GET(battery_charge_now, val);
	case PROP_POWER_WAKEUP_COUNT:
		return PLUGIN_GET(power_wakeup_count, val);
	case PROP_POWER_PRESENT:
		return PLUGIN_GET(battery_present, val);
	case PROP_POWER_HEALTH:
		return PLUGIN_GET(battery_health, val);
	case PROP_POWER_INSUSPEND_CHARGING_SUPPORT:
		return PLUGIN_GET(battery_support_insuspend_charging, val);
	}

	return -1;
}

static int power_set_prop(int prop, int val)
{
	switch (prop) {
	case PROP_POWER_STATE:
		return PLUGIN_SET(power_state, val);
	case PROP_POWER_WAKEUP_COUNT:
		return PLUGIN_SET(power_wakeup_count, val);
	}

	return -1;
}

static const struct device power = {
	.name     = "power",
	.set_prop = power_set_prop,
	.get_prop = power_get_prop,
	.type     = DEVICE_TYPE_POWER,
};

static void __CONSTRUCTOR__ module_init(void)
{
	add_device(&(power.type));
}

static void __DESTRUCTOR__ module_fini(void)
{
	remove_device(&(power.type));
}
