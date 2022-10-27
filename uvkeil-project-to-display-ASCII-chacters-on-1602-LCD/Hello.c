#include "stm32f4xx.h"

void initialize( )
{
	RCC -> AHB1ENR |= 0X1;
	RCC -> AHB1ENR |= 0x1<<3;
	RCC -> AHB1ENR |= 0X1<<4;
	
}
void configure ()
{
	int pin=0;
	for ( pin =0;pin<=2;pin++)
	{
		GPIOD->MODER &=~(0X3<<(pin*2));
		GPIOD->MODER |=(0X1<<(pin*2));
		GPIOD->OTYPER &=~(0X1<<(pin));
		GPIOD->OSPEEDR |=(0X3<<(pin*2));
		GPIOD->PUPDR &=~(0X3<<(pin*2));
		}
	for ( pin =0;pin<=7;pin++)
	{
		GPIOE->MODER &=~(0X3<<(pin*2));
		GPIOE->MODER |=(0X1<<(pin*2));
		GPIOE->OTYPER &=~(0X1<<(pin));
		GPIOE->OSPEEDR |=(0X3<<(pin*2));
		GPIOE->PUPDR &=~(0X3<<(pin*2));
		}
	//pin = 0;
		//GPIOD->MODER &=~(0X3<<(pin*2));
		//GPIOD->OTYPER &=~(0X1<<(pin));
		//GPIOD->OSPEEDR |=(0X3<<(pin*2));
		//GPIOD->PUPDR &=~(0X3<<(pin*2));
	pin = 12;
		GPIOD->MODER &=~(0X3<<(pin*2));
		GPIOD->MODER |=(0X1<<(pin*2));
		GPIOD->OTYPER &=~(0X1<<(pin));
		GPIOD->OSPEEDR |=(0X3<<(pin*2));
		GPIOD->PUPDR &=~(0X3<<(pin*2));
	
}
void delay_us(){
	int i;
	for(i=0;i<10000;i++){
		;
	}
}
void delay(int us){
	int i;
	for(i=0;i<=us;i++){
		delay_us();
	}
}
void LCD_WRITE_COMMAND(unsigned char cmd)
{
	GPIOD->ODR &=~(0X1);//RS = 0
	GPIOD->ODR &=~(0X2);// RW = 0
	GPIOD->ODR |=(0X4);//E = 1
	GPIOE->ODR &=~(0XFF);
	GPIOE->ODR |=cmd;
	delay(25);
	GPIOD->ODR &=~ (0X4);// E = 0
	delay(250);
	
}
void LCD_WRITE_DATA(unsigned int cmd)
{
	GPIOD->ODR |=(0X1);//RS = 1
	GPIOD->ODR &=~(0X2);// RW = 0
	GPIOD->ODR |=(0X4);//E = 1
	GPIOE->ODR &=~(0XFF);
	GPIOE->ODR |=cmd;
	delay(25);
	GPIOD->ODR &=~ (0X4);// E = 0
	delay(250);
	
}
void LCD_configure(void)
{
	LCD_WRITE_COMMAND (0x38);
	LCD_WRITE_COMMAND(0x6);
	LCD_WRITE_COMMAND(0x2);
	LCD_WRITE_COMMAND(0x1);
	LCD_WRITE_COMMAND(0xF);
}
void LCD_WRITE_MESSAGE(void){
	//LCD_WRITE_DATA(0x33);
	//LCD_WRITE_DATA(0x31);
	//LCD_WRITE_DATA(0x33);
	//LCD_WRITE_DATA(0x20);
	//LCD_WRITE_DATA(0x41);
	//LCD_WRITE_DATA(0x4E);
	//LCD_WRITE_DATA(0x44);
	//LCD_WRITE_DATA(0x20);
	//LCD_WRITE_DATA(0x33);
	//LCD_WRITE_DATA(0x32);
	//LCD_WRITE_DATA(0x39);
	
	LCD_WRITE_DATA(0x32);
	LCD_WRITE_DATA(0x39);
	LCD_WRITE_DATA(0x35);
}
int main()
{
	initialize();
	configure();
	LCD_configure();
	LCD_WRITE_MESSAGE();
	while(1){
		if(GPIOA->IDR &0x1){
		int pin = 12;
		GPIOD->ODR |=0x1<<pin;
		}
	}
}
