

#include "bms_defs.h"


extern BMSSystemStatusType      gBatteryStatus;
extern BMSBatterySummaryType    gBatterySummary;
extern CBITFlagsType            gCBITFlags;
extern PBITFlagsType            gPBITFlags;


typedef union __cutback_test_bits
{
    struct
    {
        unsigned char enconomy_mode :1;
        unsigned char charging_mode :1;
    } bits;
    unsigned int value;
} CutBackTestBitsType;

typedef struct __cutback_test_data
{
	float	data;
	float	result;
} CutbackTestData;

static float TemperatureCutbackData[] = {
	-20  ,
	-19.5,
	-19  ,
	-18.5,
	-18  ,
	-17.5,
	-17  ,
	-16.5,
	-16  ,
	-15.5,
	-15  ,
	-14.5,
	-14  ,
	-13.5,
	-13  ,
	-12.5,
	-12  ,
	-11.5,
	-11  ,
	-10.5,
	-10  ,
	-9.5 ,
	-9   ,
	-8.5 ,
	-8   ,
	-7.5 ,
	-7   ,
	-6.5 ,
	-6   ,
	-5.5 ,
	-5   ,
	-4.5 ,
	-4   ,
	-3.5 ,
	-3   ,
	-2.5 ,
	-2   ,
	-1.5 ,
	-1   ,
	-0.5 ,
	0    ,
	0.5  ,
	1    ,
	1.5  ,
	2    ,
	2.5  ,
	3    ,
	3.5  ,
	4    ,
	4.5  ,
	5    ,
	5.5  ,
	6    ,
	6.5  ,
	7    ,
	7.5  ,
	8    ,
	8.5  ,
	9    ,
	9.5  ,
	10   ,
	10.5 ,
	11   ,
	11.5 ,
	12   ,
	12.5 ,
	13   ,
	13.5 ,
	14   ,
	14.5 ,
	15   ,
	15.5 ,
	16   ,
	16.5 ,
	17   ,
	17.5 ,
	18   ,
	18.5 ,
	19   ,
	19.5 ,
	20   ,
	20.5 ,
	21   ,
	21.5 ,
	22   ,
	22.5 ,
	23   ,
	23.5 ,
	24   ,
	24.5 ,
	25   ,
	25.5 ,
	26   ,
	26.5 ,
	27   ,
	27.5 ,
	28   ,
	28.5 ,
	29   ,
	29.5 ,
	30   ,
	30.5 ,
	31   ,
	31.5 ,
	32   ,
	32.5 ,
	33   ,
	33.5 ,
	34   ,
	34.5 ,
	35   ,
	35.5 ,
	36   ,
	36.5 ,
	37   ,
	37.5 ,
	38   ,
	38.5 ,
	39   ,
	39.5 ,
	40   ,
	40.5 ,
	41   ,
	41.5 ,
	42   ,
	42.5 ,
	43   ,
	43.5 ,
	44   ,
	44.5 ,
	45   ,
	45.5 ,
	46   ,
	46.5 ,
	47   ,
	47.5 ,
	48   ,
	48.5 ,
	49   ,
	49.5 ,
	50   ,
	50.5 ,
	51   ,
	51.5 ,
	52   ,
	52.5 ,
	53   ,
	53.5 ,
	54   ,
	54.5 ,
	55   ,
	55.5 ,
	56   ,
	56.5 ,
	57   ,
	57.5 ,
	58   ,
	58.5 ,
	59   ,
	59.5 ,
	60   ,
	60.5 ,
	61   ,
	61.5 ,
	62   ,
	62.5 ,
	63   ,
	63.5 ,
	64   ,
	64.5 ,
	65   ,
	65.5 ,
	66   ,
	66.5 ,
	67   ,
	67.5 ,
	68   ,
	68.5 ,
	69   ,
	69.5 ,
	70   ,
	70.5 ,
	71   ,
	71.5 ,
	72   ,
	72.5 ,
	73   ,
	73.5 ,
	74   ,
	74.5 ,
	75   ,
	75.5 ,
	76   ,
	76.5 ,
	77   ,
	77.5 ,
	78   ,
	78.5 ,
	79   ,
	79.5 ,
	80   ,
	80.5 ,
	81   ,
	81.5 ,
	82   ,
	82.5 ,
	83   ,
	83.5 ,
	84   ,
	84.5 ,
	85   ,
	85.5 ,
	86 
};

