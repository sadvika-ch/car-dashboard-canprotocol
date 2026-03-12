#include "main.h"
#include "dht11.h"

// DHT11 Read 8 bits of data
uint8_t DHT11_Read(void) {
	uint8_t data = 0;
	for (uint8_t i = 0; i < 8; i++) {
		while (!(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)))
			; // wait for the pin to go high
		delay_us(40); // wait for 40 us
		if (!(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN))) // if the pin is low after 40us, it's a 0
		{
			data &= ~(1 << (7 - i));   // write 0
		} else {
			data |= (1 << (7 - i));  // if it's still high, it's a 1
		}
		while ((HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)))
			;  // wait for the pin to go low again
	}
	return data;
}

// DHT11 Start signal and response check
uint8_t DHT11_Start(void) {
	Set_Pin_Output(DHT11_PORT, DHT11_PIN);  // set the pin as output
	HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, 0);   // pull the pin low
	delay_us(18000);   // wait for 18ms
	HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, 1);   // pull the pin high
	delay_us(20);   // wait for 20us
	Set_Pin_Input(DHT11_PORT, DHT11_PIN);    // set the pin as input

	uint8_t Response = 0;
	delay_us(40); // Wait for DHT11 to pull low
	if (!(HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN))) // if the pin is low
	{
		delay_us(80);   // wait for 80us
		if ((HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)))
			Response = 1;  // if the pin is high, then sensor has responded
	}
	while ((HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)))
		;   // wait for the pin to go low again

	return Response;
}

void DWT_Delay_Init(void) {
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CYCCNT = 0;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

void delay_us(uint32_t us) {
	uint32_t start_tick = DWT->CYCCNT;
	uint32_t delay_ticks = us * (SystemCoreClock / 1000000U);
	while (DWT->CYCCNT - start_tick < delay_ticks)
		;
}

// Function to set GPIO pin as input
void Set_Pin_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}
// Function to set GPIO pin as output
void Set_Pin_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void Read_Temp_Hum(DHT11_Data_t *sensor_data) {

	uint8_t RHI, RHD, TCI, TCD, SUM;

// Attempt to read from DHT11
	if (DHT11_Start() == 1) {
		RHI = DHT11_Read();
		RHD = DHT11_Read();
		TCI = DHT11_Read();
		TCD = DHT11_Read();
		SUM = DHT11_Read();

		if (RHI + RHD + TCI + TCD == SUM) {
			sensor_data->temperature = TCI; // DHT11 only provides integer part for temperature
			sensor_data->humidity = RHI; // DHT11 only provides integer part for humidity
		}
	}
}
