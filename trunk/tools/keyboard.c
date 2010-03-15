/*--------------------------------------------------------------------
 * TITLE: Header File Plasma RTOS application 
 * AUTHOR: Ali Diouri (alidiouri@gmail.com)
 * DATE CREATED: 31/07/2009
 * FILENAME: keyboard.c
 * PROJECT: Plasma RTOS application 
 * COPYRIGHT: Software placed into the public domain by the author.
 *    Software 'as is' without warranty.  Author liable for nothing.
 * DESCRIPTION:
 *    Functions' definition for Plasma RTOS application 
 *--------------------------------------------------------------------*/

//#include <stdio.h>
//#include "plasma.h"
//#define MemoryRead(A) (*(volatile unsigned long*)(A))
/*#define MemoryWrite(A,V) *(volatile unsigned long*)(A)=(V)*/
//#include "lcd.c"
#include "libc.c"

/* MasK */
#define xPS2_CLK 	0x00000800
#define xPS2_DATA 	0x00000400


int puts(const char *string);
int Data_GPIO_IN(void);
void write_command4_lcd(unsigned char ch);


/************************GPIO0_out***********************************/
/*0 1 2 3 4 5 6 7 8 9 10 1 2 3 4 5 6 7 8 9 20 1 2 3 4 5 6 7 8 9 30 1*/
/*|  0--7  led  | E R R |  SF_D | |    VGA   |  		   |*/
/*|  		|   W S	|  LCD  | |B G R H V |		           |*/
/*|             |  	|  DATA | |L R E S S |                     |*/
/*|             | L C D |       | |U E D Y Y |                     |*/
/*|             |       |       | |E E   N N |                     |*/
/*|             |       |       | |  N   C C |                     |*/
/********************************************************************/						

/************************* gpio0_in *********************************/
/*0 1 2 3 4 5 6 7 8 9 10 1 2 3 4 5 6 7 8 9 20 1 2 3 4 5 6 7 8 9 30 1*/
/*   SW  | BTN   |ROT| PS |  R					   |*/		
/*       |W S N E|A B|D  C|  T					   |*/
/*       |E O O	A|   |A  L|  C					   |*/		
/*       |S U R S|   |T  K|					   |*/	
/*	 |T T T T|   |A   |                                        |*/
/*	 |    H H|   |	  |                                        |*/
/********************************************************************/						





/************************** Get the Data from GPIOA_IN register *************************************/
/*int Data_GPIO_IN(void)*/
/*{*/
/*	return MemoryRead(GPIOA_IN);*/
/*}*/
/*************************************************************************************/

/**************************** Clock = 12.5 MHz   / 80 ns *****************************/
/***************************   Time Functions  ***************************************/
void delay1us(void) {                
  int i;
  for (i =50/4; i>0; --i) { }
  }
// delay 5 µs
void delay5us(void) {
  int i;
  for (i = 5; i>0; --i) { delay1us();}
}
  // delay 8 µs
void delay8us(void) {
  int i;
  for (i = 8; i>0; --i) { delay1us();}
}

// delay 10 µs
void delay10us(void) {
  int i;
  for (i = 10; i>0; --i) { delay1us();}
}
// delay 15 µs
void delay15us(void) {
  int i;
  for (i = 15; i>0; --i) { delay1us();}
}
// delay 20 µs
void delay20us(void) {
  int i;
  for (i = 20; i>0; --i) { delay1us();}
}
// delay 25 µs
void delay25us(void) {
  int i;
  for (i = 25; i>0; --i) { delay1us();}
}
// delay 30 µs
void delay30us(void) {
  int i;
  for (i = 30; i>0; --i) { delay1us();}
}

// delay 100 ms
void delay100ms(void) {
  int i;
  for (i = 5000000/4; i>0; --i) { }
}
// delay 10 ms
void delay10ms(void) {
  int i;
  for (i = 500000/4; i>0; --i) { }
}

/*********************************************************************************/

// Low-case letters

