/* 
 * File:   unittest_hw_gpio.c
 * Author: kevin
 *
 * Created on October 11, 2013, 6:04 AM
 */

unsigned char gpio_read_contactor_latch_value       = 0;
unsigned char gpio_read_forever_power_latch_value   = 0;
unsigned char gpio_read_charging_fets_value         = 0;
unsigned char gpio_read_charger_enable_value        = 0;
unsigned char gpio_read_five_volt_power_value       = 0;
unsigned char gpio_read_enable_fuel_gauges          = 0;
unsigned char gpio_read_enable_charging_fets        = 0;
unsigned char gpio_read_enable_charger              = 0;
unsigned char gpio_read_enable_drive_select         = 0;
unsigned char gpio_read_enable_warning_led          = 0;
unsigned char gpio_read_enable_alarm_led            = 0;

int gpio_register_input_value = 0;


void gpio_enter_sleep_mode()
{

}

void gpio_initialize()
{

}

void gpio_latch_mux( unsigned int muxId, unsigned char address )
{

}

void gpio_close_contactor()
{
    gpio_read_contactor_latch_value = 1;
}

void gpio_open_contactor()
{
    gpio_read_contactor_latch_value = 0;
}

unsigned char gpio_read_contactor_latch()
{
    return gpio_read_contactor_latch_value;
}


void gpio_enable_forever_power()
{
    gpio_read_forever_power_latch_value = 1;
}

void gpio_disable_forever_power()
{
    gpio_read_forever_power_latch_value = 0;
}

unsigned char gpio_read_forever_power_latch()
{
    return gpio_read_forever_power_latch_value;
}

void gpio_enable_five_volt_power()
{
    gpio_read_five_volt_power_value = 1;
}

void gpio_disable_five_volt_power()
{
    gpio_read_five_volt_power_value = 0;
}

void gpio_enable_fuel_guages()
{
    gpio_read_enable_fuel_gauges = 1;
}

void gpio_disable_fuel_guages()
{
    gpio_read_enable_fuel_gauges = 0;
}


void gpio_enable_charging_fets()
{
    gpio_read_enable_charging_fets = 1;
}

void gpio_disable_charging_fets()
{
    gpio_read_enable_charging_fets = 0;
}

unsigned char gpio_read_charging_fets()
{
    return gpio_read_charging_fets_value;
}


void gpio_enable_charger()
{
    gpio_read_enable_charger = 1;
}

void gpio_disable_charger()
{
    gpio_read_enable_charger = 0;
}

unsigned char gpio_read_charger_enable()
{
    return gpio_read_charger_enable_value;
}


void gpio_enable_drive_select( unsigned char selectId )
{
    gpio_read_enable_drive_select = 1;
}

void gpio_disable_drive_select( unsigned char selectId )
{
    gpio_read_enable_drive_select = 0;
}


void gpio_enable_warning_led()
{
    gpio_read_enable_warning_led = 1;
}

void gpio_disable_warning_led()
{
    gpio_read_enable_warning_led = 0;
}

void gpio_enable_alarm_led()
{
    gpio_read_enable_alarm_led = 1;
}

void gpio_disable_alarm_led()
{
    gpio_read_enable_alarm_led = 0;
}

void gpio_set_key_switch_ptr( unsigned char *ptr )
{
}

void gpio_set_long_term_storage_ptr( unsigned char *ptr )
{

}

void gpio_set_boost_switch_ptr( unsigned char *ptr )
{

}

void gpio_set_charger_connected_ptr( unsigned char *ptr )
{

}

void gpio_cutback_pwm_initialize()
{

}

void gpio_set_cutback_pwm_duty_cycle( float duty_cycle )
{

}

int gpio_register_input( unsigned char inputId, unsigned char *pVar )
{
   return gpio_register_input_value;
}

void gpio_read_inputs()
{

}

void gpio_toggle_gpio(unsigned int id)
{

}

void gpio_enable_gpio(unsigned int id)
{

}

void gpio_disable_gpio(unsigned int id)
{

}
