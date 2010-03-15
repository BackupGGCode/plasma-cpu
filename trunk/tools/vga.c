/*--------------------------------------------------------------------
 * TITLE: vga for Plasma 
 * AUTHOR: Ali Diouri (alidiouri@gmail.com)
 * DATE CREATED: 24/02/2010
 * FILENAME: vga.c
 * PROJECT: Plasma RTOS application 
 * COPYRIGHT: Software placed into the public domain by the author.
 *    Software 'as is' without warranty.  Author liable for nothing.
 * DESCRIPTION:
 *    configuration of VGA  
 *--------------------------------------------------------------------*/


#include "plasma.h"
#include "vga.h"
#include "vga_char_rom.h"
#define MemoryWrite(A,V) *(volatile unsigned long*)(A)=(V)

void Led(int i);
void affichage(Npixel, Nline,R_pixel,U_lines,r,g,b);


void main(void)
{
 
 int r=1;
 int g=0;
 int b=0;
 int Npixel=320;
 int Nline=480;
 int R_pixel=0; //   right pixels of the colored area
 int U_lines=0; //   lines below the colored area  
	
		for(;;)
		{
		affichage(Npixel, Nline,R_pixel,U_lines,r,g,b);
		}
}
