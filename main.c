


#define F_CPU 16000000UL
#include <avr\io.h>
#include <util\delay.h>

#define control_bus PORTB
#define controlbus_direction DDRB
#define data_bus PORTD
#define databus_direction DDRD

#define rs 2
#define en 3
#define d4 4
#define d5 5
#define d6 6
#define d7 7


void LCD_CmdWrite( char a)
{
	if(a & 0x80) data_bus|=(1<<d7); else data_bus&= ~(1<<d7);
	if(a & 0x40) data_bus|=(1<<d6); else data_bus&= ~(1<<d6);
	if(a & 0x20) data_bus|=(1<<d5); else data_bus&= ~(1<<d5);
	if(a & 0x10) data_bus|=(1<<d4); else data_bus&= ~(1<<d4);
	control_bus &=~(1<<rs);control_bus |=(1<<en);
	_delay_ms(2);
	control_bus &=~(1<<en);

	_delay_ms(2);

	if(a & 0x08) data_bus|=(1<<d7); else data_bus&= ~(1<<d7);
	if(a & 0x04) data_bus|=(1<<d6); else data_bus&= ~(1<<d6);
	if(a & 0x02) data_bus|=(1<<d5); else data_bus&= ~(1<<d5);
	if(a & 0x01) data_bus|=(1<<d4); else data_bus&= ~(1<<d4);
	control_bus &=~(1<<rs);control_bus |=(1<<en);
	_delay_ms(2);
	control_bus &=~(1<<en);

	_delay_ms(2);
}




void LCD_DataWrite( char a)
{

	if(a & 0x80) data_bus|=(1<<d7); else data_bus&= ~(1<<d7);
	if(a & 0x40) data_bus|=(1<<d6); else data_bus&= ~(1<<d6);
	if(a & 0x20) data_bus|=(1<<d5); else data_bus&= ~(1<<d5);
	if(a & 0x10) data_bus|=(1<<d4); else data_bus&= ~(1<<d4);
	control_bus |=(1<<rs)|(1<<en);
	_delay_ms(2);
	control_bus &=~(1<<en);
	_delay_ms(2);

	if(a & 0x08) data_bus|=(1<<d7); else data_bus&= ~(1<<d7);
	if(a & 0x04) data_bus|=(1<<d6); else data_bus&= ~(1<<d6);
	if(a & 0x02) data_bus|=(1<<d5); else data_bus&= ~(1<<d5);
	if(a & 0x01) data_bus|=(1<<d4); else data_bus&= ~(1<<d4);
	control_bus |=(1<<rs)|(1<<en);
	_delay_ms(2);
	control_bus &=~(1<<en);
	_delay_ms(2);

}





void LCD_Init()
{
	controlbus_direction |= ((1<<rs)|(1<<en));
	databus_direction |= ((1<<d7)|(1<<d6)|(1<<d5)|(1<<d4));
	_delay_ms(2);
	LCD_CmdWrite(0x01); // clear display
	LCD_CmdWrite(0x02); // back to home
	LCD_CmdWrite(0x28); // 4bit,2line,5x7 pixel
	LCD_CmdWrite(0x06); // entry mode,cursor increments by cursor shift
	LCD_CmdWrite(0x0c); // display ON,cursor OFF
	LCD_CmdWrite(0x80); // force cursor to begin at line1

}

void LCD_Disp(const char *p)
{
	while(*p!='\0')
	{
		LCD_DataWrite(*p);
		p++; _delay_ms(2);
	}
}

void LCD_setCursor(int a, int b)
{
	int i=0;
	switch(b){
		case 0:LCD_CmdWrite(0x80);break;
		case 1:LCD_CmdWrite(0xC0);break;
		case 2:LCD_CmdWrite(0x94);break;
	case 3:LCD_CmdWrite(0xd4);break;}
	for(i=0;i<a;i++)
	LCD_CmdWrite(0x14);
}


int main()
{

LCD_Init();

	while(1)
	{

	LCD_setCursor(0,0);
	LCD_Disp("B1=");
	LCD_setCursor(3,0);
	LCD_Disp("28");

	LCD_setCursor(8,0);
	LCD_Disp("B2=");
	LCD_setCursor(11,0);
	LCD_Disp("29");

	LCD_setCursor(0,1);
	LCD_Disp("B3=");
	LCD_setCursor(3,1);
	LCD_Disp("33");

	LCD_setCursor(8,1);
	LCD_Disp("B4=");
	LCD_setCursor(11,1);
	LCD_Disp("89");

	_delay_ms(2000);
	//while(1);
	}

}
