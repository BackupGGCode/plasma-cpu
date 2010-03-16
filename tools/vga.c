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
#include "vga_char_rom.h"
#include "vga.h"



void affichage2(int R_pixel, int U_lines,int r,int g,int b);


void main(void)
{
 int r=1;
 int g=0;
 int b=0;
 //int Npixel=120;
 //int Nline=480;
 int R_pixel=311; //   right pixels of the colored area
 int U_lines=446; //   lines below the colored area  
	
		for(;;)
		{
		affichage2(R_pixel,U_lines,r,g,b);
		}
}
