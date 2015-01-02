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

static int cpu_get_prop(int prop, int *val)
{
	switch (prop) {
	case PROP_CPU_CPUINFO_MAX_FREQ:
		return PLUGIN_GET(cpufreq_cpuinfo_max_freq, val);
	case PROP_CPU_CPUINFO_MIN_FREQ:
		return PLUGIN_GET(cpufreq_cpuinfo_min_freq, val);
	case PROP_CPU_SCALING_MAX_FREQ:
		return PLUGIN_GET(cpufreq_scaling_max_freq, val);
	case PROP_CPU_SCALING_MIN_FREQ:
		return PLUGIN_GET(cpufreq_scaling_min_freq, val);
	}

	return -1;
}

static int cpu_set_prop(int prop, int val)
{
	switch (prop) {
	case PROP_CPU_SCALING_MAX_FREQ:
		return PLUGIN_SET(cpufreq_scaling_max_freq, val);
	case PROP_CPU_SCALING_MIN_FREQ:
		return PLUGIN_SET(cpufreq_scaling_min_freq, val);
	}

	return -1;
}

static const struct device cpu = {
	.name     = "cpu",
	.set_prop = cpu_set_prop,
	.get_prop = cpu_get_prop,
	.type     = DEVICE_TYPE_CPU,
};

static void __CONSTRUCTOR__ module_init(void)
{
	add_device(&(cpu.type));
}

static void __DESTRUCTOR__ module_fini(void)
{
	remove_device(&(cpu.type));
}
