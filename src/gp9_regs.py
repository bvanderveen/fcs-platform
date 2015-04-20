
# File: um6_registers.py
# Purpose: CHR-UM6 register/bit definitions for "creghead" header generator
# Author: Benjamin van der Veen
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


prefix = 'GP9'
regs = [
   # GP9 CONFIGURATION REGISTERS:
   ('CGREG_COM_SETTINGS', 0x00, 32, 'communication settings',
      [
         (None, 4),
         ('SAT',  'detailed satellite status transmission'),
         (None, 3),

         ('GPS', 'send GPS information when received'),
         (None, 7),

         (None, 8),

         (None, 4),
         ('BAUD_RATE', 4, 'serial port baudrate; 000: 9600, 001: 14400, 010: 19200, 011 -> 38400, 100 -> 57600, 101 -> 115200'),
      ]
   ),
   ('CREG_COM_RATES1', 0x01, 32, 'telemetry transmission rates for raw accelerometer, gyro, magnetometer, and pressure data. (8-bits unsigned, 0-255hz)',
      [
         ('RAW_PRESSURE_RATE', 8),
         ('RAW_MAG_RATE', 8),
         ('RAW_GYRO_RATE', 8),
         ('RAW_ACCEL_RATE', 8),
      ]
   ),
   ('CREG_COM_RATES2', 0x02, 32, 'telemetry transmission rates for all raw data and raw temperature. (8-bits unsigned, 0-255hz)',
      [
         ('ALL_RAW_RATE', 8),
         (None, 16),
         ('RAW_TEMP_RATE', 8),
      ]
   ),
   ('CREG_COM_RATES3', 0x03, 32, 'telemetry transmission rates for processed accelerometer, gyro, magnetometer, and pressure data. (8-bits unsigned, 0-255hz)',
      [
         ('PROC_PRESS_RATE', 8),
         ('PROC_MAG_RATE', 8),
         ('PROC_GYRO_RATE', 8),
         ('PROC_ACCEL_RATE', 8),
      ]
   ),
   ('CREG_COM_RATES4', 0x04, 32, 'telemetry transmission rates for all processed data and processed temperature. (8-bits unsigned, 0-255hz)',
      [
         ('ALL_PROC_RATE', 8),

         None,
         None,
         None,
         None,
         None,
         None,
         None,
         None,

         None,
         None,
         None,
         None,
         None,
         None,
         None,
         None,

         ('PROC_TEMP_RATE', 8),
      ]
   ),
   ('CREG_COM_RATES5', 0x05, 32, 'telemetry transmission rates for quaternions, euler angles, position, and velocity estimates. (8-bits unsigned, 0-255hz)',
      [
         ('VELOCITY_RATE', 8),
         ('POSITION_RATE', 8),
         ('EULER_RATE', 8),
         ('QUAT_RATE', 8),
      ]
   ),
   ('CREG_COM_RATES6', 0x06, 32, 'telemetry transmission rates for pose (euler/position packet) and health. (8-bits unsigned, 0-255hz)',
      [
         None,
         None,
         None,
         None,
         None,
         None,
         None,
         None,

         None,
         None,
         None,
         None,
         None,
         None,
         None,
         None,

         ('HEALTH_RATE', 4),
         None,
         None,
         None,
         None,

         ('POSE_RATE', 8)
      ]
   ),
   ('CREG_COM_RATES7', 0x07, 32, 'transmission rates for CHR NMEA-style packets. (4-bits unsigned, see GP9 data sheet)',
      [
         None,
         None,
         None,
         None,
         None,
         None,
         None,
         None,

         None,
         None,
         None,
         None,
         None,
         None,
         None,
         None,

         ('SENSOR_RATE', 4),
         ('ATTITUDE_RATE', 4),
         ('POSE_REATE', 4),
         ('HEALTH_RATE', 4),
      ]
   ),
   ('CGREG_FILTER_SETTINGS', 0x08, 32, 'settings used to configure high-level behavior of the filter',
      [
         (None, 8),
         (None, 8),
         (None, 8),
         (None, 4),
         ('ACC', 'if set, accelerometer will be used to update attitude estimates when GPS lock isn\'t available (default 1)'),
         ('MAG', 'if set, magnetometer will be used to update attitude estimates (default 0)'),
         ('GPS', 'if set, GPS will be used to update attitude estimates (default 1)'),
         None, 
      ]
   ),
   ('CGREG_HOME_NORTH', 0x09, 32),
   ('CGREG_HOME_EAST', 0x0a, 32),
   ('CGREG_HOME_UP', 0x0b, 32),
   ('CGREG_ZERO_PRESSURE', 0x0c, 32),

   ('CREG_GYRO_TRIM_X', 0x0e, 32),
   ('CREG_GYRO_TRIM_Y', 0x0f, 32),
   ('CREG_GYRO_TRIM_Z', 0x10, 32),


   ('CREG_MAG_CAL1_1', 0x42, 32),
   ('CREG_MAG_CAL1_2', 0x43, 32),
   ('CREG_MAG_CAL1_3', 0x44, 32),
   ('CREG_MAG_CAL2_1', 0x45, 32),
   ('CREG_MAG_CAL2_2', 0x46, 32),
   ('CREG_MAG_CAL2_3', 0x47, 32),
   ('CREG_MAG_CAL3_1', 0x48, 32),
   ('CREG_MAG_CAL3_2', 0x49, 32),
   ('CREG_MAG_CAL3_3', 0x4A, 32),

   ('CREG_MAG_BIAS_X', 0x1a, 32),
   ('CREG_MAG_BIAS_Y', 0x1b, 32),
   ('CREG_MAG_BIAS_Z', 0x1c, 32),


   # GP9 DATA REGISTERS:
   ('DREG_HEALTH', 0x55, 32, 'health',
      [
         ('GPS', 'set if GPS fails to send a packet for more than two seconds. cleared if a packet is received.'),
         ('MAG', 'magnetometer init failed'),
         ('GYRO', 'gyro init failed'),
         ('ACCEL', 'accelerometer init failed'),
         ('PRESS', 'pressure sensor init failed'),
         ('GPS_ST', 2, '1 = no lock, 2 = poor lock (GPS unused), 3 = good lock'),
         (None, 2),
         ('OVF', 'set if GP9 attempting to send data faster than baud rate allows'),
         ('SATS_IN_VIEW', 6, 'number of GPS satellites in view'),
         ('HDOP', 10, 'GPS HDOP, actual HDOP value is (contents-of-register / 10)'),
         ('SATS_USED', 6, 'number of satellites used in position solution')
      ]
   ),
   ('DREG_GYRO_RAW1', 0x56, 32,
      [
         ('Y', 16),
         ('X', 16)
      ]
   ),
   ('DREG_GYRO_RAW2', 0x57, 32,
      [
         (None, 16),
         ('Z', 16)
      ]
   ),
   ('DREG_GYRO_RAW_TIME', 0x58, 32),
   ('DREG_ACC_RAW1', 0x59, 32,
      [
         ('Y', 16),
         ('X', 16)
      ]
   ),
   ('DREG_ACC_RAW2', 0x5A, 32,
      [
         (None, 16),
         ('Z', 16)
      ]
   ),
   ('DREG_ACC_RAW_TIME', 0x5b, 32),
   ('DREG_MAG_RAW1', 0x5c, 32,
      [
         ('Y', 16),
         ('X', 16)
      ]
   ),
   ('DREG_MAG_RAW2', 0x5d, 32,
      [
         (None, 16),
         ('Z', 16)
      ]
   ),
   ('DREG_MAG_RAW_TIME', 0x5e, 32),
   ('DREG_PRESSURE_RAW', 0x5f, 32),
   ('DREG_PRESSURE_TIME', 0x60, 32),
   ('DREG_TEMPERATURE_RAW1', 0x61, 32),
   ('DREG_TEMPERATURE_RAW2', 0x62, 32),
   ('DREG_TEMPERATURE_TIME', 0x63, 32),
   ('DREG_GYRO_PROC_X', 0x64, 32),
   ('DREG_GYRO_PROC_Y', 0x65, 32),
   ('DREG_GYRO_PROC_Z', 0x66, 32),
   ('DREG_GYRO_PROC_TIME', 0x67, 32),
   ('DREG_ACCEL_PROC_X', 0x68, 32),
   ('DREG_ACCEL_PROC_Y', 0x69, 32),
   ('DREG_ACCEL_PROC_Z', 0x6a, 32),
   ('DREG_ACCEL_PROC_TIME', 0x6b, 32),
   ('DREG_MAG_PROC_X', 0x6c, 32),
   ('DREG_MAG_PROC_Y', 0x6d, 32),
   ('DREG_MAG_PROC_Z', 0x6e, 32),
   ('DREG_MAG_PROC_TIME', 0x6f, 32),
   ('DREG_PRESSURE_PROC', 0x70, 32),
   ('DREG_PRESSURE_PROC_TIME', 0x71, 32),
   ('DREG_TEMPERATURE_PROC1', 0x72, 32),
   ('DREG_TEMPERATURE_PROC2', 0x73, 32),
   ('DREG_TEMPERATURE_PROC_TIME', 0x74, 32),
   ('DREG_QUAT_AB', 0x75, 32,
      [
         ('B', 16),
         ('A', 16),
      ]
   ),
   ('DREG_QUAT_CD', 0x76, 32,
      [
         ('D', 16),
         ('C', 16),
      ]
   ),
   ('DREG_QUAT_TIME', 0x77, 32),
   ('DREG_EULER_PHI_THETA', 0x78, 32,
      [
         ('THETA', 16),
         ('PHI', 16),
      ]
   ),
   ('DREG_EULER_PSI', 0x79, 32,
      [
         ('PSI', 16),
         (None, 16),
      ]
   ),
   ('DREG_EULER_TIME', 0x7a, 32),
   ('DREG_POSITION_N', 0x7b, 32),
   ('DREG_POSITION_E', 0x7c, 32),
   ('DREG_POSITION_UP', 0x7d, 32),
   ('DREG_POSITION_TIME', 0x7e, 32),
   ('DREG_VELOCITY_N', 0x7f, 32),
   ('DREG_VELOCITY_E', 0x80, 32),
   ('DREG_VELOCITY_UP', 0x81, 32),
   ('DREG_VELOCITY_TIME', 0x82, 32),
   ('DREG_GPS_LATITUDE', 0x83, 32),
   ('DREG_GPS_LONGITUDE', 0x84, 32),
   ('DREG_GPS_ALTITUDE', 0x85, 32),
   ('DREG_GPS_COURSE', 0x86, 32),
   ('DREG_GPS_SPEED', 0x87, 32),
   ('DREG_GPS_TIME', 0x88, 32),
   ('DREG_GPS_DATE', 0x89, 32),
   ('DREG_GPS_SAT_1_2', 0x8a, 32,
      [
         ('SAT2_SNR', 8),
         ('SAT2_ID', 8),
         ('SAT1_SNR', 8),
         ('SAT1_ID', 8),
      ]
   ),
   ('DREG_GPS_SAT_3_4', 0x8b, 32,
      [
         ('SAT4_SNR', 8),
         ('SAT4_ID', 8),
         ('SAT3_SNR', 8),
         ('SAT3_ID', 8),
      ]
   ),
   ('DREG_GPS_SAT_5_6', 0x8c, 32,
      [
         ('SAT6_SNR', 8),
         ('SAT6_ID', 8),
         ('SAT5_SNR', 8),
         ('SAT5_ID', 8),
      ]
   ),
   ('DREG_GPS_SAT_7_8', 0x8d, 32,
      [
         ('SAT8_SNR', 8),
         ('SAT8_ID', 8),
         ('SAT7_SNR', 8),
         ('SAT7_ID', 8),
      ]
   ),
   ('DREG_GPS_SAT_9_10', 0x8e, 32,
      [
         ('SAT10_SNR', 8),
         ('SAT10_ID', 8),
         ('SAT9_SNR', 8),
         ('SAT9_ID', 8),
      ]
   ),
   ('DREG_GPS_SAT_11_12', 0x8f, 32,
      [
         ('SAT12_SNR', 8),
         ('SAT12_ID', 8),
         ('SAT11_SNR', 8),
         ('SAT11_ID', 8),
      ]
   ),
   ('DREG_GYRO_BIAS_X', 0x90, 32),
   ('DREG_GYRO_BIAS_Y', 0x91, 32),
   ('DREG_GYRO_BIAS_Z', 0x92, 32),

   ('DREG_BIAS_X_VARIANCE', 0x93, 32),
   ('DREG_BIAS_Y_VARIANCE', 0x94, 32),
   ('DREG_BIAS_Z_VARIANCE', 0x95, 32),

   ('DREG_QUAT_A_VARIANCE', 0x96, 32),
   ('DREG_QUAT_B_VARIANCE', 0x97, 32),
   ('DREG_QUAT_C_VARIANCE', 0x98, 32),
   ('DREG_QUAT_D_VARIANCE', 0x99, 32),

   ('GET_FW_VERSION', 0xAA, 0),
   ('FLASH_COMMIT', 0xAB, 0),
   ('RESET_TO_FACTORY', 0xAC, 0),
   ('ZERO_GYROS', 0xAD, 0),
   ('SET_HOME_POS', 0xAE, 0),
   ('RESET_EKF', 0xB3, 0),
]

