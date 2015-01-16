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

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <dlfcn.h>
#include <string.h>
#include <errno.h>
#include <linux/limits.h>

#include <hw/common.h>
#include "device-internal.h"

#ifndef EXPORT
#define EXPORT	__attribute__ ((visibility("default")))
#endif

#define ARRAY_SIZE(name)	(sizeof(name)/sizeof(name[0]))

static const char *module_path[] = {
	/* Searching for external module first */
	LIBPATH"/hw/external",
	LIBPATH"/hw/default",
};

EXPORT
int hw_get_info(const char *id, const struct hw_info_t **info)
{
	char path[PATH_MAX];
	int i;
	void *handle;
	struct hw_info_t *it;

	if (!*info || !id)
		return -EINVAL;

	/* Find matched module path */
	for (i = 0; i < ARRAY_SIZE(module_path); ++i) {
		snprintf(path, sizeof(path),
				"%s/lib%s.so", module_path[i], id);
		if (access(path, R_OK) == 0)
			break;
	}

	if (i == ARRAY_SIZE(module_path))
		return -ENOENT;

	/* Load module */
	handle = dlopen(path, RTLD_NOW);
	if (!handle) {
		_E("fail to open module : %s", dlerror());
		goto error;
	}

	/* Get the address of struct hw_common_t */
	it = dlsym(handle, HARDWARE_INFO_SYM_AS_STR);
	if (!it) {
		_E("fail to find symbol : %s", dlerror());
		goto error;
	}

	/* Check id */
	if (strncmp(id, it->id, strlen(id)) != 0) {
		_E("fail to match id : id(%s), it->id(%s)", id, it->id);
		goto error;
	}

	it->dso = handle;
	*info = it;
	return 0;

error:
	if (handle)
		dlclose(handle);

	return -ENOENT;
}
