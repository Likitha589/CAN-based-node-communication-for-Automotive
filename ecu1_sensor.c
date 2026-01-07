/*
 * File:   ecu1_sensor.c
 * Author: Likitha
 *
 * Created on 18 December, 2025, 11:25 AM
 */


#include "ecu1_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
// #include "uart.h"

uint16_t get_speed(void)
{
    // Implement the speed function
    uint16_t speed = read_adc(CHANNEL4)/10.33;
    return speed;
}

unsigned char index;
unsigned char get_gear_pos(void)
{
    // Implement the gear function
    return index;   
}