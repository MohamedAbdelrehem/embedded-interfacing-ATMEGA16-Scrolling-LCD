/*
 * WEEk3-LCD.c  BONUS
 *
 * Created: 10/24/2022 9:46:09 AM
 * Author : Mohamed
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#define LCD_DATA PORTB
#define LCD_CONT PORTA
#define en PA6
#define rs PA7

void init_LCD(void);
void LCD_cmd(char command);
void LCD_write(char data);
void LCD_PASS_String (char *str);

int main(void)
{
	DDRB = 0xFF	;							//out	data
	DDRA = 0xFF;							//out en,rs
	
	init_LCD();								//initialize the LCD function
	_delay_ms(5);						//				  x
	LCD_cmd (0x0C);						//hide cursor "CSE_"

  LCD_PASS_String("CSE 22 Mohamed");				//edit from the main code so it scroll

 
  //while (1)								// so it scroll infinitely
  //{				
	  
  //}

	}

void init_LCD(void){
	
	
	
	LCD_cmd(0x38);				//Initialize 8bit mode
	_delay_ms(1);
	LCD_cmd(0x1);				//clear
	_delay_ms(1);
	LCD_cmd(0x6);				
	_delay_ms(1);

	LCD_cmd(0x0E);				//First line start
	_delay_ms(1);
	
	} 
	
void LCD_cmd( char command)
{
	LCD_CONT = _BV(en);
	LCD_DATA = command;
	_delay_ms(1);
	LCD_CONT = 0x00;
	_delay_ms(1);
}

void LCD_write( char data){
	LCD_CONT = _BV(en) | _BV(rs);
	LCD_DATA = data;
	_delay_ms(1);
	LCD_CONT = _BV(rs);
	_delay_ms(1);
	
}
void LCD_PASS_String (char *str)		
{	
	int	LCD_Horizontal = 16;
		for (int j=LCD_Horizontal;j>0;j--)	//shift cursor 16 times so type out of screen
		{
			LCD_cmd(0x14);
		}
	
		for(int i=0;str[i]!=0;i++)	//write the word out of the screen until the 0 end of the char (string)
		{
			LCD_write (str[i]);
		}
		
		for (int i=0;str[i]!=0;i++)	//shift the screen 
		{
			LCD_cmd(0x18);				//shift the entire screen left
			_delay_ms(100);
		}	
		for (int i=0;i<LCD_Horizontal;i++)	//shift the screen 16 time so text fully go out
		{
			LCD_cmd(0x18);				//shift the entire screen left
			_delay_ms(100);
		}
}

//old way no screen out
/*
int i,j;
for (j=16;j>0;j--)
{
	for (int m=j;m>0;m--)		//no of spaces before the word
	{
		LCD_write (' ');
	}
	
	for(i=0;str[i]!=0;i++)		//loop for string
	{
		LCD_write (str[i]);
	}
	_delay_ms(200);
	LCD_cmd(0x01);				//clear screen
}
*/