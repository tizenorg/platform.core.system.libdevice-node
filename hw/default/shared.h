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


#ifndef __HW_DEFAULT_SHARED_H__
#define __HW_DEFAULT_SHARED_H__

#ifndef EXPORT
#define EXPORT	__attribute__ ((visibility("default")))
#endif

int sys_get_int(char *fname, int *val);
int sys_get_str(char *fname, char *str, int len);
int sys_set_int(char *fname, int val);
int sys_set_str(char *fname, char *val);

#endif
