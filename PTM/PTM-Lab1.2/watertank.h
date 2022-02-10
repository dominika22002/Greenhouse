#ifndef WATERPOT

#include "library.h"

void WaterTank_ADMUX() //Water tank ADMUX settings
{
    ADMUX |= ((1 << MUX0) | (1 << MUX2)); //setting channel - 00101, MUX0 = 1, MUX2 = 1
    ADMUX &= ~((1 << MUX1));              //setting zero - MUX1 = 0
}

uint16_t watertank_value()
{
    uint16_t liquidsensor_value = 0;
    WaterTank_ADMUX();
    ADCSRA |= (1 << ADSC);                 //start ADC conversion
    loop_until_bit_is_clear(ADCSRA, ADSC); //wait until ADC conversion is done
    liquidsensor_value = ADC;              //read ADC value in

    return liquidsensor_value;
}

int watertank_level(uint16_t liquidsensor_value)
{
    if (liquidsensor_value < WATERTANK_MIN)
        return 1;
    if (liquidsensor_value > WATERTANK_MAX)
        return 0;
    return 0;
}

#endif
