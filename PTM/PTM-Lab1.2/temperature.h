#ifndef TEMPERATURE

#include "library.h"

void Temp_ADMUX() //Water pot ADMUX settings
{
    ADMUX |= ((1 << MUX2));                //setting channel - 00100, MUX0 = 1, MUX1 = 1
    ADMUX &= ~((1 << MUX0) | (1 << MUX1)); //setting zero - MUX2 = 0
}

uint16_t temp_value()
{
    uint16_t liquidsensor_value = 0;
    Temp_ADMUX();
    ADCSRA |= (1 << ADSC);                 //start ADC conversion
    loop_until_bit_is_clear(ADCSRA, ADSC); //wait until ADC conversion is done
    liquidsensor_value = ADC;              //read ADC value in

    return liquidsensor_value;
}

#endif
