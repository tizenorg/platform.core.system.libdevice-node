/*
 * Copyright (c) 2012 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License"),
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/


#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>

#include "devman_plugin_intf.h"

#ifndef DEPRECATED
#define DEPRECATED __attribute__ ((deprecated))
#endif

#ifndef API
#define API __attribute__ ((visibility("default")))
#endif

#define BUF_MAX	255

#define BATTERY_CAPACITY_PATH		"/sys/class/power_supply/battery/capacity"
#define BATTERY_CAPACITY_RAW_PATH	"/sys/class/power_supply/battery/capacity_raw"
#define BATTERY_CHARGE_FULL_PATH	"/sys/class/power_supply/battery/charge_full"
#define BATTERY_CHARGE_NOW_PATH		"/sys/class/power_supply/battery/charge_now"
#define BATTERY_PRESENT_PATH		"/sys/class/power_supply/battery/present"
#define BATTERY_HEALTH_PATH			"/sys/class/power_supply/battery/health"

static int OEM_sys_get_display_count(int *value)
{
	return 0;
}

static int OEM_sys_get_backlight_min_brightness(int index, int *value)
{
	return 0;
}

static int OEM_sys_get_backlight_max_brightness(int index, int *value)
{
	return 0;
}

static int OEM_sys_get_backlight_brightness(int index, int *value, int power_saving)
{
	return 0;
}

static int OEM_sys_set_backlight_brightness(int index, int value, int power_saving)
{
	return 0;
}

static int OEM_sys_set_backlight_dimming(int index, int value)
{
	return 0;
}

static int OEM_sys_get_backlight_acl_control(int index, int *value)
{
	return 0;
}

static int OEM_sys_set_backlight_acl_control(int index, int value)
{
	return 0;
}

static int OEM_sys_get_lcd_power(int index, int *value)
{
	return 0;
}

static int OEM_sys_set_lcd_power(int index, int value)
{
	return 0;
}

static int OEM_sys_get_image_enhance_mode(int *value)
{
	return 0;
}

static int OEM_sys_set_image_enhance_mode(int value)
{
	return 0;
}

static int OEM_sys_get_image_enhance_scenario(int *value)
{
	return 0;
}

static int OEM_sys_set_image_enhance_scenario(int value)
{
	return 0;
}

static int OEM_sys_get_image_enhance_tone(int *value)
{
	return 0;
}

static int OEM_sys_set_image_enhance_tone(int value)
{
	return 0;
}

static int OEM_sys_get_image_enhance_outdoor(int *value)
{
	return 0;
}

static int OEM_sys_set_image_enhance_outdoor(int value)
{
	return 0;
}

static int OEM_sys_get_image_enhance_tune(int *value)
{
	return 0;
}

static int OEM_sys_set_image_enhance_tune(int value)
{
	return 0;
}

static int OEM_sys_image_enhance_info(int *value)
{
	return 0;
}

static int OEM_sys_set_display_frame_rate(int value)
{
	return 0;
}

static int OEM_sys_get_uart_path(int *value)
{
	return 0;
}

static int OEM_sys_set_uart_path(int value)
{
	return 0;
}

static int OEM_sys_get_usb_path(int *value)
{
	return 0;
}

static int OEM_sys_set_usb_path(int value)
{
	return 0;
}

static int OEM_sys_get_haptic_vibetones_level_max(int *value)
{
	return 0;
}

static int OEM_sys_get_haptic_vibetones_level(int *value)
{
	return 0;
}

static int OEM_sys_set_haptic_vibetones_level(int value)
{
	return 0;
}

static int OEM_sys_set_haptic_vibetones_enable(int value)
{
	return 0;
}

static int OEM_sys_set_haptic_vibetones_oneshot(int value)
{
	return 0;
}

static int read_buf(const char *file, char *buf, int size)
{
	int fd, r;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return -errno;

	r = read(fd, buf, size);
	if (r < 0) {
		r = -errno;
		goto out;
	} else if (r >= size) {
		r = -ENOMEM;
		goto out;
	}

	buf[r] = '\0';
	r = 0;

out:
	close(fd);
	return r;
}

static int OEM_sys_get_battery_capacity(int *value)
{
	char buf[BUF_MAX];
	int r;

	r = read_buf(BATTERY_CAPACITY_PATH, buf, sizeof(buf));
	if (r < 0)
		return r;

	*value = atoi(buf);
	return 0;
}

static int OEM_sys_get_battery_capacity_raw(int *value)
{
	char buf[BUF_MAX];
	int r;

	r = read_buf(BATTERY_CAPACITY_RAW_PATH, buf, sizeof(buf));
	if (r < 0)
		return r;

	*value = atoi(buf);
	return 0;
}

static int OEM_sys_get_battery_charge_full(int *value)
{
	char buf[BUF_MAX];
	int r;

	r = read_buf(BATTERY_CHARGE_FULL_PATH, buf, sizeof(buf));
	if (r < 0)
		return r;

	*value = atoi(buf);
	return 0;
}

static int OEM_sys_get_battery_charge_now(int *value)
{
	char buf[BUF_MAX];
	int r;

	r = read_buf(BATTERY_CHARGE_NOW_PATH, buf, sizeof(buf));
	if (r < 0)
		return r;

	*value = atoi(buf);
	return 0;
}

static int OEM_sys_get_battery_present(int *value)
{
	char buf[BUF_MAX];
	int r;

	r = read_buf(BATTERY_PRESENT_PATH, buf, sizeof(buf));
	if (r < 0)
		return r;

	*value = atoi(buf);
	return 0;
}

static const char *health_str[] = {
	[BATTERY_UNKNOWN] = "Unknown",
	[BATTERY_GOOD] = "Good",
	[BATTERY_OVERHEAT] = "Overheat",
	[BATTERY_DEAD] = "Dead",
	[BATTERY_OVERVOLTAGE] = "Over voltage",
	[BATTERY_UNSPECIFIED] = "Unspecified failure",
	[BATTERY_COLD] = "Cold",
};

static int OEM_sys_get_battery_health(int *value)
{
	char buf[BUF_MAX];
	int i, r;

	r = read_buf(BATTERY_CAPACITY_PATH, buf, sizeof(buf));
	if (r < 0)
		return r;

	for (i = 0; i < BATTERY_HEALTH_MAX; ++i) {
		if (!strncmp(buf, health_str[i], strlen(health_str[i]))) {
			*value = i;
			return 0;
		}
	}

	return -EPERM;
}

static int OEM_sys_get_battery_polling_required(int *value)
{
	/* TODO : DEPRECATED */
	return 0;
}

