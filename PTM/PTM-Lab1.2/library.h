#include <avr/io.h>
#include <avr/iom32.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

//LCD setting Ports and Pins
#define LCD_Data_Dir DDRD      /* Define LCD data port direction */
#define LCD_Command_Dir DDRA   /* Define LCD command port direction register */
#define LCD_Data_Port PORTD    /* Define LCD data port */
#define LCD_Command_Port PORTA /* Define LCD data port */
#define RS PA0                 /* Define Register Select (data/command reg.)pin */
#define RW PA1                 /* Define Read/Write signal pin */
#define EN PA2                 /* Define Enable signal pin */

//WATER TANK
#define WATERTANK_MIN 100
#define WATERTANK_MAX 370

//WATER POT
#define WATERPOT_MIN 280
#define WATERPOT_MAX 370

//Motor setting Control Pins
#define MOTOR_PIN1 PA6   //PIN PA6
#define MOTOR_PIN2 PA7   //PIN PA7
#define MOTOR_PORT PORTA //PORT A
#define MOTOR_DDR DDRA   //PORT A

//Water Pump Control Pin
#define PUMP_PIN PC1    //PIN PA6
#define PUMP_PORT PORTC //PORT A
#define PUMP_DDR DDRC   //PORT A

//SWITCHES
#define SWITCH_UP PC2     //PIN PC2
#define SWITCH_DOWN PC3   //PIN PC4
#define SWITCH_PORT PORTC //PORT C
#define SWITCH_DDR DDRC   //PORT C
#define SWITCH_PIN PINC   //PORT C

//BUTTONS
#define BUTTON_UP PB3     //PIN PB3
#define BUTTON_DOWN PB4  //PIN PB4
#define BUTTON_PORT PORTB //PORT B
#define BUTTON_DDR DDRB   //PORT B
#define BUTTON_PIN PINB   //PORT B

//LED
#define LED_UP PB0     //PIN PB0
#define LED_DOWN  PB1  //PIN PB1
#define LED_PORT PORTB //PORT B
#define LED_DDR DDRB   //PORT B
#define LED_PIN PINB   //PORT B

