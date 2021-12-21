#include <avr/io.h>
#include <avr/iom32.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

//LCD setting Ports and Pins
#define LCD_Data_Dir DDRD		/* Define LCD data port direction */
#define LCD_Command_Dir DDRA		/* Define LCD command port direction register */
#define LCD_Data_Port PORTD		/* Define LCD data port */
#define LCD_Command_Port PORTA		/* Define LCD data port */
#define RS PA0				/* Define Register Select (data/command reg.)pin */
#define RW PA1				/* Define Read/Write signal pin */
#define EN PA2				/* Define Enable signal pin */


//WATER TANK
#define WATERTANK_MIN 60
#define WATERTANK_MAX 300
void WaterTank_ADMUX() //Water tank ADMUX settings
{
    ADMUX |= ((1 << MUX0) | (1 << MUX2));   //setting channel - 00101, MUX0 = 1, MUX2 = 1
    ADMUX &= ~((1 << MUX1));                //setting zero - MUX1 = 0
}


//WATER POT
#define WATERPOT_MIN 60
#define WATERPOT_MAX 300
void WaterPot_ADMUX() //Water pot ADMUX settings
{
    ADMUX |= ((1 << MUX0) | (1 << MUX1));   //setting channel - 00011, MUX0 = 1, MUX1 = 1
    ADMUX &= ~((1 << MUX2));                //setting zero - MUX2 = 0
}


//Motor setting Control Pins
#define MOTOR_PIN1 PA6 //PIN PA6
#define MOTOR_PIN2 PA7 //PIN PA7
#define MOTOR_PORT PORTA //PORT A


//Water Pump Control Pin
#define PUMP_PIN PA6 //PIN PA6
#define PUMP_PORT PORTA //PORT A

//SWITCHES
#define SWITCH_UP PC0 //PIN PC0
#define SWITCH_DOWN PC1 //PIN PC1
#define SWITCH_PORT PORTC //PORT C
