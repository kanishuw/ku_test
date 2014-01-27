/*
 * File:   main.c
 * Author: kevin
 *
 * Created on October 11, 2013, 5:33 AM
 */

#include <stdint.h>

unsigned long   utils_start_timer_value = 0;
float           utils_get_elapsed_time_ms_value = 0.0;
float           utils_get_elapsed_time_ms_restart_value = 0.0f;
unsigned int    utils_elapsed_ms_value = 0;
uint64_t        utils_get_elapsed_time_ms_64_value = 0ull;
uint64_t        utils_get_elapsed_time_ms_64_restart_value = 0ull;

float gElapsed;

void usDelay(unsigned long int delay)
{

}

void BMS_eds_memset( __eds__ void *dest, char val, unsigned int len )
{

}

unsigned long utils_start_timer( unsigned int timerId )
{
    return utils_start_timer_value;
}


float utils_get_elapsed_time_ms( unsigned int timerId, float startTime )
{
    return (gElapsed = utils_get_elapsed_time_ms_value);
}

float utils_get_elapsed_time_ms_restart( unsigned int timerId,  float *startTime  )
{
    return (gElapsed = utils_get_elapsed_time_ms_restart_value);
}

unsigned int utils_elapsed_ms( unsigned int timerId, unsigned long startTime,  unsigned long timeMs )
{
    return (gElapsed = utils_elapsed_ms_value);
}

uint64_t utils_get_elapsed_time_ms_64( uint64_t startTime  )
{
    return (gElapsed = utils_get_elapsed_time_ms_64_value);
}

uint64_t utils_get_elapsed_time_ms_64_restart( uint64_t *startTime )
{
    *startTime = 0;
    return (gElapsed = utils_get_elapsed_time_ms_64_restart_value);
}
