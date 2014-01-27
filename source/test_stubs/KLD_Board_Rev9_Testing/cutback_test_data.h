/* 
 * File:   cutback_test_data.h
 * Author: kevin
 *
 * Created on July 13, 2013, 5:24 PM
 */

#ifndef CUTBACK_TEST_DATA_H
#define	CUTBACK_TEST_DATA_H

#ifdef	__cplusplus
extern "C" {
#endif

void load_low_to_high_temperature_test( float cellVoltageMin, float cellVoltageMax, float deltaT );
void load_high_to_low_temperature_test( float cellVoltageMin, float cellVoltageMax, float deltaT );
void load_discharge_test( float coreTempMin, float coreTempMax, float deltaV );
void load_discharge_test_vmax( float coreTMin, float coreTMax, float deltaT );
void load_discharge_test_economy( float coreTMin, float coreTMax, float deltaT );
void load_charge_test( float coreTempMin, float coreTempMax, float deltaV );
void load_regen_test( float coreTempMin, float coreTempMax, float deltaV );
int prepare_test_data();

void examine_results();


#ifdef	__cplusplus
}
#endif

#endif	/* CUTBACK_TEST_DATA_H */

