/*
 *   uinttest_bms_app_contactor
 *
 * This unit test validates routines in bms_app_contactor.c.
 *
 * It ensures that if follows the requirements laid out for cell celection
 */

#include <string.h>
#include <stdint.h>

#include "../unittest_utilities.h"
#include "../../bms_defs.h"

extern BMSSystemStatusType      gBatteryStatus;
extern BMSBatterySummaryType    gBatterySummary;
extern CBITFlagsType            gCBITFlags;
extern PBITFlagsType            gPBITFlags;

extern int bms_app_is_charging_value;
extern int bms_app_is_sleeping_value;

extern unsigned char gpio_read_contactor_latch_value;
extern unsigned char gpio_read_forever_power_latch_value;
extern unsigned char gpio_read_charging_fets_value;
extern unsigned char gpio_read_charger_enable_value;
extern int gpio_register_input_value;

extern float bms_hw_cn_get_contactor_voltage_value;
extern float bms_hw_cn_get_fuse_voltage_value;
extern float bms_hw_cn_get_pack_voltage_value;


extern float sStateLastTimeMs;

void bms_app_process_contactor();


/*
 * Tests for the process contactor function
 *
 * 0.  Tests contactor open scenarios.  Each varible is validated individually
 *
 * 1.  Tests the contator open scenario that meets Req BSYS-207
 *
 * 2.  Tests the contactor closure start
 *
 * 3.  Tests the contator closure completed step
 *
 * 4.  Tests that the routine believes that the contactor is closed.
 */
