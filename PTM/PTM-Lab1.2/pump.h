#ifndef PUMP

#include "library.h"


void pump_on()
{
  _delay_ms(50);
  PUMP_PORT |= (1 << PUMP_PIN);
  _delay_ms(50);
}

void pump_off()
{
  _delay_ms(50);
  PUMP_PORT &= ~(1 << PUMP_PIN);
  _delay_ms(50);
}

#endif