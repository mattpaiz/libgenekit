#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#define STALE_LIMIT 100 

#define INDEX_MAX 4 
#define INDEX_MIN 8 

#define ERPA_LIMIT 8 
#define ERPA_START 4

#define MAX_POPULATION 100

#define HUMAN_READABLE 1

#define DATA_FAT

//#define CONSTANTS
#define TRIG

#define PROXIMITY 0.0001

#define FILE_ORIGINAL "original.txt"
#define FILE_FITTEST "fittest.txt"

//#define EQU(T) ((3.14159 * cos(T)) * sin(T))
//#define EQU(T) ((3.14159 * cos(T)) * sin(T + 2.22))
#define EQU(T) ((3.14159 * sin(T + 2.82)) / (T))
//#define EQU(T) 3.1415927


/* FITNESS CONSTANTS */

#define FITNESS_POINTS 100

/* TIME CONSTANTS */

#define TIME_OFFSET_LOW  1 
#define TIME_OFFSET_HIGH 10.0 
#define TIME_FACTOR ((TIME_OFFSET_HIGH - TIME_OFFSET_LOW) / ((float)FITNESS_POINTS))

#endif 
