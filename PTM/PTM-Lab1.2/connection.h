#ifndef CONNECTION

#include "library.h"
#include "waterpot.h"
#include "watertank.h"
#include "temperature.h"
#include "motor.h"
#include "lcd.h"

#define TIME 10000
#define MAX_TEMP 0
#define MAX_DH 0
#define MAX_WP 300
#define MAX_WT 300

void jakasfunkcja()
{

    // int waterpot_val = waterpot_level(waterpot_value());
    // int watertank_val = watertank_level(watertank_value());
}

void waterpot_switch()
{
    char text[20];
    switch (waterpot_level())
    {
    case 1:
        //wlacz pompe wody
        break;
    case 2:
        //zaduzo wody w doniczce(nie powinno miec miejsca)
        break;
    case 0:
        //poziom poprawny, nic nie rob
        break;

    default:
        break;
    }
}

int watertank_switch()
{
    char text[20];
    switch (watertank_level())
    {
    case 1:
        // za malo wody w zbiorniku, dolej wode
        return 1;
    case 2:
        //za duzo wody w zbiorniku, ochrzań czlowieka
        break;
    case 0:
        //poziom w normie, nic nie rob
        break;

    default:
        break;
    }
    return 0;
}

int *temperature_switch(int dht_value[4], bool light_is_on, bool roof_is_up)
{

    temperature_level(dht_value);

    switch (dht_value[0])
    {
    case 1: // wolgotnosc jest za mala, opusc klapy
        if (roof_is_up)
        {
            //opusc klape
        }
        roof_is_up = false;

    case 2: // wolgotnosc jest za duza, podnies klapy
        if (!roof_is_up)
        {
            //podnies klape
        }
        roof_is_up = true;
        break;
    case 0:
        //poziom w normie, nic nie rob
        break;
    default:
        break;
    }

    switch (dht_value[1])
    {
    case 4: //temperatura za niska, odpal swiatlo
        if (!light_is_on)
        {
            //odpal swiatlo
        }
        light_is_on = true;
        break;
    case 5: //temperatura za wysoka, zgas swiatlo
        if (light_is_on)
        {
            //zgas swiatlo
        }
        light_is_on = false;
        break;
    case 0:
        //poziom w normie, nic nie rob
        break;
    default:
        break;
    }
    return dht_value;
}

uint16_t percent(uint16_t tank)
{
    // int pot_v = pot;
    int pot_t = tank;
    // pot = pot_v*100/MAX_WP;
    tank = pot_t * 100 / MAX_WT;
    return tank;
}

#endif