uint8_t bms_app_process_contactor_results[16];
void run_bms_app_process_contactor()
{
    memset( bms_app_process_contactor_results, 0, sizeof( bms_app_process_contactor_results ) );

    /*
     * Test 0.   First set all the variables so that the opening contactor case won't run
     *          Also, none of the other cases should run either.
     *          We test the results by looking at the contactor latch
     *          Normal mode (not reserve)
     */
    gBatteryStatus.bits.key_input_state     = BMS_KEY_STATE_TRANSITION_TO_OFF;
    gBatterySummary.max_cell_voltage        = VCELL_CONTACTOR_ABSOLUTE_MAX;
    gBatterySummary.min_cell_voltage        = VCELL_CONTACTOR_ABSOLUTE_MAX;
    gBatterySummary.pack_current            = IMAX_CONTACTOR_OPEN;
    gBatteryStatus.bits.charger_connected   = CHARGER_NOT_CONNECTED;
    gBatteryStatus.bits.reserve_mode        = RESERVE_MODE_DISABLED;

    bms_app_is_sleeping_value = 0;
    gBatteryStatus.bits.forever_power_mode  = 1;

    //0.1 -- Result: Active
    gpio_read_contactor_latch_value         = 1;       //Should not be rest to zero
    bms_app_process_contactor();
    bms_app_process_contactor_results[0]    = !!gpio_read_contactor_latch_value;

    //0.2 -- Result: Reset
    gBatteryStatus.bits.key_input_state     = BMS_KEY_STATE_OFF;
    gpio_read_contactor_latch_value         = 1;
    utils_get_elapsed_time_ms_value         = 0;
    bms_app_process_contactor();
    bms_app_process_contactor_results[1]    = !!gpio_read_contactor_latch_value;

    //0.2 -- Result: Reset
    gBatteryStatus.bits.key_input_state     = BMS_KEY_STATE_OFF;
    gpio_read_contactor_latch_value         = 1;
    utils_get_elapsed_time_ms_value         = TCONTACTOR_OPEN_MS;
    bms_app_process_contactor();
    bms_app_process_contactor_results[1]    = !gpio_read_contactor_latch_value;

    //0.2 -- Result:  Reset
    gBatteryStatus.bits.key_input_state     = BMS_KEY_STATE_TRANSITION_TO_OFF;
    gBatterySummary.max_cell_voltage        = VCELL_CONTACTOR_ABSOLUTE_MAX+1;
    gpio_read_contactor_latch_value = 1;

    bms_app_process_contactor();
    bms_app_process_contactor_results[2]    = !gpio_read_contactor_latch_value;

    //0.3 -- Result: Reset
    gBatterySummary.max_cell_voltage        = VCELL_CONTACTOR_ABSOLUTE_MAX;
    gBatterySummary.min_cell_voltage        = VCELL_CONTACTOR_NORMAL_MIN-1;
    gpio_read_contactor_latch_value         = 1;

    bms_app_process_contactor();
    bms_app_process_contactor_results[3]    = !gpio_read_contactor_latch_value;

   //0.4 -- Result: Reset
    gBatterySummary.min_cell_voltage        = VCELL_CONTACTOR_NORMAL_MIN;
    gBatterySummary.pack_current            = IMAX_CONTACTOR_OPEN+1;

    gpio_read_contactor_latch_value         = 1;       //Should not be rest to zero

    bms_app_process_contactor();
    bms_app_process_contactor_results[4]    = !gpio_read_contactor_latch_value;

    //0.5 -- Result: Reset
    gBatterySummary.pack_current            = IMAX_CONTACTOR_OPEN;
    gBatteryStatus.bits.charger_connected   = CHARGER_CONNECTED;

    bms_app_process_contactor();
    bms_app_process_contactor_results[5]    = !gpio_read_contactor_latch_value;

    //0.6 -- Result: Reset
    gBatteryStatus.bits.charger_connected   = CHARGER_NOT_CONNECTED;
    bms_app_is_sleeping_value               = 1;

    bms_app_process_contactor();
    bms_app_process_contactor_results[6]    = !gpio_read_contactor_latch_value;

    //0.7 -- Result: Reset
    bms_app_is_sleeping_value               = 0;
    gBatteryStatus.bits.forever_power_mode  = 0;

    bms_app_process_contactor();
    bms_app_process_contactor_results[7]    = !gpio_read_contactor_latch_value;

    gBatteryStatus.bits.forever_power_mode  = 1;


    /*
     * 1.  -- Result:
     *          gpio_read_contactor_latch_value == 0 AND
     *          sStateLastTimeMs == 12345.6789;
     *          gBatteryStatus.bits.contactor_closed == 1
     */

    gBatteryStatus.bits.key_input_state     = BMS_KEY_STATE_TRANSITION_TO_ON;
    gBatteryStatus.bits.forever_power_mode  = 1;
    gBatterySummary.max_cell_voltage        = VCELL_CONTACTOR_ENABLE_MAX -
            ((VCELL_CONTACTOR_ENABLE_MAX-VCELL_CONTACTOR_ENABLE_MIN)/2);

    utils_get_elapsed_time_ms_value         = 0;

    gBatterySummary.min_cell_voltage        = gBatterySummary.max_cell_voltage;
    gpio_read_contactor_latch_value         = 0;
    utils_start_timer_value                 = 12345;
    sStateLastTimeMs                        = 0;
    gBatteryStatus.bits.contactor_closed    = 0;

    bms_app_process_contactor();
    bms_app_process_contactor_results[8]    = !!gpio_read_contactor_latch_value &&
            sStateLastTimeMs == utils_start_timer_value &&
            gBatteryStatus.bits.contactor_closed;


    /* 2.1
     *     This test checks to see that incorrect sense voltages
     * will not allow the transition to on to complete.  Also, it will
     * ensure that faults are not set with a low TCONTACTOR_CLOSED_MS time
     *
     * Expected Results:
     *  BMS_KEY_STATE_TRANSITION_TO_ON == gBatteryStatus.bits.key_input_state
     *  gPBITFlags.bits.contactor_fault = 0
     */
    gBatteryStatus.bits.key_input_state     = BMS_KEY_STATE_TRANSITION_TO_ON;
    gBatteryStatus.bits.forever_power_mode  = 1;
    gpio_read_contactor_latch_value         = 1;
    gPBITFlags.bits.contactor_fault         = 0;
    bms_hw_cn_get_pack_voltage_value        = 53.0;
    bms_hw_cn_get_contactor_voltage_value   = 0.0f;
    bms_hw_cn_get_fuse_voltage_value        = 0.0f;

    utils_get_elapsed_time_ms_value         = TCONTACTOR_CLOSED_MS/4;

    bms_app_process_contactor();

    bms_app_process_contactor_results[3]    = (BMS_KEY_STATE_TRANSITION_TO_ON == gBatteryStatus.bits.key_input_state) &&
            0 == gPBITFlags.bits.contactor_fault;


    /*
     * 2.2
     *  This test checks to see that all of the voltages are checked correctly
     * for the contactor CBIT, we'll do them one at a time.
     *
     *  This is done below the TCONTACTOR_CLOSED_MS threshold, this means that
     * while value are less than what they should be, no faults will be set
     *
     */
    gBatteryStatus.bits.key_input_state     = BMS_KEY_STATE_TRANSITION_TO_ON;
    gBatteryStatus.bits.forever_power_mode  = 1;
    gpio_read_contactor_latch_value         = 1;
    gPBITFlags.bits.contactor_fault         = 0;
    bms_hw_cn_get_pack_voltage_value        = 53.0;
    bms_hw_cn_get_contactor_voltage_value   = bms_hw_cn_get_pack_voltage_value;
    bms_hw_cn_get_fuse_voltage_value        = 0.0f;

    utils_get_elapsed_time_ms_value         = TCONTACTOR_CLOSED_MS/2;

    bms_app_process_contactor();

    bms_app_process_contactor_results[3]    = (BMS_KEY_STATE_TRANSITION_TO_ON == gBatteryStatus.bits.key_input_state) &&
            0 == gPBITFlags.bits.contactor_fault;

    bms_hw_cn_get_contactor_voltage_value   = 0.0f;
    bms_hw_cn_get_fuse_voltage_value        = bms_hw_cn_get_pack_voltage_value;

    bms_app_process_contactor();

    bms_app_process_contactor_results[3]    = (BMS_KEY_STATE_TRANSITION_TO_ON == gBatteryStatus.bits.key_input_state) &&
            0 == gPBITFlags.bits.contactor_fault;

    //Now the transition should occur

    bms_hw_cn_get_contactor_voltage_value   = bms_hw_cn_get_pack_voltage_value;
    bms_hw_cn_get_fuse_voltage_value        = bms_hw_cn_get_pack_voltage_value;

    bms_app_process_contactor();

    bms_app_process_contactor_results[3]    = (BMS_KEY_STATE_ON == gBatteryStatus.bits.key_input_state) &&
            0 == gPBITFlags.bits.contactor_fault;

    /*
     * 2.3
     *  This test checks to see that all of the voltages are checked correctly
     * for the contactor CBIT, we'll do them one at a time.  Specifically:
     *
     *  This is done above the TCONTACTOR_CLOSED_MS threshold, this means that
     * values less than what they should be, faults *will* be set
     */

    gBatteryStatus.bits.key_input_state     = BMS_KEY_STATE_TRANSITION_TO_ON;
    gBatteryStatus.bits.forever_power_mode  = 1;
    gpio_read_contactor_latch_value         = 1;
    gPBITFlags.bits.contactor_fault         = 0;
    bms_hw_cn_get_pack_voltage_value        = 53.0;
    bms_hw_cn_get_contactor_voltage_value   = bms_hw_cn_get_pack_voltage_value-(VDIFF_PACK_CONTACTOR+1);
    bms_hw_cn_get_fuse_voltage_value        = bms_hw_cn_get_pack_voltage_value-(VDIFF_PACK_FUSE+1);

    utils_get_elapsed_time_ms_value         = TCONTACTOR_CLOSED_MS+1;

    bms_app_process_contactor();

    bms_app_process_contactor_results[3]    = (BMS_KEY_STATE_TRANSITION_TO_ON == gBatteryStatus.bits.key_input_state) &&
            1 == gPBITFlags.bits.contactor_fault;

    //This should put us in an ON state
    gBatteryStatus.bits.key_input_state     = BMS_KEY_STATE_TRANSITION_TO_ON;
    gBatteryStatus.bits.forever_power_mode  = 1;
    gpio_read_contactor_latch_value         = 1;
    gPBITFlags.bits.contactor_fault         = 0;
    bms_hw_cn_get_pack_voltage_value        = 53.0;
    bms_hw_cn_get_contactor_voltage_value   = bms_hw_cn_get_pack_voltage_value-VDIFF_PACK_CONTACTOR;
    bms_hw_cn_get_fuse_voltage_value        = bms_hw_cn_get_pack_voltage_value-VDIFF_PACK_FUSE;

    utils_get_elapsed_time_ms_value         = TCONTACTOR_CLOSED_MS+1;

    bms_app_process_contactor();

    bms_app_process_contactor_results[3]    = (BMS_KEY_STATE_ON == gBatteryStatus.bits.key_input_state) &&
            0 == gPBITFlags.bits.contactor_fault;
}
