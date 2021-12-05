#include <avr/io.h>
#include <avr/iom32.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>


#define LCD_Data_Dir DDRD		/* Define LCD data port direction */
#define LCD_Command_Dir DDRA		/* Define LCD command port direction register */
#define LCD_Data_Port PORTD		/* Define LCD data port */
#define LCD_Command_Port PORTA		/* Define LCD data port */
#define RS PA0				/* Define Register Select (data/command reg.)pin */
#define RW PA1				/* Define Read/Write signal pin */
#define EN PA2				/* Define Enable signal pin */