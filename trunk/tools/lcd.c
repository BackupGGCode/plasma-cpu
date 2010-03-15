/*--------------------------------------------------------------------
 * TITLE: Lcd screen 
 * AUTHOR: Ali Diouri (alidiouri@gmail.com)
 * DATE CREATED: 31/07/2009
 * FILENAME: lcd.c
 * PROJECT: 
 * COPYRIGHT: Software placed into the public domain by the author.
 *    Software 'as is' without warranty.  Author liable for nothing.
 * DESCRIPTION:
 *    write characters in lcd screen
 *--------------------------------------------------------------------*/
#include "plasma.h"
#define MemoryRead(A) (*(volatile unsigned long*)(A))
#define MemoryWrite(A,V) *(volatile unsigned long*)(A)=(V)
 
/************************GPIO0_out***********************************/
/*0 1 2 3 4 5 6 7 8 9 10 1 2 3 4 5 6 7 8 9 20 1 2 3 4 5 6 7 8 9 30 1*/
/*|  0--7  led  | E R R |  SF_D | |    VGA   |  				   |*/
/*|  			|  	W S	|  LCD  | |B G R H V |	                   |*/
/*|             |  		|  DATA | |L R E S S |                     |*/
/*|             | L C D |       | |U E D Y Y |                     |*/
/*|             |       |       | |E E   N N |                     |*/
/*|             |       |       | |  N   C C |                     |*/
/********************************************************************/	

/**************************** LCD Declaration **************************************/					
const int LCD_D_SHIFT = 11;
const int LCD_RS = 0x0400;                                                 
const int LCD_RW = 0x0200;	        /* always low: we never read the LCD */        
const int LCD_E  = 0x0100;                                                 
/***********************************************************************************/

/**************************** Clock = 12.5 MHz   / 80 ns *****************************/

/***************************   Time Functions  ***************************************/

// delay 1 µs
void delay1us(void) {                
  int i;
  for (i =50/4; i>0; --i) { }
}

// delay 40 µs
void delay40us(void) {
  int i;
  for (i = 2000/4; i>0; --i) { }
}

// delay 1 ms
void delay1ms(void) {
  int i;
  for (i = 500000/4; i>0; --i) { }
}

/*******************************************************************************************/


/******************************   LCD_E Command ********************************************/

//pulse LCD_E High for 12 clock cycles for 50 MHz
void HoldPulse_e12CC(void) {
  int i;
  MemoryWrite(GPIO0_OUT, LCD_E);
  for(i=0;i<12/4;i++){}
  MemoryWrite(GPIO0_CLEAR,LCD_E);
}
/********************************************************************************************/


/******************************  Write Functions **********************************************/	

/*** write characters ***/
void write_char_lcd(unsigned char ch) 						// ex: char=0x6c   
{                                                                         
  int lcd_output;
  int i;
  // upper nibble
  lcd_output = (ch & 0xf0) << (LCD_D_SHIFT - 4); 			// lcd_output= 0x3000			(shift_left=7)			
  lcd_output |= LCD_RS;                                     // lcd_output= 0x3400   --> LCD_RS =1  LCD_RW=0    SF_D=0110
  MemoryWrite(GPIO0_OUT,lcd_output);
  for(i=0;i<2;i++){}                                        // hold LCD_RS LCD_RW SF_D stable for 40ns before LCD_E goes high
  HoldPulse_e12CC();                                        // LCD_E high for 12 Clock cycles
  for(i=0;i<1;i++){}
  MemoryWrite(GPIO0_CLEAR,lcd_output);					    //  LCD_RS=0 LCD_RW=0
  delay1us();
 
 // lower nibble
  lcd_output = (ch & 0x0f) << LCD_D_SHIFT;         			// lcd_output= 0x6000     (shift_left=11)
  lcd_output |= LCD_RS;                          			// lcd_output= 0x6400  --> LCD_RS =1   LCD_RW=0    SF_D=1010
  MemoryWrite(GPIO0_OUT, lcd_output);						// write lower nibble
  for(i=0;i<2;i++){}                                        // hold LCD_RS LCD_RW SF_D stable for 40ns before LCD_E goes high 
  HoldPulse_e12CC();										// LCD_E high for 12 Clock cycles
  for(i=0;i<1;i++){}
  MemoryWrite(GPIO0_CLEAR,lcd_output);						// LCD_RS=0 LCD_RW=0
  delay40us();                                              // delay 40us for the next write char lcd
}

