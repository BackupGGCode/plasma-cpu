/*--------------------------------------------------------------------
 * TITLE:Appliction in Plasma Real Time Operating System 
 * AUTHOR: Ali Diouri
 * DATE CREATED: 31/07/2009
 * FILENAME: rtos_appl.c
 * PROJECT: Plasma RTOS application
 * COPYRIGHT: Software placed into the public domain by the author.
 *    Software 'as is' without warranty.  Author liable for nothing.
 * DESCRIPTION:
 *    Application using leds, LCD screen, Buttons, Switches, Ethernet
 *--------------------------------------------------------------------*/
#include "plasma.h"
#include "rtos.h"
#include "tcpip.h"
#include "lcd_leds_clock.h"

/************************* Function used ************************************/

static void LCD_Led_Clk(void *arg);
static void  Print_LCD_Led_Clk(void *arg);
static void PageCall_LCD(void *arg);
void HtmlThread(void *arg);
void ConsoleInit(void);
uint8 macAddress[] =  {0x00, 0x10, 0xdd, 0xce, 0x15, 0xd4};

//*****************************************************************************


/****************** Clock_Date_Thread definition ****************************/

// This Function creates a thread that controles Date and clock  

static void Clock_Date_Thread(void)
{
	int i=4;
	int	priority=54;
	
	OS_Thread_t *LCD_Led_Clk_thread=OS_ThreadCreate("LCD_Led_Clk", LCD_Led_Clk, (uint32*)i, priority, 0);
	
	puts("-->LCD_Led_Clk_thread\n");
	if(LCD_Led_Clk_thread)
	{	
		printf("thread_Address=0x%x  priority=%d\n",LCD_Led_Clk_thread, priority);
		puts("\n");
		puts("\n");
	}
	else puts("*****************error***********************\n");
}
//***************************************************************************************


/************************** ether_lcd definition ***************************************/

//ether_lcd() creates a thread which will links between the LCD and the data coming from ethernet

static void ether_lcd()
{
	int i=3;
	int	priority=53;
	
	OS_Thread_t *ether_lcd_thread=OS_ThreadCreate("PageCall_LCD",PageCall_LCD , (uint32*)i, priority, 0);
	
	puts("-->ether_lcd thread\n");
	if (ether_lcd_thread) 
	{
		printf("thread_Address=0x%x  priority=%d\n",ether_lcd_thread, OS_ThreadPriorityGet(ether_lcd_thread));
		puts("\n");
		puts("\n");
	}		
	else puts("*****************error***********************\n");
}
//*****************************************************************************

/********************************** Print_clock_LCD definition *****************************/

// this function writes the date and clock in LCD

static void Print_clock_LCD()
{
	int i=3;
	int	priority=53;

	OS_Thread_t *Print_LCD_thread=OS_ThreadCreate("Print_Clock_LCD",Print_LCD_Led_Clk , (uint32*)i, priority, 0);
	
	puts("-->Print_clock_LCD Thread\n");
	if (Print_LCD_thread) 
	{
		printf("thread_Address=0x%x priority=%d\n",Print_LCD_thread, OS_ThreadPriorityGet(Print_LCD_thread));
		puts("\n");
		puts("\n");
	}		
	else puts("*****************error***********************\n");
}
//********************************************************************************************

/**************************************** MainThread Function *********************************************/
void MainThread(void *Arg)
{
   (void)Arg;

#ifdef INCLUDE_ETH
   EthernetInit(macAddress);
   IPInit(EthernetTransmit, macAddress, "plasma");
   HtmlInit(1);
#endif

#ifdef INCLUDE_HTML
   IPInit(NULL, macAddress, "plasma");
   HtmlInit(1);
#endif

#ifdef INCLUDE_CONSOLE
   ConsoleInit();
#endif

	OS_ThreadSleep(50);
/***************
Clock_Date Thread
****************/
	Clock_Date_Thread();
/*******************
 Print_clock_LCD Thread
*******************/
	Print_clock_LCD();
/******************
ethernet_lcd thread
******************/
	ether_lcd();
/******************************/
	puts("\n *******************************End Thread Creation ******************************\n");
}
//*****************************************************************************************************/