static int OEM_sys_get_battery_support_insuspend_charging(int *value)
{
	/* If the target support to enter the sleep state when charging by ta,
	   this function is returned true. */
	*value = true;
	return 0;
}

static int OEM_sys_get_jack_charger_online(int *value)
{
	return 0;
}

static int OEM_sys_get_jack_earjack_online(int *value)
{
	return 0;
}

static int OEM_sys_get_jack_earkey_online(int *value)
{
	return 0;
}

static int OEM_sys_get_jack_hdmi_online(int *value)
{
	return 0;
}

static int OEM_sys_get_jack_usb_online(int *value)
{
	return 0;
}

static int OEM_sys_get_jack_cradle_online(int *value)
{
	return 0;
}

static int OEM_sys_get_jack_tvout_online(int *value)
{
	return 0;
}

static int OEM_sys_get_jack_keyboard_online(int *value)
{
	return 0;
}

static int OEM_sys_get_leds_torch_max_brightness(int *value)
{
	return 0;
}

static int OEM_sys_get_leds_torch_brightness(int *value)
{
	return 0;
}

static int OEM_sys_set_leds_torch_brightness(int value)
{
	return 0;
}

static int OEM_sys_set_power_state(int value)
{
	return 0;
}

static int OEM_sys_get_power_wakeup_count(int *value)
{
	return 0;
}

static int OEM_sys_set_power_wakeup_count(int value)
{
	return 0;
}

static int OEM_sys_get_memnotify_node(char *node)
{
	return 0;
}

static int OEM_sys_get_memnotify_victim_task(int *value)
{
	return 0;
}

static int OEM_sys_set_memnotify_threshold_lv1(int value)
{
	return 0;
}

static int OEM_sys_set_memnotify_threshold_lv2(int value)
{
	return 0;
}

static int OEM_sys_get_process_monitor_node(char *node)
{
	return 0;
}

static int OEM_sys_set_process_monitor_mp_pnp(int value)
{
	return 0;
}

static int OEM_sys_set_process_monitor_mp_vip(int value)
{
	return 0;
}

static int OEM_sys_get_cpufreq_cpuinfo_max_freq(int *value)
{
	return 0;
}

