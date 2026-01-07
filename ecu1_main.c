/*
 * File:   ecu1_main.c
 * Author: Likitha
 *
 * Created on 18 December, 2025, 11:25 AM
 */


#include "adc.h"
#include "can.h"
#include "ecu1_sensor.h"
#include "msg_id.h"
#include "matrix_keypad.h"
#include "clcd.h"
#define _XTAL_FREQ 20000000
// #include "uart.h"

void init_config()
{
    init_matrix_keypad();
    init_clcd();
    init_adc();
    init_can();
}

char event[9][3] = {"ON","GN","G1","G2","G3","G4","G5","GR","C_"};
 unsigned int s_msg_id=0;
        unsigned char data[3],g_data[3];
        unsigned int slen=0;

int main()
{
    //Call the functions
    init_config();
    unsigned char key;
    uint16_t speed;
   unsigned  char arr[3];
    unsigned int collision_flag=0;
    while(1)
    {
        key=read_switches(STATE_CHANGE);
        speed=get_speed();
        if(key==MK_SW1 && collision_flag==1)
        {
            index=1;
            collision_flag=0;
        }
        else if(key==MK_SW1 && collision_flag==0)
        {
            if(index<7)
            index++;
        }
        else if(key==MK_SW2 && collision_flag==1)
        {
            index=1;
            collision_flag=0;      
        }
        else if(key==MK_SW2 && collision_flag==0)
        {
            if(index>0)
            index--;  
        }
        else if(key==MK_SW3)
        {
            index=8;
            collision_flag=1;
        }
        
        arr[0]=speed/10 +'0';
        arr[1]=speed%10+'0';
        arr[2]='\0';
        
        //clcd_print("SPEED     GEAR",LINE1(0));
        //clcd_print(arr,LINE2(0));
        //clcd_print(event[index],LINE2(11));
        
       
       can_transmit(SPEED_MSG_ID ,arr,2);
          __delay_ms(80);
        //can_receive(&s_msg_id,data,&slen);
        /*if(s_msg_id == SPEED_MSG_ID)
        {
            data[2]='\0';
            clcd_print("SPEED           ",LINE1(0));
            clcd_print(data,LINE1(7));
        }*/
        
        can_transmit(GEAR_MSG_ID,event[index],2);
        __delay_ms(80);
       // can_receive(&s_msg_id,g_data,&slen);
        /*if(s_msg_id == GEAR_MSG_ID)
        {
            g_data[2]='\0';
            clcd_print("GEAR            ",LINE2(0));
            clcd_print(g_data,LINE2(7));
        }*/
        
    }
}