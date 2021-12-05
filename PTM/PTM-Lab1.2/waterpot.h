#ifndef WATERPOT

#include "library.h"

#define MIN_VAL 1
#define MAX_VAL 3

uint16_t waterpot_value()
{
	char text[20];
    uint16_t liquidsensor_value = 0;
    ADMUX = 0x00;
    ADCSRA |= (0 << ADSC);                 //start ADC conversion
    ADMUX |= (1 << REFS0); //ustawienie napięcia ref na napięcie zasilania
    ADMUX |= ((0 << MUX0) | (1 << MUX1) | (1 << MUX2));  //wybor kanalu, w tym wypadku kanal 3 (00011)
    // ADMUX = 0011;
    ADCSRA |= (1 << ADPS1) | (1 << ADPS0); //czestotliwosc na 8
	ADCSRA |= (1 << ADEN);				   //uruchomienie przetwornika ADC
    ADCSRA |= (1 << ADSC);                 //start ADC conversion
    loop_until_bit_is_clear(ADCSRA, ADSC); //wait until ADC conversion is done
    liquidsensor_value = ADC;              //read ADC value in

			// sprintf(text, "waterpot_value()");
			// LCD_String(text);
			// // tank_val = percent(tank_val);
			// sprintf(text, "%d",liquidsensor_value);
			// // sprintf(text, "%d",watertank_value());
			// LCD_Command(0xC0); /* Go to 2nd line*/
			// LCD_String(text);


    return liquidsensor_value;
}

int waterpot_level()
{
    uint16_t liquidsensor_value = waterpot_value();
    if (liquidsensor_value < MIN_VAL)
        return 1;
    if (liquidsensor_value > MAX_VAL)
        return 2;
    return 0;
}

#endif