void hex2char(int *x)
{
        if( !x[0]&&!x[1] && !x[2] && x[3] && !x[4] && x[5] && !x[6] && x[7]) puts("a");
  else if (!x[0] && !x[1] && x[2] && x[3] && !x[4] && !x[5] && x[6] && !x[7]) puts("b");
	else if (!x[0] && !x[1] && x[2] && !x[3] && !x[4] && !x[5] && !x[6] && x[7]) puts("c");
	else if (!x[0] && !x[1] && x[2] && !x[3] && !x[4] && !x[5] && x[6] && x[7]) puts("d");
	else if (!x[0] && !x[1] && x[2] && !x[3] && !x[4] && x[5] && !x[6] && !x[7]) puts("e");
	else if (!x[0] && !x[1] && x[2] && !x[3] && x[4] && !x[5] && x[6] && x[7]) puts("f");
	else if (!x[0] && !x[1] && x[2] && x[3] && !x[4] && x[5] && !x[6] && !x[7]) puts("g");
	else if (!x[0] && !x[1] && x[2] && x[3] && !x[4] && !x[5] && x[6] && x[7]) puts("h");
	else if (!x[0] && x[1] && !x[2] && !x[3] && !x[4] && !x[5] && x[6] && x[7]) puts("i");
	else if (!x[0] && !x[1] && x[2] && x[3] && x[4] && !x[5] && x[6] && x[7]) puts("j");
	else if (!x[0] && x[1] && !x[2] && !x[3] && !x[4] && !x[5] && x[6] && !x[7]) puts("k");
	else if (!x[0] && x[1] && !x[2] && !x[3] && x[4] && !x[5] && x[6] && x[7]) puts("l");
	else if (!x[0] && x[1] && !x[2] && !x[3] && x[4] && x[5] && !x[6] && !x[7]) puts("m");
	else if (!x[0] && !x[1] && x[2] && x[3] && !x[4] && !x[5] && !x[6] && x[7]) puts("n");
	else if (!x[0] && x[1] && !x[2] && !x[3] && !x[4] && x[5] && !x[6] && !x[7]) puts("o");
	else if (!x[0] && x[1] && !x[2] && !x[3] && x[4] && x[5] && !x[6] && x[7]) puts("p");
	else if (!x[0] && !x[1] && !x[2] && x[3] && x[4] && x[5] && !x[6] && !x[7]) puts("q");
	else if (!x[0] && !x[1] && x[2] && !x[3] && x[4] && x[5] && !x[6] && x[7]) puts("r");
	else if (!x[0] && !x[1] && !x[2] && x[3] && x[4] && !x[5] && x[6] && x[7]) puts("s");
	else if (!x[0] && !x[1] && x[2] && !x[3] && x[4] && x[5] && !x[6] && !x[7]) puts("t");
	else if (!x[0] && !x[1] && x[2] && x[3] && x[4] && x[5] && !x[6] && !x[7]) puts("u");
	else if (!x[0] && !x[1] && x[2] && !x[3] && x[4] && !x[5] && x[6] && !x[7]) puts("v");
	else if (!x[0] && !x[1] && !x[2] && x[3] && x[4] && !x[5] && x[6] && !x[7]) puts("w");
	else if (!x[0] && !x[1] && x[2] && !x[3] && !x[4] && !x[5] && x[6] && !x[7]) puts("x");
	else if (!x[0] && !x[1] && x[2] && x[3] && !x[4] && x[5] && !x[6] && x[7]) puts("y");
	else if (!x[0] && !x[1] && !x[2] && x[3] && x[4] && x[5] && !x[6] && x[7]) puts("z");
	else if (!x[0] && !x[1] && x[2] && !x[3] && x[4] && !x[5] && !x[6] && x[7])puts(" ");
	else if (!x[0] && x[1] && !x[2] && x[3] && x[4] && !x[5] && x[6] && !x[7])puts("\n");
	else if (!x[0] && !x[1] && !x[2] && !x[3] && x[4] && x[5] && !x[6] && x[7])puts("    ");
	else if (!x[0] && !x[1] && x[2] && x[3] && x[4] && !x[5] && x[6] && !x[7])puts(",");
	else if (!x[0] && x[1] && !x[2] && !x[3] && !x[4] && !x[5] && !x[6] && x[7])puts(";");
	else if (!x[0] && x[1] && !x[2] && !x[3] && x[4] && !x[5] && !x[6] && x[7])puts(":");
	else if (!x[0] && x[1] && !x[2] && !x[3] && x[4] && !x[5] && x[6] && !x[7])puts("!");
	else if (!x[0] && x[1] && !x[2] && x[3] && !x[4] && !x[5] && x[6] && !x[7])puts("ù");
	else if (!x[0] && !x[1] && !x[2] && x[3] && !x[4] && x[5] && x[6] && !x[7])puts("&");
	else if (!x[0] && !x[1] && !x[2] && x[3] && x[4] && x[5] && x[6] && !x[7])puts("é");
	else if (!x[0] && !x[1] && x[2] && !x[3] && !x[4] && x[5] && x[6] && !x[7])puts("\"");
	else if (!x[0] && !x[1] && x[2] && !x[3] && !x[4] && x[5] && !x[6] && x[7])puts("'");
	else if (!x[0] && !x[1] && x[2] && !x[3] && x[4] && x[5] && x[6] && !x[7])puts("(");
	else if (!x[0] && !x[1] && x[2] && x[3] && !x[4] && x[5] && x[6] && !x[7])puts("-");
	else if (!x[0] && !x[1] && x[2] && x[3] && x[4] && x[5] && !x[6] && x[7])puts("è");
	else if (!x[0] && !x[1] && x[2] && x[3] && x[4] && x[5] && x[6] && !x[7])puts("_");
	else if (!x[0] && x[1] && !x[2] && !x[3] && !x[4] && x[5] && x[6] && !x[7])puts("ç");
	else if (!x[0] && x[1] && !x[2] && !x[3] && !x[4] && x[5] && !x[6] && x[7])puts("à");
	else if (!x[0] && x[1] && !x[2] && !x[3] && x[4] && x[5] && x[6] && !x[7])puts(")");
	else if (!x[0] && x[1] && !x[2] && x[3] && !x[4] && x[5] && !x[6] && x[7])puts("=");
	else if (!x[0] && !x[1] && !x[2] && !x[3] && x[4] && x[5] && x[6] && !x[7])puts("²");
	//else if (!x[0] && x[1] && !x[2] && x[3] && !x[4] && x[5] && !x[6] && !x[7])puts("^");
	else if (!x[0] && x[1] && x[2] && !x[3] && !x[4] && !x[5] && !x[6] && x[7])puts("<");
	else if (!x[0] && x[1] && !x[2] && x[3] && x[4] && x[5] && !x[6] && x[7])puts("*");
	else if (!x[0] && x[1] && x[2] && !x[3] && x[4] && !x[5] && !x[6] && x[7])puts("1");
	else if (!x[0] && x[1] && x[2] && x[3] && !x[4] && !x[5] && x[6] && !x[7])puts("2");
	else if (!x[0] && x[1] && x[2] && x[3] && x[4] && !x[5] && x[6] && !x[7])puts("3");
	else if (!x[0] && x[1] && x[2] && !x[3] && x[4] && !x[5] && x[6] && x[7])puts("4");
	else if (!x[0] && x[1] && x[2] && x[3] && !x[4] && !x[5] && x[6] && x[7])puts("5");
	else if (!x[0] && x[1] && x[2] && x[3] && !x[4] && x[5] && !x[6] && !x[7])puts("6");
	else if (!x[0] && x[1] && x[2] && !x[3] && x[4] && x[5] && !x[6] && !x[7])puts("7");
	else if (!x[0] && x[1] && x[2] && x[3] && !x[4] && x[5] && !x[6] && x[7])puts("8");
	else if (!x[0] && x[1] && x[2] && x[3] && x[4] && x[5] && !x[6] && x[7])puts("9");
	//else if (x[0] && x[1] && x[2] && x[3] && !x[4] && !x[5] && !x[6] && !x[7]) puts("F0");
	}
	
