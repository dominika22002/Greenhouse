#include "lcd.h"
#include "connection.h"

static inline void InitADC(void)
{
    ADMUX |= (1 << REFS0);                 //ustawienie napięcia ref na napięcie zasilania
    ADCSRA |= (1 << ADPS1) | (1 << ADPS0); //czestotliwosc na 8
    ADCSRA |= (1 << ADEN);                 //uruchomienie przetwornika ADC
}

void Initialization()
{
    MOTOR_DDR |= (1 << MOTOR_PIN1);    //Motor init
    MOTOR_DDR |= (1 << MOTOR_PIN2);    //Motor init
    PUMP_DDR |= (1 << PUMP_PIN);       //Pump init
    SWITCH_DDR |= (1 << SWITCH_UP);    //Switch init
    SWITCH_DDR |= (1 << SWITCH_DOWN);  //Switch init
    BUTTON_DDR |= (1 << BUTTON_UP);    //Button init
    BUTTON_DDR |= (1 << BUTTON_DOWN);  //Button init
    LED_DDR |= (1 << LED_UP);          //Button init
    LED_DDR |= (1 << LED_DOWN);        //Button init
    SWITCH_PORT |= (1 << SWITCH_UP);   //Switch pull up
    SWITCH_PORT |= (1 << SWITCH_DOWN); //Switch pull up
    BUTTON_PORT |= (1 << BUTTON_UP);   //Button pull up
    BUTTON_PORT |= (1 << BUTTON_DOWN); //Button pull up

    PUMP_PORT &= ~(1 << PUMP_PIN); //turn off the pump

    InitADC();
    LCD_Init();
}

int main(void)
{
    Initialization();
    //Variables
    char text[20];                  //LCD text buffor

    bool LCD_is_busy = false;       //tell us if water tank level is okay
    int roof = WhichSwitch();       //tell us if roof is up
    bool pump_is_on = false;

    _delay_ms(200); //wait to initialization

    while (1)
    {
        roof = WhichSwitch();
        led(roof);
        roof_up_down();
        uint16_t tank_val = watertank_value();
        uint16_t pot_val = percent(waterpot_value());
        uint16_t temp_val = redo(temp_value());

        uint16_t i = temp_val / 100;
        uint16_t j = temp_val - i * 100;

        LCD_is_busy = watertank_switch(tank_val);
        if (!LCD_is_busy)
        {
            sprintf(text, "Tem    Pot  Tank");
            LCD_String(text);
            if (j < 10)
                sprintf(text, "%d,0%d  %3d  %3d ", i, j, pot_val, tank_val);
            else
                sprintf(text, "%d,%2d  %3d  %3d ", i, j, pot_val, tank_val);
            LCD_Command(0xC0);
            LCD_String(text);
            waterpot_switch(pot_val,pump_is_on);
        }
        else
        {
            sprintf(text, "Dolej wody!");
            LCD_String(text);
            sprintf(text, "%d / %d", tank_val, WATERTANK_MIN);
            LCD_Command(0xC0);
            LCD_String(text);
        }
        _delay_ms(1000);
        LCD_Clear();
    }

    return 0;
}
