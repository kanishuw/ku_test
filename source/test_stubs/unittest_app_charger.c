/*
 * unittest_app_charger.c
 *
 * Contains stubs to allow interfacing and controlling the outputs of
 * the routines in bms_app_charger.c
 */

int bms_app_is_charging_value = 0;

void bms_app_charging_initialize()
{

}

int bms_app_is_charging()
{
    return bms_app_is_charging_value;
}

void bms_app_charger_process()
{

}