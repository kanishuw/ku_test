/*
 *   uinttest_bms_app_charger
 *
 * This unit test validates routines in bms_app_charger.c.
 *
 * It ensures that if follows the requirements laid out for cell celection
 */

#include <string.h>
#include "bms_defs.h"

#include "../unittest_utilities.h"

#include "../../bms_app_charger.c"


/* Testing the state chaning function
 * 0.  All variables are set such that the 
 *     routine returns BMS_CHARGER_CHARGING_ENABLED
 *
 * 1.  max_cell_voltage > VCELL_MAX_CHARGE-VCELL_VOLTAGE_IMBALANCE_HYSTERESIS
 *     AND max_cell_voltage <= VCELL_MAX_CHARGE
 *     AND !Hysterisis
 *     Result: BMS_CHARGER_CHARGING_ENABLED
 * 
 * 2.  max_cell_voltage > VCELL_MAX_CHARGE
 *     AND !Hysterisis
 *     AND !sDelayStateRequested
 *     Result: BMS_CHARGER_DELAYED
 *             Hysterisis is set  
 * 
 * 3.  max_cell_voltage > VCELL_MAX_CHARGE
 *     AND !Hysterisis
 *     AND sDelayStateRequested
 *     Result: BMS_CHARGER_IDLE
 * 
 * 4.  max_cell_voltage > VCELL_MAX_CHARGE-VCELL_VOLTAGE_IMBALANCE_HYSTERESIS
 *      AND max_cell_voltage <= VCELL_MAX_CHARGE
 *      AND Hysterisis 
 *      AND sDelayStateRequested 
 *     Result: BMS_CHARGER_CHARGING_IDLE
 * 
 * 5.  max_cell_voltage > VCELL_MAX_CHARGE-VCELL_VOLTAGE_IMBALANCE_HYSTERESIS
 *      AND Hysterisis 
 *      AND !sDelayStateRequested 
 *     Result: BMS_CHARGER_CHARGING_DELAYED
 * 
 * 6.  max_cell_voltage <= VCELL_MAX_CHARGE-VCELL_VOLTAGE_IMBALANCE_HYSTERESIS
 *     Result: BMS_CHARGER_CHARGING_ENABLED
 *             !Hysterisis
 * 
 * 7.  gBatterySummary.pack_current < ICHARGE_MAX_ZERO_CURRENT_NEG
 *       OR > ICHARGE_MAX_ZERO_CURRENT_POS 
 *     Result: BMS_CHARGER_CHARGING_ENABLED **NOTE:  This may be an issue, do 
 * we really want an enable when there is current flowing?  Is there a case here 
 * where the charger will enable erroniously?  Created an Issue BSD-82 to track this
 * 
 * 8.  gBatterySummary.pack_current == 0
 *     AND sZeroCurrentTimerDelaySeconds > TCHARGE_ZERO_CURRENT_SETTLING_TIME_SECONDS
 *     AND !sDelayStateRequested
 *     Result: BMS_CHARGER_CHARGING_DELAYED 
 *         AND sDelayStateRequested
 * 
 * 9.  gBatterySummary.pack_current == 0
 *     AND sZeroCurrentTimerDelaySeconds > TCHARGE_ZERO_CURRENT_SETTLING_TIME_SECONDS
 *     AND sDelayStateRequested
 *     Result: BMS_CHARGER_CHARGING_IDLE 
 *          AND sDelayStateRequested
 *          
 * 10. gBatterySummary.max_core_temperature <= TPCHARGER_CELL_MAX_LIMIT
 *    AND gBatterySummary.min_core_temperature >= TPCHARGER_CELL_MIN_LIMIT   
 *    Result: BMS_CHARGER_CHARGING_ENABLED  
 * 
 * 11.  gBatterySummary.max_core_temperature > TPCHARGER_CELL_MAX_LIMIT
 *      AND gBatterySummary.min_core_temperature >= TPCHARGER_CELL_MIN_LIMIT
 *      AND !sDelayStateRequested
 *      Result: BMS_CHARGER_CHARGING_DELAYED
 *          AND sDelayStateRequested
 *    
 * 12.  gBatterySummary.max_core_temperature <= TPCHARGER_CELL_MAX_LIMIT
 *      AND gBatterySummary.min_core_temperature < TPCHARGER_CELL_MIN_LIMIT
 *      AND !sDelayStateRequested
 *      Result: BMS_CHARGER_CHARGING_DELAYED
 *          AND sDelayStateRequested
 * 
 * 13.  VPACK_MAX_CHARGE > VPACK_START_CHARGE
 *      Result: True
 * 
 * 14.  gBatterySummary.pack_voltage < VPACK_MAX_CHARGE
 *      AND !Hysterisis
 *      Result: BMS_CHARGER_CHARGING_ENABLED
 * 
 * 15.  gBatterySummary.pack_voltage >= VPACK_MAX_CHARGE
 *      AND Hysterisis
 *      Result: BMS_CHARGER_CHARGING_IDLE
 *          AND Hysterisis
 * 
 * 16.  gBatterySummary.pack_voltage < VPACK_MAX_CHARGE
 *      AND gBatterySummary.pack_voltage >= VPACK_START_CHARGE
 *      AND Hysterisis
 *      Result: BMS_CHARGER_CHARGING_IDLE
 *
 * 17.  gBatterySummary.pack_voltage < VPACK_START_CHARGE
 *      AND Hysterisis
 *      Result: BMS_CHARGER_CHARGING_ENABLED
 *          AND !Hysterisis
 * 
 * 18.  gBatterySummary.pack_current < ICHARGE_PACK_MAX
 *      Result:" BMS_CHARGER_CHARGING_SHUTDOWN
 * 
 * 19.  gBatterySummary.pack_current > ICHARGE_PACK_MIN
 *      Result: BMS_CHARGER_CHARGING_SHUTDOWN
 *
 * 20.  gBatterySummary.pack_current < ICHARGE_PACK_MIN
 *      Result: BMS_CHARGER_CHARGING_ENABLED
 *
 * 21.  sAmpHourAccumilator > IHCHARGE_MAX
 *      Result: BMS_CHARGER_CHARGING_SHUTDOWN
 * 
 * 22.  sChargerTimerSeconds > TCHARGE_MAX_SECONDS
 *      Result: BMS_CHARGER_CHARGING_SHUTDOWN
 */

