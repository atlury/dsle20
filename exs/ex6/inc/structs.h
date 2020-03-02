/*
 * structs.h
 *
 *  Created on: 11/01/2020
 *      Author: gbs
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

/**
 * The mdan_t data structure is used to represent the sensory data related to
 * accelerometers. Such data includes readings from:
 *  -- 1 counter to store the number of readings (cycles);
 *  -- 3 accelerometers (one per axis, X, Y and Z);
 *  -- 3 temperatures from each accelerometer (X, Y and Z);
 *  -- 3 temperatures from V/F converters (X, Y and Z);
 *  -- 4 internal output voltages, 5V from an DC/DC, 15V (DC/DC), -15V (DC/DC)
 *    and a 5V from a regulator;
 *  -- 1 variable to store the spent time between each interrupt;
 */
typedef struct mdan_t
{
  uint32_t count;

  float accel_x;
  float accel_x_temp;
  float vf_x_temp;

  float accel_y;
  float accel_y_temp;
  float vf_y_temp;

  float accel_z;
  float accel_z_temp;
  float vf_z_temp;

  float v_5_ad;
  float v_5_reg;
  float v_15_ad;
  float v_m15_ad;

  float time_ms;
}mdan_t;

/**
 * The gyros_t data structure is used to represent the sensory data related to
 * gyrometers. Such data includes readings from:
 *  -- 1 counter to store the number of readings (cycles);
 *  -- 3 gyrometers (one per axis, X, Y and Z);
 *  -- 3 temperatures from each gyrometer (X, Y and Z);
 *  -- 1 variable to store the spent time between each interrupt;
 */
typedef struct gyros_t
{
  uint32_t count;

  float gyro_x;
  float gyro_x_temp;

  float gyro_y;
  float gyro_y_temp;

  float gyro_z;
  float gyro_z_temp;

  float time_ms;
}gyros_t;

/**
 * A "structure of structures". The sensors_t represents a pack of sensory data,
 * from both, accelerometers and gyrometers. It is used to simplify the logging
 * and telemetry tasks.
 */
typedef struct sensors_t
{
  uint32_t count;
  mdan_t mdan;
  gyros_t gyro;
}sensors_t;


#endif /* STRUCTS_H_ */
