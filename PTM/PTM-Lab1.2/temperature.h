#ifndef TEMPERATURE

#include "library.h"

#define DHT11_PIN PA4
#define MIN_VAL_DH 1
#define MAX_VAL_DH 3
#define MIN_VAL_T 1
#define MAX_VAL_T 3

char text[20];


void Request() /* Microcontroller send start pulse/request */
{
	DDRA |= (1 << DHT11_PIN);
	PORTA &= ~(1 << DHT11_PIN); /* set to low pin */
	_delay_ms(50);				/* wait for 20ms */
	PORTA |= (1 << DHT11_PIN);	/* set to high pin */
}

void Response() /* receive response from DHT11 */
{

	DDRA &= ~(1<<DHT11_PIN);
	while(PINA & (1<<DHT11_PIN));
	while((PINA & (1<<DHT11_PIN))==0);
	while(PINA & (1<<DHT11_PIN));

}

uint8_t Receive_data() /* receive data */
{
	uint8_t c = 0;
	for (int q = 0; q < 8; q++)
	{
		PORTA &= ~(1 << DHT11_PIN);	 /* set to low pin */
		_delay_ms(50);				 /* wait for 20ms */
		if (PINA & (1 << DHT11_PIN)) /* if high pulse is greater than 30ms */
			c = (c << 1) | (0x01);	 /* then its logic HIGH */
		else						 /* otherwise its logic LOW */
			c = (c << 1);
		PORTA |= (1 << DHT11_PIN); /* set to high pin */
		_delay_ms(20);			   /* wait for 20ms */
	}
	
	LCD_Clear();
	sprintf(text, "%s",c);
	LCD_String(text);
	_delay_ms(500);
	return c;
}

int *temperature_level(int dht_value[4])
{
	char text[20];
	dht_value[0] = 0;
	dht_value[1] = 0;
	uint8_t I_RH, D_RH, I_Temp, D_Temp, CheckSum;

	Request(); /* send start pulse */
	LCD_Clear();
	sprintf(text, "Request()");
	LCD_String(text);
	_delay_ms(250);
	_delay_ms(10);

	Response(); /* receive response */
	LCD_Clear();
	sprintf(text, "Response()");
	LCD_String(text);
	_delay_ms(250);




	I_RH = Receive_data();	   /* store first eight bit in I_RH */
	D_RH = Receive_data();	   /* store next eight bit in D_RH */
	I_Temp = Receive_data();   /* store next eight bit in I_Temp */
	D_Temp = Receive_data();   /* store next eight bit in D_Temp */
	CheckSum = Receive_data(); /* store next eight bit in CheckSum */
	dht_value[2] = I_RH;
	dht_value[3] = I_Temp;
	_delay_ms(10);


	if (I_RH < MIN_VAL_DH)
		dht_value[0] = 1;
	if (I_RH > MAX_VAL_DH)
		dht_value[0] = 2;
	if (I_Temp < MIN_VAL_T)
		dht_value[1] = 4;
	if (I_Temp > MAX_VAL_T)
		dht_value[1] = 5;
	return dht_value;
}
void reset(int dht[4])
{
	dht[0] = 0;
	dht[1] = 0;
	dht[2] = 0;
	dht[3] = 0;
}

// int temperature_level()
// {
// 	uint16_t liquidsensor_value = temperature_value();
// 	if (liquidsensor_value < MIN_VAL)
// 		return 1;
// 	if (liquidsensor_value > MAX_VAL)
// 		return 2;
// 	return 0;
// }

#endif