uint8_t unittest_determine_next_charger_state_results[23];
void run_determine_next_charger_state_test()
{
    /*Test 0
     * First of all set up the variables and
     * conditions so that we get an enable, then we'll
     * venture into testing individual cases
     */
    memset( unittest_determine_next_charger_state_results, 0, sizeof( unittest_determine_next_charger_state_results ) );
    memset( sHysterisisHigh, 0, sizeof( sHysterisisHigh ) );
    sDelayStateRequested = 0;
    gBatterySummary.max_cell_voltage = VCELL_MAX_CHARGE-VCELL_VOLTAGE_IMBALANCE_HYSTERESIS-0.200f;
    gBatterySummary.pack_current = -5.0f;
    gBatterySummary.max_core_temperature = TPCHARGER_CELL_MAX_LIMIT-10.0f;
    gBatterySummary.min_core_temperature = TPCHARGER_CELL_MIN_LIMIT+10.0f;
    gBatterySummary.pack_voltage = VPACK_MAX_CHARGE-10.0f;
    gBatterySummary.pack_current = 0;
    sAmpHourAccumilator = 0;
    sChargerTimerSeconds = 0;

    unittest_determine_next_charger_state_results[0] = 
            bms_app_determine_next_charger_state() == BMS_CHARGER_CHARGING_ENABLED;

    /* 1.  max_cell_voltage > VCELL_MAX_CHARGE-VCELL_VOLTAGE_IMBALANCE_HYSTERESIS
     *     AND max_cell_voltage <= VCELL_MAX_CHARGE
     *     AND !Hysterisis
     *     Result: BMS_CHARGER_CHARGING_ENABLED
     */
    gBatterySummary.max_cell_voltage = VCELL_MAX_CHARGE-VCELL_VOLTAGE_IMBALANCE_HYSTERESIS+
                                        (VCELL_VOLTAGE_IMBALANCE_HYSTERESIS/2);
    sHysterisisHigh[BMS_CHARGER_HYSTERISIS_CELL_VMAX] = 0;

    unittest_determine_next_charger_state_results[1] = 
            (bms_app_determine_next_charger_state() == BMS_CHARGER_CHARGING_ENABLED);

    /* 2.  max_cell_voltage > VCELL_MAX_CHARGE
     *     AND !Hysterisis
     *     AND !sDelayStateRequested
     *     Result: BMS_CHARGER_DELAYED
     *             Hysterisis is set
     */
    sHysterisisHigh[BMS_CHARGER_HYSTERISIS_CELL_VMAX] = 0;
    sDelayStateRequested = 0;
    gBatterySummary.max_cell_voltage = VCELL_MAX_CHARGE + 0.200f;
    unittest_determine_next_charger_state_results[2] = 
            (bms_app_determine_next_charger_state() == BMS_CHARGER_CHARGING_DELAYED &&
             sHysterisisHigh[BMS_CHARGER_HYSTERISIS_CELL_VMAX]);

    /*
     * 3.  max_cell_voltage > VCELL_MAX_CHARGE
     *     AND !Hysterisis
     *     AND sDelayStateRequested (from last test)
     *     Result: BMS_CHARGER_IDLE
     *        AND Hysterisis
     *        AND sDelayStateRequested
     */
    sHysterisisHigh[BMS_CHARGER_HYSTERISIS_CELL_VMAX] = 0;
    unittest_determine_next_charger_state_results[3] =
            (bms_app_determine_next_charger_state() == BMS_CHARGER_CHARGING_IDLE) &&
            sHysterisisHigh[BMS_CHARGER_HYSTERISIS_CELL_VMAX] &&
            sDelayStateRequested;


    /* 4.  max_cell_voltage > VCELL_MAX_CHARGE-VCELL_VOLTAGE_IMBALANCE_HYSTERESIS
     *      AND max_cell_voltage <= VCELL_MAX_CHARGE
     *      AND Hysterisis  (set via last test)
     *      AND sDelayStateRequested (set via last test)
     *     Result: BMS_CHARGER_CHARGING_IDLE
     */
    gBatterySummary.max_cell_voltage = VCELL_MAX_CHARGE-VCELL_VOLTAGE_IMBALANCE_HYSTERESIS+
                            (VCELL_VOLTAGE_IMBALANCE_HYSTERESIS/2);

    unittest_determine_next_charger_state_results[4] =
            (bms_app_determine_next_charger_state() == BMS_CHARGER_CHARGING_IDLE) &&
            sHysterisisHigh[BMS_CHARGER_HYSTERISIS_CELL_VMAX] &&
            sDelayStateRequested;

    /* 5.  max_cell_voltage > VCELL_MAX_CHARGE-VCELL_VOLTAGE_IMBALANCE_HYSTERESIS
     *      AND Hysterisis (from last test)
     *      AND !sDelayStateRequested
     *     Result: BMS_CHARGER_CHARGING_DELAYED
     */
    gBatterySummary.max_cell_voltage = VCELL_MAX_CHARGE-VCELL_VOLTAGE_IMBALANCE_HYSTERESIS+
                        (VCELL_VOLTAGE_IMBALANCE_HYSTERESIS/2);

    sDelayStateRequested = 0;
    unittest_determine_next_charger_state_results[5] =
            (bms_app_determine_next_charger_state() == BMS_CHARGER_CHARGING_DELAYED) &&
            sHysterisisHigh[BMS_CHARGER_HYSTERISIS_CELL_VMAX] &&
            sDelayStateRequested;



     /* 6.  max_cell_voltage <= VCELL_MAX_CHARGE-VCELL_VOLTAGE_IMBALANCE_HYSTERESIS
      *     Result: BMS_CHARGER_CHARGING_ENABLED
      *             !Hysterisis
      */
    gBatterySummary.max_cell_voltage = VCELL_MAX_CHARGE-VCELL_VOLTAGE_IMBALANCE_HYSTERESIS-0.001f;
    unittest_determine_next_charger_state_results[6] =
            (bms_app_determine_next_charger_state() == BMS_CHARGER_CHARGING_ENABLED) &&
            !sHysterisisHigh[BMS_CHARGER_HYSTERISIS_CELL_VMAX];


     /* 7.  gBatterySummary.pack_current < ICHARGE_MAX_ZERO_CURRENT_NEG
      *       OR > ICHARGE_MAX_ZERO_CURRENT_POS
      *     Result: BMS_CHARGER_CHARGING_ENABLED **NOTE:  This may be an issue, do
      * we really want an enable when there is current flowing?  Is there a case here
      * where the charger will enable erroniously?  Created an Issue BSD-82 to track this
      */
    gBatterySummary.pack_current = ICHARGE_MAX_ZERO_CURRENT_NEG-1;
    unittest_determine_next_charger_state_results[7] =
            (bms_app_determine_next_charger_state() == BMS_CHARGER_CHARGING_ENABLED);

    /* 8.  gBatterySummary.pack_current == 0
     *     AND sZeroCurrentTimerDelaySeconds > TCHARGE_ZERO_CURRENT_SETTLING_TIME_SECONDS
     *     AND !sDelayStateRequested
     *     Result: BMS_CHARGER_CHARGING_DELAYED
     *         AND sDelayStateRequested
     */
    gBatterySummary.pack_current = 0;
    sZeroCurrentTimerDelaySeconds = TCHARGE_ZERO_CURRENT_SETTLING_TIME_SECONDS-1;
    utils_get_elapsed_time_ms_64_restart_value = 1500;
    unittest_determine_next_charger_state_results[8] =
            (bms_app_determine_next_charger_state() == BMS_CHARGER_CHARGING_DELAYED) &&
            sDelayStateRequested;

    /* 9.  gBatterySummary.pack_current == 0
     *     AND sZeroCurrentTimerDelaySeconds > TCHARGE_ZERO_CURRENT_SETTLING_TIME_SECONDS
     *     AND sDelayStateRequested  (set by last test)
     *     Result: BMS_CHARGER_CHARGING_IDLE
     *          AND sDelayStateRequested
     */
    gBatterySummary.pack_current = 0;
    sZeroCurrentTimerDelaySeconds = TCHARGE_ZERO_CURRENT_SETTLING_TIME_SECONDS-1;
    utils_get_elapsed_time_ms_64_restart_value = 1500;
    unittest_determine_next_charger_state_results[9] =
            (bms_app_determine_next_charger_state() == BMS_CHARGER_CHARGING_IDLE) &&
            sDelayStateRequested;

    /* 10. gBatterySummary.max_core_temperature <= TPCHARGER_CELL_MAX_LIMIT
     *    AND gBatterySummary.min_core_temperature >= TPCHARGER_CELL_MIN_LIMIT
     *    Result: BMS_CHARGER_CHARGING_ENABLED
     */
    gBatterySummary.max_core_temperature = TPCHARGER_CELL_MAX_LIMIT - 10.0f;
    gBatterySummary.min_core_temperature = TPCHARGER_CELL_MIN_LIMIT + 10.0f;
    unittest_determine_next_charger_state_results[10] =
            (bms_app_determine_next_charger_state() == BMS_CHARGER_CHARGING_ENABLED);



    /* 11.  gBatterySummary.max_core_temperature > TPCHARGER_CELL_MAX_LIMIT
     *      AND gBatterySummary.min_core_temperature >= TPCHARGER_CELL_MIN_LIMIT
     *      AND !sDelayStateRequested
     *      Result: BMS_CHARGER_CHARGING_DELAYED
     *          AND sDelayStateRequested
     */
    gBatterySummary.max_core_temperature = TPCHARGER_CELL_MAX_LIMIT + 1.0f;
    gBatterySummary.min_core_temperature = TPCHARGER_CELL_MIN_LIMIT + 10.0f;
    sDelayStateRequested = 0;
    unittest_determine_next_charger_state_results[11] =
            (bms_app_determine_next_charger_state() == BMS_CHARGER_CHARGING_DELAYED);

    /* 12.  gBatterySummary.max_core_temperature <= TPCHARGER_CELL_MAX_LIMIT
     *      AND gBatterySummary.min_core_temperature < TPCHARGER_CELL_MIN_LIMIT
     *      AND !sDelayStateRequested
     *      Result: BMS_CHARGER_CHARGING_DELAYED
     *          AND sDelayStateRequested
     */
    gBatterySummary.max_core_temperature = TPCHARGER_CELL_MAX_LIMIT;
    gBatterySummary.min_core_temperature = TPCHARGER_CELL_MIN_LIMIT - 1.0f;
    sDelayStateRequested = 0;
    unittest_determine_next_charger_state_results[12] =
        (bms_app_determine_next_charger_state() == BMS_CHARGER_CHARGING_DELAYED);


     /* 13.  VPACK_MAX_CHARGE > VPACK_START_CHARGE
      *      Result: True
      */
    unittest_determine_next_charger_state_results[13] =
            (VPACK_MAX_CHARGE > VPACK_START_CHARGE);


     /* 14.  gBatterySummary.pack_voltage < VPACK_MAX_CHARGE
     *      AND !Hysterisis
     *      Result: BMS_CHARGER_CHARGING_ENABLED
     *       AND Hysterisis
     */
    gBatterySummary.pack_voltage = VPACK_MAX_CHARGE-1;
    sHysterisisHigh[BMS_CHARGER_HYSTERISIS_PACK_VMAX] = 0;
    unittest_determine_next_charger_state_results[14] =
        (bms_app_determine_next_charger_state() == BMS_CHARGER_CHARGING_DELAYED) &&
        sHysterisisHigh[BMS_CHARGER_HYSTERISIS_PACK_VMAX];

     /* 15.  gBatterySummary.pack_voltage >= VPACK_MAX_CHARGE
      *      AND Hysterisis (set by last test step)
      *      Result: BMS_CHARGER_CHARGING_IDLE
      *          AND Hysterisis
      */
    gBatterySummary.pack_voltage = VPACK_MAX_CHARGE+1;
    unittest_determine_next_charger_state_results[15] =
        (bms_app_determine_next_charger_state() == BMS_CHARGER_CHARGING_IDLE) &&
        sHysterisisHigh[BMS_CHARGER_HYSTERISIS_PACK_VMAX];


     /* 16.  gBatterySummary.pack_voltage < VPACK_MAX_CHARGE
      *      AND gBatterySummary.pack_voltage >= VPACK_START_CHARGE
      *      AND Hysterisis (set by last test step)
      *      Result: BMS_CHARGER_CHARGING_IDLE
      */
    gBatterySummary.pack_voltage = VPACK_START_CHARGE + (VPACK_MAX_CHARGE-VPACK_START_CHARGE)/2;
    unittest_determine_next_charger_state_results[16] =
        (bms_app_determine_next_charger_state() == BMS_CHARGER_CHARGING_IDLE);

     /* 17.  gBatterySummary.pack_voltage < VPACK_START_CHARGE
      *      AND Hysterisis
      *      Result: BMS_CHARGER_CHARGING_ENABLED
      *          AND !Hysterisis
     */
    gBatterySummary.pack_voltage = VPACK_START_CHARGE-1;
    unittest_determine_next_charger_state_results[17] =
        (bms_app_determine_next_charger_state() == BMS_CHARGER_CHARGING_ENABLED) &&
       !sHysterisisHigh[BMS_CHARGER_HYSTERISIS_PACK_VMAX];

     /* 18.  gBatterySummary.pack_current < ICHARGE_PACK_MAX
      *      Result:" BMS_CHARGER_CHARGING_SHUTDOWN
     */
    gBatterySummary.pack_current = ICHARGE_PACK_MAX - 1.0f;
    unittest_determine_next_charger_state_results[18] =
        (bms_app_determine_next_charger_state() == BMS_CHARGER_CHARGING_SHUTDOWN);

     /* 19.  gBatterySummary.pack_current > ICHARGE_PACK_MIN
      *      Result: BMS_CHARGER_CHARGING_SHUTDOWN
      */
    gBatterySummary.pack_current = ICHARGE_PACK_MIN + 1.0f;
    unittest_determine_next_charger_state_results[19] =
        (bms_app_determine_next_charger_state() == BMS_CHARGER_CHARGING_SHUTDOWN);

     /* 20.  gBatterySummary.pack_current < ICHARGE_PACK_MIN
      *      Result: BMS_CHARGER_CHARGING_ENABLED
      */
    gBatterySummary.pack_current = ICHARGE_PACK_MIN - 10.0f;
    unittest_determine_next_charger_state_results[19] =
        (bms_app_determine_next_charger_state() == BMS_CHARGER_CHARGING_ENABLED);


     /* 21.  sAmpHourAccumilator > IHCHARGE_MAX
      *      Result: BMS_CHARGER_CHARGING_SHUTDOWN
      */
    sAmpHourAccumilator = IHCHARGE_MAX + 1.0f;
    unittest_determine_next_charger_state_results[21] =
        (bms_app_determine_next_charger_state() == BMS_CHARGER_CHARGING_SHUTDOWN);


     /* 22.  sChargerTimerSeconds > TCHARGE_MAX_SECONDS
      *      Result: BMS_CHARGER_CHARGING_SHUTDOWN
      */
    sChargerTimerSeconds = TCHARGE_MAX_SECONDS + 1.0f;
    unittest_determine_next_charger_state_results[22] =
        (bms_app_determine_next_charger_state() == BMS_CHARGER_CHARGING_SHUTDOWN);

}
