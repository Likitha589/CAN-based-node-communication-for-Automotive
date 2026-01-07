/*
 * File:   ecu2_main.c
 * Author: Likitha
 *
 * Created on 18 December, 2025, 6:27 PM
 */


#include <xc.h>
#include "adc.h"
#include "ecu2_sensor.h"
#include "digital_keypad.h"
#include "ssd.h"
#include "msg_id.h"
#include "can.h"
#define _XTAL_FREQ 2000000


unsigned char ssd[MAX_SSD_CNT];
unsigned char digit[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};

void init_config(void)
{
    init_adc();
    init_ssd_control();
    init_digital_keypad();
    init_can();
    TRISB0=TRISB1=TRISB6=TRISB7=0;
    RB0=RB1=RB6=RB7=0;
}

void main(void)
{
    init_config();
    unsigned int delay = 0;

    unsigned char rpm_arr[4];
    unsigned char ind_arr[1];

    unsigned int msgid;          
    unsigned char data[4];
    unsigned char len=0;  

    while (1)
    {
        unsigned int rpm = get_rpm();
        unsigned char key = read_digital_keypad(STATE_CHANGE);
        IndicatorStatus ind = process_indicator(key); 

        rpm_arr[3] = ((rpm % 10) + '0');
        rpm_arr[2] = (((rpm / 10)%10) + '0');
        rpm_arr[1] = (((rpm / 100)%10)   + '0');
        rpm_arr[0] = ((rpm / 1000)+'0');

        ind_arr[0] = ind;

        can_transmit(RPM_MSG_ID, rpm_arr, 4);
        __delay_ms(80);
        
        //can_receive(&msgid, data, &len);
       /* if (msgid == RPM_MSG_ID)
        {   
            ssd[0] = digit[data[0]];
            ssd[1] = digit[data[1]];
            ssd[2] = digit[data[2]];
            ssd[3] = digit[data[3]];
            
            display(ssd);
        }*/
        
        can_transmit(INDICATOR_MSG_ID,ind_arr, 1);
        __delay_ms(80);    
       // can_receive(&msgid,data,&len);
       /* if(msgid == INDICATOR_MSG_ID)
        {
           if(data[0]==e_ind_left)
           {
            if(delay++==50)
            {
                delay=0;
                RB0 = !RB0;
                RB1 = !RB1;
                RB6 = 0;
                RB7 = 0;
            }
        }
        else if(data[0]==e_ind_right)
        {
            if(delay++==50)
            {
                delay=0;
                RB6 = !RB6;
                RB7 = !RB7;
                RB0 = 0;
                RB1 = 0;
              }
        }
        else if(data[0]==e_ind_off)
        {
            RB0 = 0;
            RB1 = 0;
            RB6 = 0;
            RB7 = 0;
        }
        }*/
    
    }
}