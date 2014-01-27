/*
 * unittest_app_sleep.c
 *
 * Contains stubs to allow interfacing and controlling the outputs of
 * the routines in bms_app_charger.c
 */

int bms_app_is_sleeping_value = 0;

int bms_app_is_sleeping()
{
    return bms_app_is_sleeping_value;
}

