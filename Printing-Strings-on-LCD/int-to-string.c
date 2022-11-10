#include "stm32f4xx.h"


char num_string[10];

void initialize( )
{
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
void LCD_WRITE_COMMAND(unsigned int cmd)
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
void LCD_WRITE_DATA(unsigned char cmd)
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
void num_to(int n){
	int size=10;
	char str[10];
	int i;
	for(i =0;i<size;i++){
		str[i] = n%10 +'0';
		n = n/10;
		num_string[size-i] = str[i];
		if(n==0){
			break;
		}
	}
}
void LCD_WRITE_MESSAGE()
{
	int i;
	char arr[12] = "IRFAN_SANDHU";
	num_to(746576);
	for(i=0;i<=12;i++){
		if(arr[i] != ' '){
			LCD_WRITE_DATA(arr[i]);
		}	
	}
	
}

int main()
{
	int new1;
	initialize();
	configure();
	LCD_configure();
	LCD_WRITE_MESSAGE();
}