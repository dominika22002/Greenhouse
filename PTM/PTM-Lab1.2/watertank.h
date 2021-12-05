#ifndef WATERPOT

#include "library.h"

#define MIN_VAL 60
#define MAX_VAL 300

uint16_t watertank_value()
{
    char text[20];
    uint16_t liquidsensor_value = 0;
    ADMUX = 0x00;
    ADCSRA |= (0 << ADSC);
    ADMUX |= (1 << REFS0); //ustawienie napięcia ref na napięcie zasilania
    // ADMUX = 0x00; //wybor kanalu, w tym wypadku kanal 5 (00101)
    ADMUX |= ((1 << MUX0) | (0 << MUX1) | (1 << MUX2)); //wybor kanalu, w tym wypadku kanal 5 (00101)
    // ADMUX = 0101;
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0); //czestotliwosc na 8
	ADCSRA |= (1 << ADEN);				   //uruchomienie przetwornika ADC
    ADCSRA |= (1 << ADSC);                              //start ADC conversion
    loop_until_bit_is_clear(ADCSRA, ADSC);              //wait until ADC conversion is done
    liquidsensor_value = ADC;                           //read ADC value in

    		// sprintf(text, "watertank_value()");
			// LCD_String(text);
			// // tank_val = percent(tank_val);
			// sprintf(text, "%d",liquidsensor_value);
			// // sprintf(text, "%d",watertank_value());
			// LCD_Command(0xC0); /* Go to 2nd line*/
			// LCD_String(text);


    return liquidsensor_value;
}

int watertank_level()
{
    uint16_t liquidsensor_value = watertank_value();
    if (liquidsensor_value < MIN_VAL)
        return 1;
    if (liquidsensor_value > MAX_VAL)
        return 2;
    return 0;
}

// static inline void initADC5(void) { // czujnik wody
// ADMUX |= (1 << REFS0); //ustawienie napięcia ref na napięcie zasilania
// //ADMUX |= ((1<<MUX0)| (1<<MUX2)); //wybor kanalu, w tym wypadku kanal 7 (00111)
// ADCSRA |= (1 << ADPS1) | (1 << ADPS0); //czestotliwosc na 8
// ADCSRA |= (1 << ADEN); //uruchomienie przetwornika ADC
// }

#endif
