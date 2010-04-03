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
#define MemoryWrite(A,V) *(volatile unsigned long*)(A)=(V)
#define MemoryRead(A) (*(volatile unsigned long*)(A))

// Masks

#define xBlank 		0x00400000
#define xBT_W 		0x00000010
#define xBT_E 		0x00000080
#define xBT_S 		0x00000020
#define xBT_N 		0x00000040
#define xSW 	  	0x0000000f

//***********************************************************  
// manage the buttons
// -----------------------------------------
// change the position of the object
// 
////************************************************************


// West Button 
int BT_W(void)
{   
	int k=0;
	int i=Data_GPIO_IN();
	i=i&xBT_W;
	return (i==xBT_W);
}
// East Button
int BT_E(void)
{
	int k=0;
	int i=Data_GPIO_IN();
	i=i&xBT_E;
	return (i==xBT_E);
}

// South Button
int BT_S(void)
{
	int k=0;
	int i=Data_GPIO_IN();
	i=i&xBT_S;
	return (i==xBT_S);
}

// North Button
int BT_N(void)
{
	int k=0;
	int i=Data_GPIO_IN();
	i=i&xBT_N;
	return (i==xBT_N);
}

//***********************************************************  
// Switch colors
// -----------------------------------------
// switch the color of the object depending on 
// the switch  buttons(2,1,0 from the right) 
////************************************************************

int ColorSwitch(void)
{
  int i=Data_GPIO_IN();
	i=i&xSW;
	if(i==0x1)
    return 1<<16;
  else if(i==0x2)
    return (1<<17);
  else if(i==0x3)
    return (1<<16 |1<<17);
  else if(i==0x4)
    return (1<<18);
  else if(i==0x5)
    return (1<<18 |1<<16);
  else if(i==0x6)
    return (1<<18 |1<<17);
  else if(i==0x7)
    return (1<<16 |1<<17|1<<18);
  else return 0;
}

//***********************************************************  
// shift lines
// -----------------------------------------
// Nlines  : Number of lines to be shifted
// Color   : the Color Chosen
////************************************************************

void shift_lines(int Nlines, int Color)
{
  int j,Nl;
  for(Nl=0;Nl<Nlines;)
  {
      j=0;
      MemoryWrite(GPIO0_CLEAR, Color);
      while(((MemoryRead(VGA_Counter)& xBlank)!=xBlank)) 
      {
           j=1;
           if (((MemoryRead(VGA_Counter)& xBlank)==xBlank)) break;
           
      }
      while(((MemoryRead(VGA_Counter)& xBlank)==xBlank))
      {
           if(j==1) j=2;
           else j=3;
           if (((MemoryRead(VGA_Counter)& xBlank)!=xBlank)) break;
      }
      if (j==1 || j==3) Nl++;
      if (j==2)         Nl=Nl+2;
  }
}
 
 
///********************************************************////
///                Main Function 
///********************************************************//// 
void main(void)
{
  int j,Nl,Np;			
  int Nlines=200;						// Number of lines
  int Npixels=1;						// Number of pixel
  int N_Sh_Pix=0;  						// Number of pixel to shift 0 --> 59  1 pix
  int Color=1<<18;						// initial Color
  int U_Nlines=100;						// Up offset
  int D_Nlines=480-Nlines-U_Nlines+1;	// down offset
  
  
  for(;;)
  {
    if(BT_W()) 
    {
      N_Sh_Pix++;
      if (N_Sh_Pix==60) N_Sh_Pix=0;
    }
    else if (BT_E())  
    {
      N_Sh_Pix--;
      if (N_Sh_Pix==-1) N_Sh_Pix=59;
    }
    if(BT_S())
    {
        U_Nlines++;
        if(U_Nlines==281) U_Nlines=0;
        }
     if(BT_N())
    {
        U_Nlines--;
        if(U_Nlines==-1) U_Nlines=280;
    }
    
    Color=ColorSwitch();
    shift_lines(U_Nlines,Color);
    for(Nl=0;Nl<Nlines;)   // for each line
    {
        while (((MemoryRead(VGA_Counter)& xBlank)!=xBlank))
        {
          for(Np=0;Np<N_Sh_Pix;Np++){if (((MemoryRead(VGA_Counter)& xBlank)==xBlank)) break;}
          if (((MemoryRead(VGA_Counter)& xBlank)==xBlank)) break;
          MemoryWrite(GPIO0_OUT,Color);
          if (((MemoryRead(VGA_Counter)& xBlank)==xBlank)) break;
          for(Np=0;Np<Npixels;Np++){if (((MemoryRead(VGA_Counter)& xBlank)==xBlank)) break;}
          if (((MemoryRead(VGA_Counter)& xBlank)==xBlank)) break;
          MemoryWrite(GPIO0_CLEAR,Color);
          if (((MemoryRead(VGA_Counter)& xBlank)==xBlank)) break;
          for(Np=0;Np<320-Npixels-N_Sh_Pix;Np++){if (((MemoryRead(VGA_Counter)& xBlank)==xBlank)) break;}
          Nl++;
          if (((MemoryRead(VGA_Counter)& xBlank)==xBlank)) break;
        }
      }
      shift_lines(D_Nlines,Color);
    }
}
