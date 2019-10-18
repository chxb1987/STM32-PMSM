#include "display_driver.h"
#include "stm32f10x_gpio.h"
#include "stddef.h"

GPIO_InitTypeDef GPIO_InitStructure;


#define TAR_IO_GROUP	GPIOB
#define PIN_SCK			GPIO_Pin_7			
#define PIN_RCK			GPIO_Pin_6
#define PIN_SI			GPIO_Pin_5

static void output_sck(uint8_t dat){
	GPIO_WriteBit (TAR_IO_GROUP, PIN_SCK, dat);
}

static void output_rck(uint8_t dat){
	GPIO_WriteBit (TAR_IO_GROUP, PIN_SCK, dat);
}

static void output_sdi(uint8_t dat){
	GPIO_WriteBit (TAR_IO_GROUP, PIN_SI, dat);
}

void init(struct dirver_74hc595* pdev){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	/* Configure PD0 and PD2 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = PIN_SCK 
								| PIN_RCK
								| PIN_SI;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(TAR_IO_GROUP, &GPIO_InitStructure);

	pdev->output_sck = output_sck;
	pdev->output_rck = output_rck;
	pdev->output_sdi = output_sdi;

}

void hc595_init(struct dirver_74hc595* pdev){
	pdev->init = init;
	pdev->init(pdev);
}

void hc595_write(struct dirver_74hc595* pdev, uint8_t data){
	
	for(int i=0; i<8; i++){
		pdev->output_sdi((data >> i)&0x01);
		pdev->output_rck(0x00);
		pdev->output_rck(0x01);
	}
}

void hc595_output(struct dirver_74hc595* pdev){

}