static int OEM_sys_get_cpufreq_cpuinfo_min_freq(int *value)
{
	return 0;
}

static int OEM_sys_get_cpufreq_scaling_max_freq(int *value)
{
	return 0;
}

static int OEM_sys_set_cpufreq_scaling_max_freq(int value)
{
	return 0;
}

static int OEM_sys_get_cpufreq_scaling_min_freq(int *value)
{
	return 0;
}

static int OEM_sys_set_cpufreq_scaling_min_freq(int value)
{
	return 0;
}

static int OEM_sys_get_backlight_brightness_by_lux(int lux, int *value)
{
	return 0;
}

static int OEM_sys_get_whitemagic_mode(int index, int *value)
{
	return 0;
}

static int OEM_sys_set_whitemagic_mode(int index, int value)
{
	return 0;
}

static int OEM_sys_get_hdmi_support(int *value)
{
	return 0;
}

static int OEM_sys_get_hardkey_backlight(int *value){
	return 0;
}

static int OEM_sys_set_hardkey_backlight(int value){
	return 0;
}


const OEM_sys_devman_plugin_interface default_plugin = {
	/* Light interfaces */
	.OEM_sys_get_display_count = OEM_sys_get_display_count,

	.OEM_sys_get_backlight_min_brightness = OEM_sys_get_backlight_min_brightness,
	.OEM_sys_get_backlight_max_brightness = OEM_sys_get_backlight_max_brightness,
	.OEM_sys_get_backlight_brightness = OEM_sys_get_backlight_brightness,
	.OEM_sys_set_backlight_brightness = OEM_sys_set_backlight_brightness,

	.OEM_sys_set_backlight_dimming = OEM_sys_set_backlight_dimming,

	.OEM_sys_get_backlight_acl_control = OEM_sys_get_backlight_acl_control,
	.OEM_sys_set_backlight_acl_control = OEM_sys_set_backlight_acl_control,

	.OEM_sys_get_lcd_power = OEM_sys_get_lcd_power,
	.OEM_sys_set_lcd_power = OEM_sys_set_lcd_power,

	/* Image Ehnhace interfaces */
	.OEM_sys_get_image_enhance_mode = OEM_sys_get_image_enhance_mode,
	.OEM_sys_set_image_enhance_mode = OEM_sys_set_image_enhance_mode,
	.OEM_sys_get_image_enhance_scenario = OEM_sys_get_image_enhance_scenario,
	.OEM_sys_set_image_enhance_scenario = OEM_sys_set_image_enhance_scenario,
	.OEM_sys_get_image_enhance_tone = OEM_sys_get_image_enhance_tone,
	.OEM_sys_set_image_enhance_tone = OEM_sys_set_image_enhance_tone,
	.OEM_sys_get_image_enhance_outdoor = OEM_sys_get_image_enhance_outdoor,
	.OEM_sys_set_image_enhance_outdoor = OEM_sys_set_image_enhance_outdoor,

	.OEM_sys_get_image_enhance_tune = OEM_sys_get_image_enhance_tune,
	.OEM_sys_set_image_enhance_tune = OEM_sys_set_image_enhance_tune,

	.OEM_sys_image_enhance_info = OEM_sys_image_enhance_info,

	.OEM_sys_set_display_frame_rate = OEM_sys_set_display_frame_rate,

	/* UART path interfaces */
	.OEM_sys_get_uart_path = OEM_sys_get_uart_path,
	.OEM_sys_set_uart_path = OEM_sys_set_uart_path,

	/* USB path interfaces */
	.OEM_sys_get_usb_path = OEM_sys_get_usb_path,
	.OEM_sys_set_usb_path = OEM_sys_set_usb_path,

	/* Vibrator interfaces */
	.OEM_sys_get_haptic_vibetones_level_max = OEM_sys_get_haptic_vibetones_level_max,
	.OEM_sys_get_haptic_vibetones_level = OEM_sys_get_haptic_vibetones_level,
	.OEM_sys_set_haptic_vibetones_level = OEM_sys_set_haptic_vibetones_level,
	.OEM_sys_set_haptic_vibetones_enable = OEM_sys_set_haptic_vibetones_enable,
	.OEM_sys_set_haptic_vibetones_oneshot = OEM_sys_set_haptic_vibetones_oneshot,

	/* Battery interfaces */
	.OEM_sys_get_battery_capacity = OEM_sys_get_battery_capacity,
	.OEM_sys_get_battery_capacity_raw = OEM_sys_get_battery_capacity_raw,
	.OEM_sys_get_battery_charge_full = OEM_sys_get_battery_charge_full,
	.OEM_sys_get_battery_charge_now = OEM_sys_get_battery_charge_now,
	.OEM_sys_get_battery_present = OEM_sys_get_battery_present,
	.OEM_sys_get_battery_health = OEM_sys_get_battery_health,
	.OEM_sys_get_battery_polling_required= OEM_sys_get_battery_polling_required,
	.OEM_sys_get_battery_support_insuspend_charging = OEM_sys_get_battery_support_insuspend_charging,

	/* Connection interfaces  */
	.OEM_sys_get_jack_charger_online = OEM_sys_get_jack_charger_online,
	.OEM_sys_get_jack_earjack_online = OEM_sys_get_jack_earjack_online,
	.OEM_sys_get_jack_earkey_online = OEM_sys_get_jack_earkey_online,
	.OEM_sys_get_jack_hdmi_online = OEM_sys_get_jack_hdmi_online,
	.OEM_sys_get_jack_usb_online = OEM_sys_get_jack_usb_online,
	.OEM_sys_get_jack_cradle_online = OEM_sys_get_jack_cradle_online,
	.OEM_sys_get_jack_tvout_online = OEM_sys_get_jack_tvout_online,
	.OEM_sys_get_jack_keyboard_online = OEM_sys_get_jack_keyboard_online,

	/* Torch interfaces */
	.OEM_sys_get_leds_torch_max_brightness = OEM_sys_get_leds_torch_max_brightness,
	.OEM_sys_get_leds_torch_brightness = OEM_sys_get_leds_torch_brightness,
	.OEM_sys_set_leds_torch_brightness = OEM_sys_set_leds_torch_brightness,

	/* Power management interfaces */
	.OEM_sys_set_power_state = OEM_sys_set_power_state,

	/* TODO: Should determine enum values of wakeup_count nodes */
	.OEM_sys_get_power_wakeup_count = OEM_sys_get_power_wakeup_count,
	.OEM_sys_set_power_wakeup_count = OEM_sys_set_power_wakeup_count,

	/* OOM interfaces */
	.OEM_sys_get_memnotify_node = OEM_sys_get_memnotify_node,
	.OEM_sys_get_memnotify_victim_task = OEM_sys_get_memnotify_victim_task,
	.OEM_sys_set_memnotify_threshold_lv1 = OEM_sys_set_memnotify_threshold_lv1,
	.OEM_sys_set_memnotify_threshold_lv2 = OEM_sys_set_memnotify_threshold_lv2,

	/* Process monitor interfaces */
	.OEM_sys_get_process_monitor_node = OEM_sys_get_process_monitor_node,
	.OEM_sys_set_process_monitor_mp_pnp = OEM_sys_set_process_monitor_mp_pnp,
	.OEM_sys_set_process_monitor_mp_vip = OEM_sys_set_process_monitor_mp_vip,

	/* UART path interfaces */
	.OEM_sys_get_cpufreq_cpuinfo_max_freq = OEM_sys_get_cpufreq_cpuinfo_max_freq,
	.OEM_sys_get_cpufreq_cpuinfo_min_freq = OEM_sys_get_cpufreq_cpuinfo_min_freq,
	.OEM_sys_get_cpufreq_scaling_max_freq = OEM_sys_get_cpufreq_scaling_max_freq,
	.OEM_sys_set_cpufreq_scaling_max_freq = OEM_sys_set_cpufreq_scaling_max_freq,
	.OEM_sys_get_cpufreq_scaling_min_freq = OEM_sys_get_cpufreq_scaling_min_freq,
	.OEM_sys_set_cpufreq_scaling_min_freq = OEM_sys_set_cpufreq_scaling_min_freq,

	.OEM_sys_get_backlight_brightness_by_lux = OEM_sys_get_backlight_brightness_by_lux,

	.OEM_sys_get_whitemagic_mode = OEM_sys_get_whitemagic_mode,
	.OEM_sys_set_whitemagic_mode = OEM_sys_set_whitemagic_mode,

	.OEM_sys_get_hdmi_support = OEM_sys_get_hdmi_support,

	.OEM_sys_get_hardkey_backlight = OEM_sys_get_hardkey_backlight,
	.OEM_sys_set_hardkey_backlight = OEM_sys_set_hardkey_backlight,
};
