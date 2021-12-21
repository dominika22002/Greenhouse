#ifndef WATERPOT

#include "library.h"

uint16_t waterpot_value()
{
    uint16_t liquidsensor_value = 0;
    WaterPot_ADMUX();
    ADCSRA |= (1 << ADSC);                  //start ADC conversion
    loop_until_bit_is_clear(ADCSRA, ADSC);  //wait until ADC conversion is done
    liquidsensor_value = ADC;               //read ADC value in

    return liquidsensor_value;
}

int waterpot_level()
{
    uint16_t liquidsensor_value = waterpot_value();
    if (liquidsensor_value < WATERPOT_MIN)
        return 1;
    if (liquidsensor_value > WATERPOT_MAX)
        return 2;
    return 0;
}

#endif
