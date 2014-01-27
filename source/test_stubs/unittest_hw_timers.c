
#include <stdint.h>

#include "bms_hw_timers.h"
int bms_hw_set_timer_cb( unsigned char timerId, uint64_t timeOutMs, TimerCBType timerCB, void *data )
{
    return 0;
}

void bms_hw_enable_timer( int timerId )
{

}

void bms_hw_disable_timer( int timerId )
{

}

unsigned long bms_hw_timers_get_time_ms( unsigned char timerId )
{
    return 0;
}

unsigned long bms_hw_timers_get_max_time_ms( unsigned char timerId )
{
    return 0;
}

unsigned long bms_hw_timers_ticks_to_usec( unsigned char timerId, unsigned long ticks )
{
    return 0;
}

void bms_hw_timers_64bit_timer_cb()
{


}

uint64_t bms_hw_timer_get_time_ms_64()
{

    return 0;
}

uint64_t bms_hw_timers_get_max_time_ms_64()
{

    return 0;
}