/*** write command for initialisation ***/
 void write_command4_lcd(unsigned char ch)                  // ex: ch =0x03
{                           
  int lcd_output;                                             
  int i;
  // write lower nibble: 
  lcd_output = (ch & 0x0f) << LCD_D_SHIFT;          		 // lcd_output= 0x0180 (shift_left=11)
  MemoryWrite(GPIO0_OUT, lcd_output);                        // write lower nibble
  for(i=0;i<2;i++){}                                         // hold LCD_RS LCD_RW SF_D stable for 40ns before LCD_E goes high 
  HoldPulse_e12CC();                                         // LCD_E high for 12 Clock cycles
  for(i=0;i<1;i++){}
  MemoryWrite(GPIO0_CLEAR,lcd_output);
  for(i=0;i<2;i++){}
}

/*** write command for configuration ***/
void write_command8_lcd(unsigned char ch)                    // ex: ch=0x28        
{  
  int lcd_output;       
  int i;
  
  //upper nibble
  lcd_output = (ch & 0xf0) << (LCD_D_SHIFT-4);			     // lcd_output= 0x1000    (shift_left=4)
  MemoryWrite(GPIO0_OUT, lcd_output);                        // write upper nibble
  for(i=0;i<2;i++){}                                         // hold LCD_RS LCD_RW SF_D stable for 40ns before LCD_E goes high 
  HoldPulse_e12CC();                                         // LCD_E high for 12 Clock cycles
  for(i=0;i<1;i++){}
  MemoryWrite(GPIO0_CLEAR,lcd_output);
  delay1us();
  
  //lower nibble
  lcd_output = (ch & 0x0f) << LCD_D_SHIFT;					 // lcd_output= 0x0600     (shift_left=11)
  MemoryWrite(GPIO0_OUT, lcd_output);                        // write lower nibble
  for(i=0;i<2;i++){}                                         // hold LCD_RS LCD_RW SF_D stable for 40ns before LCD_E goes high 
  HoldPulse_e12CC();                                         // LCD_E high for 12 Clock cycles
  for(i=0;i<1;i++){}
  MemoryWrite(GPIO0_CLEAR,lcd_output);
  delay40us();                                               // delay 40us for the next lcd write command 
}

/****************************************************************************************************************/

/************************************  Function Initialization ***************************************************/
void initialize_lcd(void) {
  int i;

  for (i=0; i<15; i++) {            // wait 15 ms
    delay1ms();
  }

  write_command4_lcd(0x03);         // write SF_D<11:8> =0x3 and pulse lcd_E high for 12 clock cycles 

  for (i=0; i<5; i++) {             //  wait 5 ms
    delay1ms();           
  }

  write_command4_lcd(0x03);			// write SF_D<11:8> =0x3 and pulse lcd_E high for 12 clock cycles 
  
  
  for (i=0; i<100; i++) {           //  wait 100 us
    delay1us();
  };

  write_command4_lcd(0x03);			// write SF_D<11:8> =0x3 and pulse lcd_E high for 12 clock cycles 
 
  
  for (i=0; i<40; i++) {            // wait 40 us
    delay1us();
  };
  
  write_command4_lcd(0x02);			// write SF_D<11:8> =0x2 and pulse lcd_E high for 12 clock cycles 

  for (i=0; i<40; i++) {            // wait 40 us
    delay1us();
  }
  
}
/*************************************************************************************************************************/


/*********************************** Function Configuration **************************************************************/
void configure_lcd(void)
{
  write_command8_lcd(0x28);         // issue function Set Command 0x28
  write_command8_lcd(0x06);         // issue an Entry Mode Set 0x06
  write_command8_lcd(0x0c);         // issue a Display On/Off Command 0x0c
  write_command8_lcd(0x01);         // clear display command
  delay1ms();                       // |
  delay1ms();                       // |  wait 2 ms
}
/*************************************************************************************************************************/ 


/************************************** Main Function ********************************************************************/
int main(void)
{
  initialize_lcd();  // initialize
  configure_lcd();   // Configure
    
  write_command8_lcd(0x81);             // the first line 
  
  write_char_lcd(0x53);  				// S
  write_char_lcd(0x54); 				// T
  write_char_lcd(0x41); 				// A
  write_char_lcd(0x47); 				// G
  write_char_lcd(0x45); 				// E
  write_char_lcd(0x00);
  write_char_lcd(0x4c);                	// L
  write_char_lcd(0x49);				   	// I
  write_char_lcd(0x52);				   	// R
  write_char_lcd(0x4d); 			   	// M
  write_char_lcd(0x4d); 			   	// M

  write_command8_lcd(0xc3);            // the second line
  
  write_char_lcd(0x41); 				// A
  write_char_lcd(0x4c);                	// L
  write_char_lcd(0x49);				   	// I
  write_char_lcd(0x00);
  write_char_lcd(0x44);                 // D
  write_char_lcd(0x49);				   	// I
  write_char_lcd(0x4f);         		// O
  write_char_lcd(0x55);                 // U
  write_char_lcd(0x52);				   	// R
  write_char_lcd(0x49);				   	// I
  return 0;
}