/* 
 * File:   unittest_utilities.h
 * Author: kevin
 *
 * Created on October 21, 2013, 12:32 PM
 */

#ifndef UNITTEST_UTILITIES_H
#define	UNITTEST_UTILITIES_H

#ifdef	__cplusplus
extern "C" {
#endif

extern unsigned long   utils_start_timer_value;
extern float           utils_get_elapsed_time_ms_value;
extern float           utils_get_elapsed_time_ms_restart_value;
extern unsigned int    utils_elapsed_ms_value;
extern uint64_t        utils_get_elapsed_time_ms_64_value;
extern uint64_t        utils_get_elapsed_time_ms_64_restart_value;

#ifdef	__cplusplus
}
#endif

#endif	/* UNITTEST_UTILITIES_H */