static float VoltageCutbackData[] = {
	2.5  ,
	2.52 ,
	2.54 ,
    2.56 ,
	2.58 ,
	2.6  ,
	2.62 ,
	2.64 ,
	2.6  ,
	2.68 ,
	2.7  ,
	2.72 ,
	2.74 ,
	2.76 ,
	2.78 ,
	2.8  ,
	2.82 ,
	2.84 ,
	2.86 ,
	2.88 ,
	2.9  ,
	2.92 ,
	2.94 ,
	2.96 ,
	2.98 ,
	3    ,
	3.02 ,
	3.04 ,
	3.06 ,
	3.08 ,
	3.1  ,
	3.12 ,
	3.14 ,
	3.16 ,
	3.18 ,
	3.2  ,
	3.22 ,
	3.24 ,
	3.26 ,
	3.28 ,
	3.3  ,
	3.32 ,
	3.34 ,
	3.36 ,
	3.38 ,
	3.4  ,
	3.42 ,
	3.44 ,
	3.46 ,
	3.48 ,
	3.5  ,
	3.52 ,
	3.54 ,
	3.56 ,
	3.58 ,
	3.6  ,
	3.62 ,
	3.64 ,
	3.66 ,
	3.68 ,
	3.7  ,
	3.72 ,
	3.74 ,
	3.76 ,
	3.78 ,
	3.8  ,
	3.82,
	3.84,
	3.86,
	3.88,
	3.9 ,
	3.92,
	3.94,
	3.96,
	3.98,
	4   ,
	4.02,
	4.04,
	4.06,
	4.08,
	4.1 ,
	4.12,
	4.14,
	4.16,
	4.18,
	4.2 ,
	4.22,
	4.24,
	4.26,
	4.27,
	4.29,
	4.31,
	4.33,
	4.35,
	4.37,
	4.39,
	4.41,
	4.43,
	4.45,
	4.47,
	4.49,
	4.51,
	4.53,
	4.55,
	4.57,
	4.59,
	4.61,
	4.63,
	4.65,
	4.67,
	4.69,
	4.71,
	4.73,
	4.75,
	4.77,
	4.79,
	4.81,
	4.83,
	4.85,
	4.87
};

static float Results[ sizeof( TemperatureCutbackData )/sizeof( TemperatureCutbackData[0])];
static float MaxData[ sizeof( TemperatureCutbackData )/sizeof( TemperatureCutbackData[0])];

static InterruptCBType sEconomyChangeCB=0;

//Direction -- 0 == low to high
//			   1 == high to low
unsigned int sDirection = 0;

//Test Type
//   Temperature  = 0;
//   Voltage      = 1;
unsigned int sType      = 0;

//Test Charge Mode
//	 CHARGING_MODE_REGEN
//	 CHARGING_MODE_CHARGING
//	 CHARGING_MODE_DISCHARGING
//	 CHARGING_MODE_IDLE
unsigned int sChargeMode = 0;

unsigned int sIndex = 0;
unsigned int sCurrentIndex = 0;

float sMinValue;
float sMaxValue;
float sDeltaValue;

void load_low_to_high_temperature_test( float cellVoltageMin, float cellVoltageMax, float deltaT )
{
    sDirection = 0;
    sType = 0;
    sIndex = 0;
    sChargeMode = CHARGING_MODE_IDLE;

    sMinValue = cellVoltageMin;
    sMaxValue = cellVoltageMax;
    sDeltaValue = deltaT;
}

void load_high_to_low_temperature_test( float cellVoltageMin, float cellVoltageMax, float deltaT )
{
    sDirection = 1;
    sType = 0;
    sIndex = 0;
    sChargeMode = CHARGING_MODE_IDLE;

    sMinValue = cellVoltageMin;
    sMaxValue = cellVoltageMax;
    sDeltaValue = deltaT;

    //Flip the data around for the test
    int idx = 0;
    int length = sizeof(TemperatureCutbackData)/sizeof(TemperatureCutbackData[0]);

    //Flip the data around
    for( ;idx < length/2; ++idx )
    {
        float f = TemperatureCutbackData[idx];
        TemperatureCutbackData[idx] = TemperatureCutbackData[length-1-idx];
        TemperatureCutbackData[length-1-idx] = f;
    }

}

void load_discharge_test( float coreTMin, float coreTMax, float deltaT )
{
    sDirection = 1;
    sType = 1;
    sIndex = 0;
    sChargeMode = CHARGING_MODE_DISCHARGING;

    sMinValue = coreTMin;
    sMaxValue = coreTMax;
    sDeltaValue = deltaT;

    int idx = 0;
    int length = sizeof(VoltageCutbackData)/sizeof(VoltageCutbackData[0]);

    //Flip the data around
    for( ;idx < length/2; ++idx )
    {
        float f = VoltageCutbackData[idx];
        VoltageCutbackData[idx] = VoltageCutbackData[length-1-idx];
        VoltageCutbackData[length-1-idx] = f;
    }
}

