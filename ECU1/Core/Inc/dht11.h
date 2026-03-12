/*
 * dht11.h
 *
 *  Created on: Feb 27, 2026
 *      Author: Dhiyanesh
 */

#ifndef INC_DHT11_H_
#define INC_DHT11_H_

/* USER CODE BEGIN PV */
typedef struct {
	uint8_t temperature;
	uint8_t humidity;
} DHT11_Data_t;

#define DHT11_PORT GPIOG
#define DHT11_PIN GPIO_PIN_12

uint8_t DHT11_Read(void);
uint8_t DHT11_Start(void);
void DWT_Delay_Init(void);
void delay_us(uint32_t);
void Set_Pin_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void Set_Pin_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void Read_Temp_Hum(DHT11_Data_t *data);

#endif /* INC_DHT11_H_ */
