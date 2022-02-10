#ifndef CONNECTION

#include "library.h"
#include "waterpot.h"
#include "watertank.h"
#include "temperature.h"
#include "motor.h"
#include "pump.h"

int WhichSwitch()
{
    if (bit_is_clear(SWITCH_PIN, SWITCH_UP)) //jesli jest wcisnieta gorna krancowka
        return 0;

    if (bit_is_clear(SWITCH_PIN, SWITCH_DOWN)) //jesli jest wcisnieta dolna krancowka
        return 1;
    return 2;
}

void led(int roof)
{
    if (roof == 0)
    {
        LED_PORT &= ~(1 << LED_DOWN);
        LED_PORT |= (1 << LED_UP);
    }
    if (roof == 1)
    {
        LED_PORT &= ~(1 << LED_UP);
        LED_PORT |= (1 << LED_DOWN);
    }
    if (roof != 1 && roof != 0)
    {
        LED_PORT &= ~(1 << LED_UP);
        LED_PORT &= ~(1 << LED_DOWN);
    }
}

void waterpot_switch(uint16_t pot_val, bool pump_is_on)
{
    if (waterpot_level(pot_val) == 1)
    {
        // pump_on();
        pump_is_on = true;
    }
    if (waterpot_level(pot_val) == 2)
        if (pump_is_on) //jesli pompa wlaczona
        {
            // pump_off(); //wylacz pompe
            pump_is_on = false;
        }
}

bool watertank_switch(uint16_t tank_val)
{
    if (watertank_level(tank_val) == 1)
        return true;
    else
        return false;
}

void roof_up_down()
{
    bool choice = false;
    char text[20];
    if (bit_is_set(BUTTON_PIN, BUTTON_UP) || bit_is_set(BUTTON_PIN, BUTTON_DOWN))
    {
        LCD_Clear();
        while (bit_is_clear(BUTTON_PIN, BUTTON_UP) && bit_is_set(SWITCH_PIN, SWITCH_UP))
        {
            motor_right(); // ciagnij linke
            sprintf(text, "Podnosze dach");
            LCD_String(text);
            choice = true;
            while (bit_is_clear(BUTTON_PIN, BUTTON_UP) && bit_is_set(SWITCH_PIN, SWITCH_UP))
                ;
        }
        LCD_Clear();
        if (choice)
            motor_stop();

        while (bit_is_clear(BUTTON_PIN, BUTTON_DOWN) && bit_is_set(SWITCH_PIN, SWITCH_DOWN))
        {
            motor_left(); // luzuj linke
            sprintf(text, "Opuszczam dach");
            LCD_String(text);
            choice = true;
            while (bit_is_clear(BUTTON_PIN, BUTTON_DOWN) && bit_is_set(SWITCH_PIN, SWITCH_DOWN))
                ;
        }
        LCD_Clear();
        if (choice)
            motor_stop();
    }
}

uint16_t percent(uint16_t tank)
{
    int tank_t = tank;
    tank = tank_t * 100 / 400;
    return tank;
}

uint16_t redo(uint16_t a)
{
    const int B = 4275; // B value of the thermistor
    const long int R0 = 100000;
    float R = 1023.0 / a - 1.0;
    R = R0 * R;
    uint16_t temperature = (1.0 / (log(R / R0) / B + 1 / 298.15) - 273.15) * 100;
    return temperature;
}

#endif