#include "ecu2_sensor.h"
#include "digital_keypad.h"
#include "adc.h"
#include "ssd.h" 

//#include "adc.h"
#include "can.h"
//#include "msg_id.h"
//#include "uart.h"

volatile IndicatorStatus prev_ind_status=e_ind_off;
volatile IndicatorStatus cur_ind_status=e_ind_off;
volatile unsigned char led_state=LED_OFF;

uint16_t get_rpm()
{
    //Implement the rpm function
    uint16_t speed = read_adc(CHANNEL4)*5.866;
    return speed;
}

IndicatorStatus process_indicator(unsigned char key)
{
    //Implement the indicator function
    if(key==SWITCH1)
    {
        cur_ind_status=e_ind_left;
    }
    else if(key==SWITCH2)
    {
        cur_ind_status=e_ind_right;
    }
    else if(key==SWITCH3)
    {
        cur_ind_status=e_ind_off;
    }
    return cur_ind_status;
    
}