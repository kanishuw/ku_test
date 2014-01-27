/*
 * unittest_hw_contactor
 *
 * Containes stubs to allow interfacing and controlling the outputs of
 * the routines in bms_hw_contactor.c
 */

float bms_hw_cn_get_contactor_voltage_value = 0.0f;
float bms_hw_cn_get_fuse_voltage_value = 0.0f;
float bms_hw_cn_get_pack_voltage_value = 0.0f;


float bms_hw_cn_get_contactor_voltage()
{
    return bms_hw_cn_get_contactor_voltage_value;
}

float bms_hw_cn_get_fuse_voltage()
{
    return bms_hw_cn_get_fuse_voltage_value;
}

float bms_hw_cn_get_pack_voltage()
{
    return bms_hw_cn_get_pack_voltage_value;
}

