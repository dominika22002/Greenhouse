#ifndef MOTOR

#include "library.h"


void motor_left()
{
  _delay_ms(100);
  MOTOR_PORT &= ~(1 << MOTOR_PIN1); 
  _delay_ms(100);
  MOTOR_PORT |= (1 << MOTOR_PIN2);
  _delay_ms(100);
}

void motor_right()
{
  _delay_ms(100);
  MOTOR_PORT &= ~(1 << MOTOR_PIN2); 
  _delay_ms(100);
  MOTOR_PORT |= (1 << MOTOR_PIN1);
  _delay_ms(100);
}

void motor_stop()
{
  _delay_ms(100);
  MOTOR_PORT &= ~(1 << MOTOR_PIN2); 
  _delay_ms(100);
  MOTOR_PORT &= ~(1 << MOTOR_PIN1);
  _delay_ms(100);
}

#endif
