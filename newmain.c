/*
 * File:   newmain.c
 * Author: Likitha
 *
 * Created on 5 January, 2026, 5:20 PM
 */


#include <xc.h>
#include <stdint.h>
#include "can.h"
#include "clcd.h"
#include "msg_id.h"
#include "ecu2_sensor.h"
#define _XTAL_FREQ 20000000
//#include "message_handler.h"
//#include "isr.h"
//#include "timer0.h"

//static init_leds() {
  //  TRISB = 0x08; // Set RB2 as output, RB3 as input, remaining as output
   // PORTB = 0x00;
// }

static void init_config(void) {
    // Initialize CLCD and CANBUS
    init_clcd();
    init_can();
    TRISB0=TRISB1=TRISB6=TRISB7=0;
    RB0=RB1=RB6=RB7=0;
    // Enable Interrupts
    //init_timer0();
}


void main(void) {
    // Initialize peripherals
    init_config();
    unsigned long int delay=0;
    unsigned int rmsgid=0;
    unsigned char rdata[5];
    unsigned int rlen=0;
    
    /* ECU1 main loop */
    while (1) {
        // Read CAN Bus data and handle it
        clcd_print("SP GR RPM  IND ",LINE1(0));
        can_receive(&rmsgid,rdata,&rlen);
      //  __delay_us(80);
        if(rmsgid==SPEED_MSG_ID)
        {
            rdata[2]='\0';
            clcd_print(rdata,LINE2(0));
        }
        else if(rmsgid==GEAR_MSG_ID)
        {
            rdata[2]='\0';
            clcd_print(rdata,LINE2(3));
        }
        else if(rmsgid==RPM_MSG_ID)
        {
            rdata[4]='\0';
            clcd_print(rdata,LINE2(6));
        }
        else if(rmsgid==INDICATOR_MSG_ID)
        {
           if(rdata[0]==e_ind_left)
           {
                if(delay++==200)
                {
                    RB0 = !RB0;
                    RB1 = !RB1;
                    RB6 = 0;
                    RB7 = 0;
                    delay =0;
                  
                }
                clcd_print("<-", LINE2(11));
            }
            else if(rdata[0]==e_ind_right)
            {
                if(delay++==200)
                {
                    RB6 = !RB6;
                    RB7 = !RB7;
                    RB0 = 0;
                    RB1 = 0;
                    delay =0;                  
                }
                clcd_print("->", LINE2(11));                
           }
           else if(rdata[0] == e_ind_off)
           {
            RB0 = RB1 = RB6 = RB7 = 0;
            clcd_print("_", LINE2(11));
           }  
        }
    }
    return;
            
}     