/**************************************************************************************/
//up-case letters

void hex2char_maj(int *x)
{
        if(!x[0] && !x[1] && !x[2] && x[3] && !x[4] && x[5] && !x[6] && x[7]) puts("A");
	else if (!x[0] && !x[1] && x[2] && x[3] && !x[4] && !x[5] && x[6] && !x[7]) puts("B");
	else if (!x[0] && !x[1] && x[2] && !x[3] && !x[4] && !x[5] && !x[6] && x[7]) puts("C");
	else if (!x[0] && !x[1] && x[2] && !x[3] && !x[4] && !x[5] && x[6] && x[7]) puts("D");
	else if (!x[0] && !x[1] && x[2] && !x[3] && !x[4] && x[5] && !x[6] && !x[7]) puts("E");
	else if (!x[0] && !x[1] && x[2] && !x[3] && x[4] && !x[5] && x[6] && x[7]) puts("F");
	else if (!x[0] && !x[1] && x[2] && x[3] && !x[4] && x[5] && !x[6] && !x[7]) puts("G");
	else if (!x[0] && !x[1] && x[2] && x[3] && !x[4] && !x[5] && x[6] && x[7]) puts("H");
	else if (!x[0] && x[1] && !x[2] && !x[3] && !x[4] && !x[5] && x[6] && x[7]) puts("I");
	else if (!x[0] && !x[1] && x[2] && x[3] && x[4] && !x[5] && x[6] && x[7]) puts("J");
	else if (!x[0] && x[1] && !x[2] && !x[3] && !x[4] && !x[5] && x[6] && !x[7]) puts("K");
	else if (!x[0] && x[1] && !x[2] && !x[3] && x[4] && !x[5] && x[6] && x[7]) puts("L");
	else if (!x[0] && x[1] && !x[2] && !x[3] && x[4] && x[5] && !x[6] && !x[7]) puts("M");
	else if (!x[0] && !x[1] && x[2] && x[3] && !x[4] && !x[5] && !x[6] && x[7]) puts("N");
	else if (!x[0] && x[1] && !x[2] && !x[3] && !x[4] && x[5] && !x[6] && !x[7]) puts("O");
	else if (!x[0] && x[1] && !x[2] && !x[3] && x[4] && x[5] && !x[6] && x[7]) puts("P");
	else if (!x[0] && !x[1] && !x[2] && x[3] && x[4] && x[5] && !x[6] && !x[7]) puts("Q");
	else if (!x[0] && !x[1] && x[2] && !x[3] && x[4] && x[5] && !x[6] && x[7]) puts("R");
	else if (!x[0] && !x[1] && !x[2] && x[3] && x[4] && !x[5] && x[6] && x[7]) puts("S");
	else if (!x[0] && !x[1] && x[2] && !x[3] && x[4] && x[5] && !x[6] && !x[7]) puts("T");
	else if (!x[0] && !x[1] && x[2] && x[3] && x[4] && x[5] && !x[6] && !x[7]) puts("U");
	else if (!x[0] && !x[1] && x[2] && !x[3] && x[4] && !x[5] && x[6] && !x[7]) puts("V");
	else if (!x[0] && !x[1] && !x[2] && x[3] && x[4] && !x[5] && x[6] && !x[7]) puts("W");
	else if (!x[0] && !x[1] && x[2] && !x[3] && !x[4] && !x[5] && x[6] && !x[7]) puts("X");
	else if (!x[0] && !x[1] && x[2] && x[3] && !x[4] && x[5] && !x[6] && x[7]) puts("Y");
	else if (!x[0] && !x[1] && !x[2] && x[3] && x[4] && x[5] && !x[6] && x[7]) puts("Z");
	else if (!x[0] && !x[1] && x[2] && !x[3] && x[4] && !x[5] && !x[6] && x[7])puts(" ");
	else if (!x[0] && x[1] && !x[2] && x[3] && x[4] && !x[5] && x[6] && !x[7])puts("\n");
	else if (!x[0] && !x[1] && !x[2] && !x[3] && x[4] && x[5] && !x[6] && x[7])puts("    ");
	else if (!x[0] && !x[1] && x[2] && x[3] && x[4] && !x[5] && x[6] && !x[7])puts("?");
	else if (!x[0] && x[1] && !x[2] && !x[3] && !x[4] && !x[5] && !x[6] && x[7])puts(".");
	else if (!x[0] && x[1] && !x[2] && !x[3] && x[4] && !x[5] && !x[6] && x[7])puts("/");
	else if (!x[0] && x[1] && !x[2] && !x[3] && x[4] && !x[5] && x[6] && !x[7])puts("§");
	else if (!x[0] && x[1] && !x[2] && x[3] && !x[4] && !x[5] && x[6] && !x[7])puts("%");
	else if (!x[0] && !x[1] && !x[2] && x[3] && !x[4] && x[5] && x[6] && !x[7])puts("1");
	else if (!x[0] && !x[1] && !x[2] && x[3] && x[4] && x[5] && x[6] && !x[7])puts("2");
	else if (!x[0] && !x[1] && x[2] && !x[3] && !x[4] && x[5] && x[6] && !x[7])puts("3");
	else if (!x[0] && !x[1] && x[2] && !x[3] && !x[4] && x[5] && !x[6] && x[7])puts("4");
	else if (!x[0] && !x[1] && x[2] && !x[3] && x[4] && x[5] && x[6] && !x[7])puts("5");
	else if (!x[0] && !x[1] && x[2] && x[3] && !x[4] && x[5] && x[6] && !x[7])puts("6");
	else if (!x[0] && !x[1] && x[2] && x[3] && x[4] && x[5] && !x[6] && x[7])puts("7");
	else if (!x[0] && !x[1] && x[2] && x[3] && x[4] && x[5] && x[6] && !x[7])puts("8");
	else if (!x[0] && x[1] && !x[2] && !x[3] && !x[4] && x[5] && x[6] && !x[7])puts("9");
	else if (!x[0] && x[1] && !x[2] && !x[3] && !x[4] && x[5] && !x[6] && x[7])puts("0");
	else if (!x[0] && x[1] && !x[2] && !x[3] && x[4] && x[5] && x[6] && !x[7])puts("°");
	else if (!x[0] && x[1] && !x[2] && x[3] && !x[4] && x[5] && !x[6] && x[7])puts("+");
	else if (!x[0] && !x[1] && !x[2] && !x[3] && x[4] && x[5] && x[6] && !x[7])puts("²");
	else if (!x[0] && x[1] && !x[2] && x[3] && !x[4] && x[5] && !x[6] && !x[7])puts("¨");
	else if (!x[0] && x[1] && x[2] && !x[3] && !x[4] && !x[5] && !x[6] && x[7])puts("<");
	else if (!x[0] && x[1] && !x[2] && x[3] && x[4] && x[5] && !x[6] && x[7])puts("µ");
	else if (!x[0] && x[1] && x[2] && !x[3] && x[4] && !x[5] && !x[6] && x[7])puts("1");
	else if (!x[0] && x[1] && x[2] && x[3] && !x[4] && !x[5] && x[6] && !x[7])puts("2");
	else if (!x[0] && x[1] && x[2] && x[3] && x[4] && !x[5] && x[6] && !x[7])puts("3");
	else if (!x[0] && x[1] && x[2] && !x[3] && x[4] && !x[5] && x[6] && x[7])puts("4");
	else if (!x[0] && x[1] && x[2] && x[3] && !x[4] && !x[5] && x[6] && x[7])puts("5");
	else if (!x[0] && x[1] && x[2] && x[3] && !x[4] && x[5] && !x[6] && !x[7])puts("6");
	else if (!x[0] && x[1] && x[2] && !x[3] && x[4] && x[5] && !x[6] && !x[7])puts("7");
	else if (!x[0] && x[1] && x[2] && x[3] && !x[4] && x[5] && !x[6] && x[7])puts("8");
	else if (!x[0] && x[1] && x[2] && x[3] && x[4] && x[5] && !x[6] && x[7])puts("9");
	//else if (x[0] && x[1] && x[2] && x[3] && !x[4] && !x[5] && !x[6] && !x[7]) puts("F0");
	}