void load_discharge_test_vmax( float coreTMin, float coreTMax, float deltaT )
{
    (*sEconomyChangeCB)( 0 );      //The first call after boot up will put it into VMax mode
    load_discharge_test( coreTMin, coreTMax, deltaT );
}

void load_discharge_test_economy( float coreTMin, float coreTMax, float deltaT )
{
    
    //This is for the special case where the voltage must be at least BMS_DISCHARGE_GRAPH_VLIMIT_NORMAL_B
    //before it will switch into econo mode.
    gBatterySummary.min_cell_voltage     = BMS_DISCHARGE_GRAPH_VLIMIT_NORMAL_B+0.02f;

    (*sEconomyChangeCB)( 0 );      //The first call after boot up will put it into VMax mode
    (*sEconomyChangeCB)( 0 );      //The second call after boot up will put it into Economy/Extended range mode
    load_discharge_test( coreTMin, coreTMax, deltaT );
}

void load_charge_test( float cellVMin, float cellVMax, float deltaT )
{
    sDirection = 0;
    sType = 1;
    sIndex = 0;
    sChargeMode = CHARGING_MODE_CHARGING;

    sMinValue = cellVMin;
    sMaxValue = cellVMax;
    sDeltaValue = deltaT;
}

void load_regen_test( float cellVMin, float cellVMax, float deltaV, unsigned char mode )
{
    sDirection = 0;
    sType = 1;
    sIndex = 0;
    sChargeMode = CHARGING_MODE_REGEN;

    sMinValue = cellVMin;
    sMaxValue = cellVMax;
    sDeltaValue = deltaV;
}

int prepare_test_data()
{
    if( sType == 0 )
    {
        //Do temperature data
        if( sIndex == sizeof(TemperatureCutbackData)/sizeof(TemperatureCutbackData[0] ) )
        {
            return 0;
        }


        if( sDirection == 0)
        {
            gBatterySummary.min_core_temperature = TemperatureCutbackData[ sIndex ];
            gBatterySummary.max_core_temperature = gBatterySummary.min_core_temperature + sDeltaValue;
        }
        else if( sDirection == 1)
        {
            gBatterySummary.max_core_temperature = TemperatureCutbackData[ sIndex ];
            gBatterySummary.min_core_temperature = gBatterySummary.max_core_temperature - sDeltaValue;
        }

        gBatterySummary.min_cell_voltage     = sMinValue;
        gBatterySummary.max_cell_voltage     = sMaxValue;

        gBatteryStatus.bits.charging_mode    = sChargeMode;
    }
    else if( sType == 1 )
    {
        if( sIndex == sizeof(VoltageCutbackData)/sizeof(VoltageCutbackData[0] ) )
        {
            return 0;
        }

        if( sDirection == 0 )
        {
            gBatterySummary.min_cell_voltage     = VoltageCutbackData[ sIndex ];
            gBatterySummary.max_cell_voltage     = gBatterySummary.min_cell_voltage + sDeltaValue;
        }
        else if( sDirection == 1 )
        {
            gBatterySummary.max_cell_voltage     = VoltageCutbackData[ sIndex ];
            gBatterySummary.min_cell_voltage     = gBatterySummary.max_cell_voltage - sDeltaValue;
        }

        gBatterySummary.min_core_temperature = sMinValue;
        gBatterySummary.max_core_temperature = sMaxValue;

        gBatteryStatus.bits.charging_mode    = sChargeMode;
    }
    else
    {
        return 0;
    }

    return 1;
}

void gpio_set_cutback_pwm_duty_cycle( float dutyCycle )
{
    if( sType == 0 )
    {
        Results[ sIndex ] = dutyCycle;
        TemperatureCutbackData[ sIndex ] = gBatterySummary.min_core_temperature;
        MaxData[ sIndex ] = gBatterySummary.max_core_temperature;
    }
    else if( sType == 1)
    {
        Results[ sIndex ] = dutyCycle;
        VoltageCutbackData[ sIndex ] = gBatterySummary.min_cell_voltage;
        MaxData[ sIndex ] = gBatterySummary.max_cell_voltage;
    }

    ++sIndex;
}

void examine_results()
{
    sDirection += 1;
    sDirection -= 1;
}


void gpio_configure_economy_input( InterruptCBType cb )
{
    sEconomyChangeCB = cb;
}
