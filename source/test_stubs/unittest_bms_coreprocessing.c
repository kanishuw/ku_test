/* 
 * File:   unittest_bms_coreprocessing.c
 * Author: kevin
 *
 * Created on October 11, 2013, 5:52 AM
 */

#include "bms_defs.h"

unsigned int balance_gates_record[ MAX_NUM_CORES ];

void bms_acp_set_balance_gates( unsigned int coreId, unsigned int balance_gates )
{
    balance_gates_record[ coreId ] = balance_gates;
}

void bms_acp_sleep()
{

}