/**************************************************************************************/

void hex2char_Alt(int *x)
{
        if (!x[0] && !x[1] && x[2] && !x[3] && !x[4] && x[5] && !x[6] && !x[7]) puts("€");
	else if (!x[0] && !x[1] && !x[2] && x[3] && x[4] && x[5] && x[6] && !x[7])puts("~");
	else if (!x[0] && !x[1] && x[2] && !x[3] && !x[4] && x[5] && x[6] && !x[7])puts("#");
	else if (!x[0] && !x[1] && x[2] && !x[3] && !x[4] && x[5] && !x[6] && x[7])puts("{");
	else if (!x[0] && !x[1] && x[2] && !x[3] && x[4] && x[5] && x[6] && !x[7])puts("[");
	else if (!x[0] && !x[1] && x[2] && x[3] && !x[4] && x[5] && x[6] && !x[7])puts("|");
	else if (!x[0] && !x[1] && x[2] && x[3] && x[4] && x[5] && !x[6] && x[7])puts("");
	else if (!x[0] && !x[1] && x[2] && x[3] && x[4] && x[5] && x[6] && !x[7])puts("\\");
	else if (!x[0] && x[1] && !x[2] && !x[3] && !x[4] && x[5] && x[6] && !x[7])puts("^");
	else if (!x[0] && x[1] && !x[2] && !x[3] && !x[4] && x[5] && !x[6] && x[7])puts("@");
	else if (!x[0] && x[1] && !x[2] && !x[3] && x[4] && x[5] && x[6] && !x[7])puts("]");
	else if (!x[0] && x[1] && !x[2] && x[3] && !x[4] && x[5] && !x[6] && x[7])puts("}");
	else if (!x[0] && !x[1] && !x[2] && !x[3] && x[4] && x[5] && x[6] && !x[7])puts("¤");
	}


