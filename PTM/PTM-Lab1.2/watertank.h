#ifndef WATERPOT

#include "library.h"

uint16_t watertank_value()
{
    uint16_t liquidsensor_value = 0;
    WaterTank_ADMUX();
    ADCSRA |= (1 << ADSC);                  //start ADC conversion
    loop_until_bit_is_clear(ADCSRA, ADSC);  //wait until ADC conversion is done
    liquidsensor_value = ADC;               //read ADC value in
    
    return liquidsensor_value;
}

int watertank_level()
{
    uint16_t liquidsensor_value = watertank_value();
    if (liquidsensor_value < WATERTANK_MIN)
        return 1;
    if (liquidsensor_value > WATERTANK_MAX)
        return 2;
    return 0;
}

#endif
