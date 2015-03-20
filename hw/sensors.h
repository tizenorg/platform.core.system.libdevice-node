/*
 * sensord
 *
 * Copyright (c) 2015 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
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
 *
 */

#ifndef _SENSORS_HAL_INTERFACE_H_
#define _SENSORS_HAL_INTERFACE_H_

#include <hw/common.h>

/* the id of this device */
#define SENSOR_HARDWARE_DEVICE_ID "sensor"
#define SENSOR_HARDWARE_DEVICE_VERSION MAKE_VERSION(0,1)

/**
 * Sensor types
 * These types are used to control the sensors.
 */
enum sensor_type {
	SENSOR_TYPE_METADATA = -2,          /* TODO: Meta Data */
	SENSOR_TYPE_ACCELEROMETER = 1,      /* Accelerometer Sensor*/
	SENSOR_TYPE_GEOMAGNETIC = 2,        /* Geomagnetic Sensor */
	SENSOR_TYPE_TEMPERATURE = 10,       /* Temperature Sensor */
	SENSOR_TYPE_HUMIDITY = 11,          /* Humidity Sensor */

	/*
	 * Base for device manufacturers private sensor types.
	 * These sensor types can't be exposed in the SDK.
	 * if new sensor type should be needed, use this type.
	 */
	SENSOR_TYPE_CUSTOM = 10000,
};

/* Sensor string type */
#define SENSOR_STRING_TYPE_ACCELEROMETER "accelerometer"

/**
 * sensor event data
 *
 * - base unit
 * acceleration values  : meter per second per second (m/s^2)
 * magnetic values      : micro-Tesla (uT)
 * orientation values   : degrees
 * gyroscope values     : degrees/s
 * temperature values   : degrees centigrade
 * proximitiy values    : distance(near or far)
 * light values         : lux
 * pressure values      : hectopascal (hPa)
 * humidity             : relative humidity (%)
 * uncalibrated gyro    : degrees/s
 * uncalibrated mag     : micro-Tesla (uT)
 * heart rate monitor   : bpm/..
 */
struct sensor_event {
	int version; /* version of structure */
	int sensor_handle; /* sensor identifier */
	int type; /* sensor(or data) type */
	int accuracy; /* accuracy */
	int value_count; /* count of values */
	unsigned long long timestamp; /* timestamp */
	float *values;
	float reserved[4];
};

struct sensor_info {
	/* Name of this sensor. */
	const char *name;

	/* vendor of the hardware part */
	const char *vendor;

	/* version of the hardware part */
	int version;

	/* handle that identifies this sensors. this handle Must be unique */
	int handle;

	/* this sensor's type. */
	sensor_type type;

	/* this sensor event type. */
	int event_type;

	/* minimum range of this sensor's value in SI units */
	float min_range;

	/* maximum range of this sensor's value in SI units */
	float max_range;

	/* smallest difference between two values reported by this sensor */
	float resolution;

	/*
	 *   continuous: minimum sample period allowed in microseconds
	 *   on-change : 0
	 *   one-shot  :-1
	 *   special   : 0, unless otherwise noted
	 */
	int min_interval;

	/* number of events reserved for this sensor in the batch mode FIFO.
	 * If there is a dedicated FIFO for this sensor, then this is the
	 * size of this FIFO. If the FIFO is shared with other sensors,
	 * this is the size reserved for that sensor and it can be zero.
	 */
	int fifo_count;

	/* maximum number of events of this sensor that could be batched.
	 * This is especially relevant when the FIFO is shared between
	 * several sensors; this value is then set to the size of that FIFO.
	 */
	int max_batch_count;

	/* permission required to see this sensor, register to it and receive data.
	 * Set to 0 if no permission is required.
	 */
	int permission;

	/* max delay */
	/* This value is defined only for continuous mode and on-change sensors.
	 * It is the delay between two sensor events corresponding to the lowest
	 * frequency that this sensor supports. When lower frequencies are requested
	 * through batch()/setDelay() the events will be generated at this frequency
	 * instead. It can be used by the framework or applications to estimate
	 * when the batch FIFO may be full.
	 */
	int maxDelay;

	void* reserved[7];
};

struct sensor_module {
	/* it must be first*/
	struct hw_common common;

	/*
	 * if there is a something to do during the module is loading,
	 * initialize() is called.
	 */
	int (*initialize)(struct sensor_module *dev);

	/*
	 * Enumerate all available sensor information list of this module.
	 * @param[out]   infos   sensor_info list
	 * @param[out]   count   the count of sensors
	 * @return      @c 0 on success,
	 *              otherwise a negative error value
	 */
	int (*get_sensor_infos)(struct sensor_module *dev, sensor_info **infos, int *count);

	/*
	 * A Handle identifies a given sensors.
	 * The handle is used to enable/disenable sensors in HAL implementation.
	 * This handle must be given from sensor framework becuase it MUST be unique
	 * in the whole of the system. sensor framework will give the all of the sensor
	 * in this module.
	 * NOTE: handle = (idx << SENSOR_INDEX_SHIFT | sensor_type);
	 * @param[in]   info     the information of specific sensor in this module.
	 * @param[in]   handle   the handle given by sensor framework
	 * @return      @c 0 on success,
	 *              otherwise a negative error value
	 */
	int (*set_handle)(struct sensor_module *dev, sensor_info info, int handle);

	/*
	 * Enable/Disable one sensor by using unique handle.
	 * @param[in]   handle    the sensor handle
	 * @param[in]   enabled   enable(1) or disenable(0)
	 * @return      @c 0 on success,
	 *              otherwise a negative error value
	 */
	int (*enable)(struct sensor_module *dev, int handle, int enabled);

	/*
	 * fd should be provided to sensor daemon for polling the event.
	 * @param[in]   handle    the sensor handle
	 * @param[out]  fd        the fd for polling the event in sensor fw
	 * @return      @c 0 on success,
	 *              otherwise a negative error value
	 */
	int (*get_fd)(struct sensor_module *dev, int handle, int *fd);

	/*
	 * Read the most recent sensor data.
	 * @param[in]   handle    the sensor handle
	 * @param[out]  data      the sensor data
	 * @return      @c 0 on success,
	 *              otherwise a negative error value
	 */
	int (*get_sensor_data)(struct sensor_module *dev,
			int handle, sensor_event *data);

	/* TBD:
	int sensor_set_command(struct sensor_module *dev, int handle, const char *cmd);
	*/

	/*
	 * Sets a sensor’s parameters, including sampling frequency and maximum
	 * report latency.
	 * @param[in]   handle                 the sensor handle
	 * @param[in]   flags                  the sensor flags
	 * @param[in]   interval_ns            the interval(ns)
	 * @param[in]   max_report_latency_ns  the max_report_latency(ns)
	 * @return      @c 0 on success,
	 *              otherwise a negative error value
	 */
	int (*batch)(struct sensor_module *dev, int handle, int flags,
			unsigned long long interval_ns, unsigned long long max_report_latency_ns);

	/*
	 * Send flush event to device in order to flush buffer.
	 * @param[in]   handle    the sensor handle
	 * @return      @c 0 on success,
	 *              otherwise a negative error value
	 */
	int (*flush)(struct sensor_module *dev, int handle);

	int (*reserved_fp[8])(void);
};

#endif /* _SENSORS_HAL_INTERFACE_H_ */