int main(void)
{
  int j=0;
  // initialization
	int t=0;
	int i=0;
	int clk_reg=0;
	int PS2Data_in=0;
	int PS2Clk=0;
	char key;
	int clk[22];
	int data[8];
	int data_tmp[8]; 
	int caplock=0;
	int alt_gr=0;
		
	do {
	PS2Data_in=((xPS2_DATA & Data_GPIO_IN())==xPS2_DATA);
	PS2Clk=((xPS2_CLK & Data_GPIO_IN())==xPS2_CLK);
	
	if(!PS2Data_in)
	{
	delay25us();
	//////////////
	clk[0]=((xPS2_CLK & Data_GPIO_IN())==xPS2_CLK); 
	////////////////
	delay25us();
	/////////////
	clk[1]=((xPS2_CLK & Data_GPIO_IN())==xPS2_CLK); 
	////////////////
	delay30us();
	//////////////
	data[7]=((xPS2_DATA & Data_GPIO_IN())==xPS2_DATA);
	clk[2]=((xPS2_CLK & Data_GPIO_IN())==xPS2_CLK); 
	////////////////
	delay30us();
	//////////////
	clk[3]=((xPS2_CLK & Data_GPIO_IN())==xPS2_CLK); 
	////////////////
	delay30us();
	//////////////
	data[6]=((xPS2_DATA & Data_GPIO_IN())==xPS2_DATA);
	clk[4]=((xPS2_CLK & Data_GPIO_IN())==xPS2_CLK); 
	////////////////
	delay20us();
	//////////////
	clk[5]=((xPS2_CLK & Data_GPIO_IN())==xPS2_CLK); 
	////////////////
	delay25us();
	//////////////
	data[5]=((xPS2_DATA & Data_GPIO_IN())==xPS2_DATA);
	clk[6]=((xPS2_CLK & Data_GPIO_IN())==xPS2_CLK); 
	////////////////
	delay30us();
	//////////////
	clk[7]=((xPS2_CLK & Data_GPIO_IN())==xPS2_CLK); 
	///////////////
	delay15us();
	delay25us();
	//////////////
	data[4]=((xPS2_DATA & Data_GPIO_IN())==xPS2_DATA);
	clk[8]=((xPS2_CLK & Data_GPIO_IN())==xPS2_CLK); 
	////////////////
	delay30us();
	//////////////
	clk[9]=((xPS2_CLK & Data_GPIO_IN())==xPS2_CLK); 
	/////////////////////////////////////////////////
	delay10us();
	delay10us();
	//////////////
	data[3]=((xPS2_DATA & Data_GPIO_IN())==xPS2_DATA);
	clk[10]=((xPS2_CLK & Data_GPIO_IN())==xPS2_CLK); 
	////////////////
	delay30us();
	//////////////
	clk[11]=((xPS2_CLK & Data_GPIO_IN())==xPS2_CLK); 
	////////////////////
		delay25us();
	//////////////
	data[2]=((xPS2_DATA & Data_GPIO_IN())==xPS2_DATA);
	clk[12]=((xPS2_CLK & Data_GPIO_IN())==xPS2_CLK); 
	////////////////
	delay30us();
	/////////////
	clk[13]=((xPS2_CLK & Data_GPIO_IN())==xPS2_CLK); 
	////////////////
	delay30us();
	//////////////
	data[1]=((xPS2_DATA & Data_GPIO_IN())==xPS2_DATA);
	clk[14]=((xPS2_CLK & Data_GPIO_IN())==xPS2_CLK); 
	////////////////
	delay30us();
	//////////////
	clk[15]=((xPS2_CLK & Data_GPIO_IN())==xPS2_CLK); 
	////////////////
	delay30us();
	//////////////
	data[0]=((xPS2_DATA & Data_GPIO_IN())==xPS2_DATA);
	clk[16]=((xPS2_CLK & Data_GPIO_IN())==xPS2_CLK); 
	////////////////
	delay20us();
	//////////////
	clk[17]=((xPS2_CLK & Data_GPIO_IN())==xPS2_CLK); 
	////////////////
	delay25us();
	//////////////
	clk[18]=((xPS2_CLK & Data_GPIO_IN())==xPS2_CLK); 
	////////////////
	delay30us();
	//////////////
	clk[19]=((xPS2_CLK & Data_GPIO_IN())==xPS2_CLK); 
	///////////////
	delay15us();
	delay25us();
	//////////////
	clk[20]=((xPS2_CLK & Data_GPIO_IN())==xPS2_CLK); 
	////////////////
	delay30us();
	//////////////
	clk[21]=((xPS2_CLK & Data_GPIO_IN())==xPS2_CLK); 
  
  // caplock pushed
  if (!data[0] && data[1] && !data[2] && data[3] && data[4] && !data[5] && !data[6] && !data[7]) caplock=!caplock;
  
  
  if (!caplock)  // if caplock not pushed --> low-case letters
  {
    
    if((!data_tmp[0] && data_tmp[1] && !data_tmp[2] && data_tmp[3] && !data_tmp[4] && data_tmp[5] && !data_tmp[6] && !data_tmp[7])&& !(data[0] && data[1] && data[2] && data[3] && !data[4] && !data[5] && !data[6] && !data[7])) 
    {   // if the button "^" is pushed
        if(!data[0] && data[1] && !data[2] && !data[3] && !data[4] && data[5] && !data[6] && !data[7]) puts("ô");
        else if (!data[0] && data[1] && !data[2] && !data[3] && !data[4] && !data[5] && data[6] && data[7]) puts("î");
        else if (!data[0] && !data[1] && data[2] && data[3] && data[4] && data[5] && !data[6] && !data[7]) puts("û");
        else if (!data[0] && !data[1] && data[2] && !data[3] && !data[4] && data[5] && !data[6] && !data[7]) puts("ê");
        else if(!data[0] && !data[1] && !data[2] && data[3] && !data[4] && data[5] && !data[6] && data[7]) puts("â");
        else 
            { puts("^");
              hex2char(data);
             }
    }
    else hex2char(data);      
   }
    
  else hex2char_maj(data);     // otherwise up-case
	if(!(data[0] && data[1] && data[2] && data[3] && !data[4] && !data[5] && !data[6] && !data[7]))
    {
    for(i=0;i<8;i++) data_tmp[i]=data[i];
    }
	
}
	
      delay10ms();

		
	
		
    }while(1);		
		
return 0;
}






