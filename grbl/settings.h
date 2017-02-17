/*
 settings.h - eeprom configuration handling
 Part of Grbl

 Copyright (c) 2011-2016 Sungeun K. Jeon for Gnea Research LLC
 Copyright (c) 2009-2011 Simen Svale Skogsrud

 Grbl is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Grbl is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include "nuts_bolts.h"

#ifndef EEPROM_LINE_SIZE
    #define EEPROM_LINE_SIZE 80
#endif

// Version of the EEPROM data. Will be used to migrate existing data from older versions of Grbl
// when firmware is upgraded. Always stored in byte 0 of eeprom
#define SETTINGS_VERSION 10  // NOTE: Check settings_reset() when moving to next version.

// Define bit flag masks for the boolean settings in settings.flag.
#define BITFLAG_REPORT_INCHES      bit(0)
#define BITFLAG_LASER_MODE         bit(1)
#define BITFLAG_INVERT_ST_ENABLE   bit(2)
#define BITFLAG_HARD_LIMIT_ENABLE  bit(3)
#define BITFLAG_HOMING_ENABLE      bit(4)
#define BITFLAG_SOFT_LIMIT_ENABLE  bit(5)
#define BITFLAG_INVERT_LIMIT_PINS  bit(6)
#define BITFLAG_INVERT_PROBE_PIN   bit(7)

// Define status reporting boolean enable bit flags in settings.status_report_mask
#define BITFLAG_RT_STATUS_POSITION_TYPE     bit(0)
#define BITFLAG_RT_STATUS_BUFFER_STATE      bit(1)

// Define settings restore bitflags.
#define SETTINGS_RESTORE_DEFAULTS      bit(0)
#define SETTINGS_RESTORE_PARAMETERS    bit(1)
#define SETTINGS_RESTORE_STARTUP_LINES bit(2)
#define SETTINGS_RESTORE_BUILD_INFO    bit(3)
#ifndef SETTINGS_RESTORE_ALL
#define SETTINGS_RESTORE_ALL 0xFF // All bitflags

// Define EEPROM memory address location values for Grbl settings and parameters
#define EEPROM_ADDR_GLOBAL         ((uint8_t *)1)
#define EEPROM_ADDR_PARAMETERS     ((uint8_t *)512)
#define EEPROM_ADDR_STARTUP_BLOCK  ((uint8_t *)768)
#define EEPROM_ADDR_BUILD_INFO     ((uint8_t *)942)

// Define EEPROM address indexing for coordinate parameters
#define N_COORDINATE_SYSTEM 6  // Number of supported work coordinate systems (from index 1)
#define SETTING_INDEX_NCOORD N_COORDINATE_SYSTEM+1 // Total number of system stored (from index 0)
// NOTE: Work coordinate indices are (0=G54, 1=G55, ... , 6=G59)
#define SETTING_INDEX_G28    N_COORDINATE_SYSTEM    // Home position 1
#define SETTING_INDEX_G30    N_COORDINATE_SYSTEM+1  // Home position 2
// #define SETTING_INDEX_G92    N_COORDINATE_SYSTEM+2  // Coordinate offset (G92.2,G92.3 not supported)

// Define Grbl axis settings numbering scheme. Starts at START_VAL, every INCREMENT, over N_SETTINGS.
#define AXIS_N_SETTINGS          4
#define AXIS_SETTINGS_START_VAL  100 // NOTE: Reserving settings values >= 100 for axis settings. Up to 255.
#define AXIS_SETTINGS_INCREMENT  10  // Must be greater than the number of axis settings

typedef enum
{
    SETTING_PULSE_MICROSECONDS     = 0,
    SETTING_STEPPER_IDLE_LOCK_TIME = 1,
    SETTING_STEP_INVERT_MASK       = 2,
    SETTING_DIR_INVERT_MASK        = 3,
    SETTING_INVERT_ST_ENABLE       = 4,
    SETTING_INVERT_LIMIT_PINS      = 5,
    SETTING_INVERT_PROBE_PIN       = 6,
    SETTING_STATUS_REPORT_MASK     = 10,
    SETTING_JUNCTION_DEVIATION     = 11,
    SETTING_ARC_TOLERANCE          = 12,
    SETTING_REPORT_INCHES          = 13,
    SETTING_SOFT_LIMIT_ENABLE      = 20,
    SETTING_HARD_LIMIT_ENABLE      = 21,
    SETTING_HOMING_ENABLE          = 22,
    SETTING_HOMING_DIR_MASK        = 23,
    SETTING_HOMING_FEED_RATE       = 24,
    SETTING_HOMING_SEEK_RATE       = 25,
    SETTING_HOMING_DEBOUNCE_DELAY  = 26,
    SETTING_HOMING_PULLOFF         = 27,
    SETTING_RPM_MAX                = 30,
    SETTING_RPM_MIN                = 21,
    SETTING_LASER_MODE             = 32,

    SETTING_STEPS_MM_X             = 100,
    SETTING_STEPS_MM_Y             = 101,
    SETTING_STEPS_MM_Z             = 102,
    SETTING_STEPS_MM_A             = 103,
    SETTING_STEPS_MM_B             = 104,
    SETTING_STEPS_MM_C             = 105,

    SETTING_MAX_RATE_X             = 110,
    SETTING_MAX_RATE_Y             = 111,
    SETTING_MAX_RATE_Z             = 112,
    SETTING_MAX_RATE_A             = 113,
    SETTING_MAX_RATE_B             = 114,
    SETTING_MAX_RATE_C             = 115,

    SETTING_ACCEL_X                = 120,
    SETTING_ACCEL_Y                = 121,
    SETTING_ACCEL_Z                = 122,
    SETTING_ACCEL_A                = 123,
    SETTING_ACCEL_B                = 124,
    SETTING_ACCEL_C                = 125,

    SETTING_MAX_TRAVEL_X           = 130,
    SETTING_MAX_TRAVEL_Y           = 131,
    SETTING_MAX_TRAVEL_Z           = 132,
    SETTING_MAX_TRAVEL_A           = 133,
    SETTING_MAX_TRAVEL_B           = 134,
    SETTING_MAX_TRAVEL_C           = 135,
} setting_t;

// Global persistent settings (Stored from byte EEPROM_ADDR_GLOBAL onwards)
typedef struct
{
    // Axis settings
    float steps_per_mm[N_AXIS];
    float max_rate[N_AXIS];
    float acceleration[N_AXIS];
    float max_travel[N_AXIS];

    // Remaining Grbl settings
    uint8_t pulse_microseconds;
    uint8_t step_invert_mask;
    uint8_t dir_invert_mask;
    uint8_t stepper_idle_lock_time; // If max value 255, steppers do not disable.
    uint8_t status_report_mask; // Mask to indicate desired report data.
    float junction_deviation;
    float arc_tolerance;

    float rpm_max;
    float rpm_min;

    uint8_t flags;  // Contains default boolean settings

    uint8_t homing_dir_mask;
    float homing_feed_rate;
    float homing_seek_rate;
    uint16_t homing_debounce_delay;
    float homing_pulloff;
} settings_t;
extern settings_t settings;

// Initialize the configuration subsystem (load settings from EEPROM)
void settings_init();

// Helper function to clear and restore EEPROM defaults
void settings_restore(uint8_t restore_flag);

// A helper method to set new settings from command line
uint8_t settings_store_global_setting(uint8_t parameter, float value);

// Stores the protocol line variable as a startup line in EEPROM
void settings_store_startup_line(uint8_t n, char *line);

// Reads an EEPROM startup line to the protocol line variable
uint8_t settings_read_startup_line(uint8_t n, char *line);

// Stores build info user-defined string
void settings_store_build_info(char *line);

// Reads build info user-defined string
uint8_t settings_read_build_info(char *line);

// Writes selected coordinate data to EEPROM
void settings_write_coord_data(uint8_t coord_select, float *coord_data);

// Reads selected coordinate data from EEPROM
uint8_t settings_read_coord_data(uint8_t coord_select, float *coord_data);

// Returns the step pin mask according to Grbl's internal axis numbering
uint8_t get_step_pin_mask(uint8_t i);

// Returns the direction pin mask according to Grbl's internal axis numbering
uint8_t get_direction_pin_mask(uint8_t i);

// Returns the limit pin mask according to Grbl's internal axis numbering
uint8_t get_limit_pin_mask(uint8_t i);

#endif /* SETTINGS_H_ */
