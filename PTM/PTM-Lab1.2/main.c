#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/iom32.h>

//#include "lcd.h"
// #include "waterpot.h"
// #include "watertank.h"
#include "connection.h"
// #include "temperature.h"

static inline void initADC(void)
{                        // czujnik wody
  ADMUX |= (1 << REFS0); //ustawienie napięcia ref na napięcie zasilania
  //ADMUX |= ((1<<MUX0)| (1<<MUX2)); //wybor kanalu, w tym wypadku kanal 7 (00111)
  ADCSRA |= (1 << ADPS1) | (1 << ADPS0); //czestotliwosc na 8
  ADCSRA |= (1 << ADEN);                 //uruchomienie przetwornika ADC
}

int main(void)
{
  // inicjalizacja naszych rzeczy
  DDRA |= (1 << PA6);
  DDRA |= (1 << PA7);
  initADC();
  LCD_Init();

  //zmienne przechowujace wartosci
  uint16_t liquidsensor_value = 0;
  int busy = 0;
  char text[20];
  int time_sum = 0;

  char printbuff[100];

  bool light_is_on = false;
  bool roof_is_up = false;
  int dht_value[4];
  reset(dht_value);

  motor_stop();
  while (1)
  {
  }
  return 0;

  while (1)
  {
    uint16_t pot_val = waterpot_value();
    uint16_t tank_val = watertank_value();
    // busy = watertank_switch();
    busy = 0;
    // waterpot_switch();
    if (busy != 1)
    {
      sprintf(text, "DH  T  WP  WT");
      LCD_String(text);
      // tank_val = percent(tank_val);
      sprintf(text, "%d, %d, %d, %d ", dht_value[2], dht_value[3], pot_val, tank_val);
      LCD_Command(0xC0); /* Go to 2nd line*/
      LCD_String(text);
    }
    else
    {
      sprintf(text, "Dolej wody!");
      LCD_String(text);
      // sprintf(text, "%d / %d", tank_val, MIN_VAL);
      LCD_Command(0xC0);
      LCD_String(text);
    }
    // waterpot_switch();
    // temperature_switch(dht_value, light_is_on, roof_is_up);
    // tank_val = percent(tank_val);
    _delay_ms(1000);
    LCD_Clear();
  }

  return (0);
}
