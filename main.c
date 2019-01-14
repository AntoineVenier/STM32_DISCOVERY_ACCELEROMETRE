/*-------------------------------------*/
/*-------Projet SPI Accelerometre------*/
/*-------------------------------------*/


#include "stm32f4xx_hal.h"

void conf_init(void);
SPI_HandleTypeDef SPIAcc;
unsigned char spiSendData[2];
unsigned char spiReceiveData[6];


int main (void)
{	
		conf_init();
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_RESET);
		spiSendData[0]=0x20;
		spiSendData[1]=0x17;
		HAL_SPI_Transmit(&SPIAcc,spiSendData,2,50);
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_SET);
	
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_RESET);
		spiSendData[0]=0x20|0x80;
		HAL_SPI_Transmit(&SPIAcc,spiSendData,1,50);
		HAL_SPI_Receive(&SPIAcc,spiReceiveData,1,50);
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_SET);
	
	
	
    while(1)
    {
        
        
    }
    
    
    
}

void conf_init (void)
{
	
	//MOSI MISO configuration
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef SPI_pins;
	SPI_pins.Pin = GPIO_PIN_5 | GPIO_PIN_6| GPIO_PIN_7;
	SPI_pins.Mode = GPIO_MODE_AF_PP;
	SPI_pins.Alternate = GPIO_AF5_SPI1;
	SPI_pins.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOA,&SPI_pins);
	
	
	//CS configuration
	__HAL_RCC_GPIOE_CLK_ENABLE();
	GPIO_InitTypeDef SPI_CS_pin;
	SPI_CS_pin.Pin = GPIO_PIN_3;
	SPI_CS_pin.Mode=GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOE, &SPI_CS_pin);
	
	
		//LED configuration
	__HAL_RCC_GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef LED_pin;
	LED_pin.Pin = GPIO_PIN_12 | GPIO_PIN_13;
	LED_pin.Mode=GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOE, &LED_pin);
	
	
	//SPI configuration
	__HAL_RCC_SPI1_CLK_ENABLE();
  SPIAcc.Instance = SPI1;
	SPIAcc.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	SPIAcc.Init.Direction = SPI_DIRECTION_2LINES;
	SPIAcc.Init.CLKPhase = SPI_PHASE_1EDGE;
	SPIAcc.Init.CLKPolarity = SPI_POLARITY_LOW;
	SPIAcc.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	SPIAcc.Init.DataSize = SPI_DATASIZE_8BIT;
	SPIAcc.Init.FirstBit = SPI_FIRSTBIT_MSB;
	SPIAcc.Init.NSS = SPI_NSS_SOFT;
	SPIAcc.Init.TIMode = SPI_TIMODE_DISABLE;
	SPIAcc.Init.Mode = SPI_MODE_MASTER;
	HAL_SPI_Init(&SPIAcc);
  
  
 
}
