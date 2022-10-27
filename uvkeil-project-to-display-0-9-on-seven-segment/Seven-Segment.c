#include "stm32f4xx.h"

void initialize(){
	RCC->AHB1ENR |=0X2;
}

void configure(){
	int pin;
	for (pin = 0; pin <= 7; pin++){
		GPIOB->MODER &=~ (0X3 << (pin * 2));
		GPIOB->MODER |= (0X1 << (pin * 2));
		GPIOB->OTYPER &=~ (0X1 << (pin));
		GPIOB->OSPEEDR |= (0X3 << (pin * 2));
		GPIOB->PUPDR &=~ (0X3 << (pin * 2));
	}
}

void delay(){
	int j = 0;
	for (j=0; j<10000000; j++);
}


int main(void){
	int counter = 0;
	initialize();
	configure();
	while(1){
		delay();
		if(counter>9){
			counter=0;
		}
		switch(counter){
			case 0:
				GPIOB->ODR &=~(0xFF);
				GPIOB->ODR |= 0x40;
				break;
			case 1:
				GPIOB->ODR &=~(0xFF);
				GPIOB->ODR |= 0x79;
				break;
			case 2:
				GPIOB->ODR &=~(0xFF);
				GPIOB->ODR |= 0x24;
				break;
			case 3:
				GPIOB->ODR &=~(0xFF);
				GPIOB->ODR |= 0x30;
				break;
			case 4:
				GPIOB->ODR &=~(0xFF);
				GPIOB->ODR |= 0x19;
				break;
			case 5:
				GPIOB->ODR &=~(0xFF);
				GPIOB->ODR |= 0x12;
				break;
			case 6:
				GPIOB->ODR &=~(0xFF);
				GPIOB->ODR |= 0x02;
				break;
			case 7:
				GPIOB->ODR &=~(0xFF);
				GPIOB->ODR |= 0x78;
				break;
			case 8:
				GPIOB->ODR &=~(0xFF);
				GPIOB->ODR |= 0x00;
				break;
			case 9:
				GPIOB->ODR &=~(0xFF);
				GPIOB->ODR |= 0x10;
				break;
		}
		counter++;
	}
	
}