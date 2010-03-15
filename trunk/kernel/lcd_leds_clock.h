/*--------------------------------------------------------------------
 * TITLE: Header File Plasma RTOS application 
 * AUTHOR: Ali Diouri (alidiouri@gmail.com)
 * DATE CREATED: 31/07/2009
 * FILENAME: lcd_leds_clock.h
 * PROJECT: Plasma RTOS application 
 * COPYRIGHT: Software placed into the public domain by the author.
 *    Software 'as is' without warranty.  Author liable for nothing.
 * DESCRIPTION:
 *    Functions' definition for Plasma RTOS application 
 *--------------------------------------------------------------------*/


/* MasK */
#define xSW 	0x0000000f
#define xBT_W 	0x00000010
#define xBT_S 	0x00000020
#define xBT_N 	0x00000040
#define xBT_E 	0x00000080
#define xRT_BA	0x00000300
#define xRT_B	0x00000200
#define xRT_A	0x00000100
#define xRT_C	0x00200000


/************************GPIO0_out***********************************/
/*0 1 2 3 4 5 6 7 8 9 10 1 2 3 4 5 6 7 8 9 20 1 2 3 4 5 6 7 8 9 30 1*/
/*|  0--7  led  | E R R |  SF_D | |    VGA   |  				   |*/
/*|  			|  	W S	|  LCD  | |B G R H V |	                   |*/
/*|             |  		|  DATA | |L R E S S |                     |*/
/*|             | L C D |       | |U E D Y Y |                     |*/
/*|             |       |       | |E E   N N |                     |*/
/*|             |       |       | |  N   C C |                     |*/
/********************************************************************/						

/************************* gpio0_in *********************************/
/*0 1 2 3 4 5 6 7 8 9 10 1 2 3 4 5 6 7 8 9 20 1 2 3 4 5 6 7 8 9 30 1*/
/*   SW  | BTN   |ROT| PS |					  R					   |*/		
/*       |W S N E|A B|D  C|					  T					   |*/
/*       |E	O O	A|   |A  L|					  C					   |*/		
/*       |S U R S|   |T  K|					 					   |*/	
/*		 |T T T T|   |A   |                                        |*/
/*		 |	H H	 |	 |	  |                                        |*/
/********************************************************************/						




/**************************** LCD Declaration **************************************/					
const int LCD_D_SHIFT = 11;
const int LCD_RS = 0x0400;                                                 
const int LCD_RW = 0x0200;	        /* always low: we never read the LCD */        
const int LCD_E  = 0x0100;                                                 
/***********************************************************************************/

/*************************** Global variables **************************************/
int n;                    // Enable/Disable print clock and date on the LCD
int FreeSem=0;            // Enable/Disable to print Click-count on the LCD 
int trf=0;                // Website link clicked(trf=1) 
int cnt=0;
int h_=18;                 // hour
int m_=32;                 // minute
int s_=0;                 // second
int d_=3;                // day
int mo_=8;                // month
int y_=2009;              // year
/************************************************************************************/

/************************** Get the Data from GPIOA_IN register *************************************/
int Data_GPIO_IN(void)
{
	return MemoryRead(GPIOA_IN);
}
/*************************************************************************************/

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


/******************************  Write Command **********************************************/	


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
 
 // low nibble
  lcd_output = (ch & 0x0f) << LCD_D_SHIFT;         			// lcd_output= 0x6000     (shift_left=11)
  lcd_output |= LCD_RS;                          			// lcd_output= 0x6400  --> LCD_RS =1   LCD_RW=0    SF_D=1010
  MemoryWrite(GPIO0_OUT, lcd_output);						// write lower nibble
  for(i=0;i<2;i++){}                                        // hold LCD_RS LCD_RW SF_D stable for 40ns before LCD_E goes high 
  HoldPulse_e12CC();										// LCD_E high for 12 Clock cycles
  for(i=0;i<1;i++){}
  MemoryWrite(GPIO0_CLEAR,lcd_output);						// LCD_RS=0 LCD_RW=0
  delay40us();                                              // delay 40us for the next write char lcd
}

 void write_command4_lcd(unsigned char ch)                  // ex: ch =0x03
{                           
  int lcd_output;                                             
  int i;
  /* write lower nibble: */
  lcd_output = (ch & 0x0f) << LCD_D_SHIFT;          		 // lcd_output= 0x0180 (shift_left=11)
  MemoryWrite(GPIO0_OUT, lcd_output);                        // write lower nibble
  for(i=0;i<2;i++){}                                         // hold LCD_RS LCD_RW SF_D stable for 40ns before LCD_E goes high 
  HoldPulse_e12CC();                                         // LCD_E high for 12 Clock cycles
  for(i=0;i<1;i++){}
  MemoryWrite(GPIO0_CLEAR,lcd_output);
  for(i=0;i<2;i++){}
}

  
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

/*************************************************** Switch Function *****************************************************/
/* This function return whether we want to change the clock and date.
switches =1111 --> change the clock and date.
switches !=1111 --> leave the clock and date as they are.
*/
int Change_clock(void)
{
	int i=Data_GPIO_IN();
	i=i&xSW;
	if (i==xSW) return 1;                
	else return 0;
}
/**************************************************************************************************************************/

/*************************************************** Button Functions *****************************************************/
/* these functions let us know which button was clicked 
--> West Button
--> South Button
--> North Button
--> East Button
--> Rotation A : to the right
--> Rotation B : to the left
*/

// West Button 
int BT_W(void)
{   
	int k=0;
	int i=Data_GPIO_IN();
	i=i&xBT_W;
	for (k=0;k<10;k++)
	{
		delay1ms();
	}
	if(i==xBT_W) return 1;
	else return 0;
}

// South Button
int BT_S(void)
{
	int k=0;
	int i=Data_GPIO_IN();
	i=i&xBT_S;
	for (k=0;k<10;k++)
	{
		delay1ms();
	}
	if(i==xBT_S) return 1;
	else return 0;
}

// North Button
int BT_N(void)
{
	int k=0;
	int i=Data_GPIO_IN();
	i=i&xBT_N;
	for (k=0;k<10;k++)
	{
		delay1ms();
	}
	if(i==xBT_N) return 1;
	else return 0;
}

// East Button
int BT_E(void)
{
	int k=0;
	int i=Data_GPIO_IN();
	i=i&xBT_E;
	for (k=0;k<10;k++)
	{
		delay1ms();
	}
	if(i==xBT_E) return 1;
	else return 0;
}

// Rotation A
int RT_A(void)
{   
	int i0=Data_GPIO_IN();
	i0=i0&xRT_BA;
	if(i0==xRT_A) return 1;
	else return 0;
	
}

// Rotation B
int RT_B(void)
{
	int i=Data_GPIO_IN();
	i=i&xRT_BA;
	if(i==xRT_B) return 1;
	else return 0;
}
// Rotation Center
int RT_C(void)
{
	int i=Data_GPIO_IN();
	i=i&xRT_C;
	if(i==xRT_C) return 1;
	else return 0;
}
/**********************************************************************************************************************************/

/******************************************************* Clock & Date Functions  ***********************************************/  
/*
Print_Date_Clock(): shows the date & clock on LCD screen .
                    It is disabled when a link in the web site 
                    is clicked (FreeSem=1) 

				H     : M     : S     ,   D .   M     .   Y
				h2 h1   m2 m1   s2 s1   d2 d1  mo2 mo1  y4 y3 y2 y1
					
*/

void Print_Date_Clock(int h,int m,int s,int d, int mo,int y)
{
		/*date*/
	int d2=d/10;
	int d1=d-d2*10;
	int mo2=mo/10;
	int mo1=mo-mo2*10;
	int y4=y/1000;
	int y3=(y-y4*1000)/100;
	int y2=(y-y4*1000-y3*100)/10;
	int y1=(y-y4*1000-y3*100-y2*10);
	
	   /*clock*/
	int h2=h/10;
	int h1=h-h2*10;
	int m2=m/10;
	int m1=m-m2*10;
	int s2=s/10;
	int s1=s-s2*10;
	
	if(!FreeSem)                           //   disable (FreeSem =1) / Enable (FreeSem=0)
	{			
	           /* DATE */
	
		write_command8_lcd(0xcf);           //   the place to write in   
		write_char_lcd(0x30+y1);			// y1
  
		write_command8_lcd(0xce);             
		write_char_lcd(0x30+y2);            // y2
    
		write_command8_lcd(0xcd);             
		write_char_lcd(0x30+y3);            // y3
  
		write_command8_lcd(0xcc);             
		write_char_lcd(0x30+y4);            // y4 
   
		write_command8_lcd(0xcb);
		write_char_lcd(0x2e);               // .  
    
		write_command8_lcd(0xca);
		write_char_lcd(0x30+mo1);           // mo1
    
		write_command8_lcd(0xc9);             
		write_char_lcd(0x30+mo2);           // mo2
    
		write_command8_lcd(0xc8);
		write_char_lcd(0x2e);               // .
	  
		write_command8_lcd(0xc7);
		write_char_lcd(0x30+d1);            // d1
		 
		write_command8_lcd(0xc6);             
		write_char_lcd(0x30+d2);            // d2
		
		
				/* CLOCK */		
		
		write_command8_lcd(0x86);             
		write_char_lcd(0x30+h2);            // h2
		
		write_command8_lcd(0x87);
		write_char_lcd(0x30+h1);			// h1
		
		write_command8_lcd(0x88);         
		write_char_lcd(0x3a);               // :
	  
		write_command8_lcd(0x89);             
		write_char_lcd(0x30+m2);            // m2
    
		write_command8_lcd(0x8a);
		write_char_lcd(0x30+m1);            // m1
    
	    write_command8_lcd(0x8b);
		write_char_lcd(0x3a);               // : 
    
		write_command8_lcd(0x8c);             
		write_char_lcd(0x30+s2);            // s2
     
	    write_command8_lcd(0x8d);             
		write_char_lcd(0x30+s1);            // s1
		
		write_command8_lcd(0x0c);           // dispay on , cursor off , blink off
	}	
}

/*    clock_date() : is the function that make the clock and date work .
                     if Change_clock() =0 the clock run.
					 if Change_clock() =1 the clock stop and we can modify it
                     by using the buttons.
					
					H     : M     : S     ,   D .   M     .   Y
				h2 h1   m2 m1   s2 s1   d2 d1  mo2 mo1  y4 y3 y2 y1
*/



void clock_date(int h,int m,int s,int d,int mo ,int y)
{   
	int j=0x86; // the place to write
	int i=128;  // for led
	
	
	/*date*/
	int d2=d/10;
	int d1=d-d2*10;
	int mo2=mo/10;
	int mo1=mo-mo2*10;
	int y4=y/1000;
	int y3=(y-y4*1000)/100;
	int y2=(y-y4*1000-y3*100)/10;
	int y1=(y-y4*1000-y3*100-y2*10);
	
	/*clock*/
	int s1=s%10;
	int s2=(s-s1)/10;
	int m1=m%10;
	int m2=(m - m1)/10;
	int h1=h%10;
	int h2=(h - h1)/10;
	
	for(;;)
	{
		while(!Change_clock())            // no change clock
		{	
			write_command8_lcd(0x0c);    // dispay on , cursor off , blink off
			
			s1=s1+1;
			Led(i);      
			i=i/2;
			OS_ThreadSleep(100);   //1 s
			n=0;
			if(i==0) i=128;
			if (s1==10)
			{
				s1=0;
				s2=s2+1;
				if ( s2==6)
				{
					s2=0;
					m1=m1+1;
		
					if (m1==10)	
					{ 
						m1=0;
						m2=m2+1;
					
						if (m2==6)
						{
							m2=0;
							h1=h1+1;
					
							if (h1==10)	
							{
								h1=0;
								h2=h2+1;
							}
							if (h2==2 && h1==4)
							{ 
								h1=0;
								h2=0;
								d1=d1+1;
								if( d1==10&& (d2==0 || d2 ==1))
								{
									d1=0;
									d2=d2+1;
								}
								if (d2==2 && d1==9 && mo2==0 && mo1==2 &&  (y%4)!=0)        // 28 days
								{
									d1=1;
									d2=0;
									mo1=3;
								}
								else if (d2==3 && d1==0 && mo2==0 && mo1==2 &&  (y%4)==0)    // 29 days
								{
									d1=1;
									d2=0;
									mo1=3;
								}
								else if (d1==1 && d2==3 && ((mo1==4) || mo1==6 || mo1==9 || (mo2==1 && mo1==1)))     // month 30 days
								{ 
									d1=1;
									d2=0;
									mo1=mo1+1;
									if (mo1==10)
									{
										mo1=0;
										mo2=1;
									}
								
								}
								else if  ((mo1==1 && mo2==0) || mo1==3 ||mo1==5|| mo1==7||mo1==8||(mo1==0 && mo2==1) || (mo1==2 && mo2==1)) // month 31 days
								{ 
									if (d1==10 && d2==2)
									{
										d1=0;
										d2=d2+1;
									}
									if (d1==2 && d2==3)
									{
										d1=1;
										d2=0;
										if(mo2==1 && mo1==2)
										{
											mo1=1;
											mo2=0;
											y1=y1+1;
											if (y1==10)
											{
												y1=0;
												y2=y2+1;
												if (y2==10)
												{
													y2=0;
													y3=y3+1;
													if (y3==10)
													{
														y3=0;
														y4=y4+1;
														if (y4==10)
														{
															y4=1;
														}
													}	
												}
											}
										}
										else
										{
											mo1=mo1+1;
											if 	(mo1==10)
											{
												mo1=0;
												mo2=1;
											}
										}
									}										
								}	
							}		 		
						}	
					}
				}		
			}
		
			d_=d2*10+d1;
			mo_=mo2*10+mo1;
			y_=(y4*1000)+(y3*100)+(y2*10)+y1;
			
			h_=h2*10+h1;
			m_=m2*10+m1;
			s_=s2*10+s1;
			n=1;
		
		}

		while (Change_clock())               	// change Clock (!!!!beta!!!!)
		{	
		   OS_ThreadSleep(70);               	//700ms
			
			n=0;                          
			write_command8_lcd(j);            	// where the cursor starts
			write_command8_lcd(0x0f);         	// dispay on , cursor on , blink on
			
			if(BT_E()==1)                     	// if the East button is clicked the cursor moves to the right
			{
				j=j+1;                         
				if(j==0x8e) j=0x86;
				if(j==0xd0) j=0xc6;
			}
			if(BT_W()==1)                  		// if the West button is clicked the cursor moves to the left
			{
				j=j-1;
				if(j==0x85) j=0x8d;
				if(j==0xc5) j=0xcf;
			}
			if (BT_N()==1)						// if the North button is clicked the cursor moves up
			{
				j=j-0x40;
				if(j<0x80) j=j+0x80;
			}
			if (BT_S()==1)						// if the South button is clicked the cursor moves down
			{
				j=j+0x40;
				if(j>0xcf) j=j-0x80;
			}	
			if  (RT_A()==1)                     // Rotate to the right --> +1
			{
				Led(i);
				i=i/2;
				if (i==0) i=128;
				if (j>0x85 && j<0x8d)           // change the clock
				{	
					if (j==0x86) 
					{
						h2=h2+1;
						if (h2==3) h2=0;
					}
					if (j==0x87) 
					{
						h1=h1+1;
						if (h2==2 && h1==4) h1=0;
						if (((h2==0)||(h2==1))&& (h1==10)) h1=0;
					}
					if (j==0x89)
					{
						m2=m2+1;
						if (m2==6) m2=0;
					}
					if (j==0x8a)
					{
						m1=m1+1;
						if(m1==10) m1=0;
					}
					if	(j==0x8c)
					{
						s2=s2+1;
						if (s2==6) s2=0;
					}
					if (j==0x8d)
					{
						s1=s1+1;
						if(s1==10) s1=0;
					}
				}
				if (j>0xc5 && j<0xd0)                      // change the date
				{	
					if (j==0xc6) 
					{
						d2=d2+1;
						if (d2==4) d2=0;
					}
					if (j==0xc7) 
					{
						d1=d1+1;
						if (d1==10) d1=0;
					}	
					if (j==0xc9)
					{
						mo2=mo2+1;
						if (mo2==2) mo2=0;
					}
					if (j==0xca)
					{
						mo1=mo1+1;
						if(mo1==10) mo1=0;
					}
					if	(j==0xcc)
					{
						y4=y4+1;
						if (y4==10) y4=0;
					}
					if (j==0xcd)
					{
						y3=y3+1;
						if(y3==10) y3=0;
					}
					if (j==0xce)
					{
						y2=y2+1;
						if(y2==10) y2=0;
					}
					if (j==0xcf)
					{
						y1=y1+1;
						if(y1==10) y1=0;
					}
				}
			}			
			if  (RT_B()==1)						  	//   rotate left --> -1
			{
				Led(i);
				i=i*2;
				if (i==128) i=1;
				if (j>0x85 && j<0x8d)				// change the clock
				{	
					if (j==0x86) 
					{
						h2=h2-1;
						if (h2==-1) h2=2;
					}
					if (j==0x87) 
					{
						h1=h1-1;
						if (h1==-1) h1=9;
						}
					if (j==0x89)
					{
						m2=m2-1;
						if (m2==-1) m2=5;
					}
					if (j==0x8a)
					{
						m1=m1-1;
						if(m1==-1) m1=9;
					}
					if	(j==0x8c)
					{
						s2=s2-1;
						if (s2==-1) s2=5;
					}
					if (j==0x8d)
					{
						s1=s1-1;
						if(s1==-1) s1=9;
					}	
				}
				if (j>0xc5 && j<0xd0)                   // change the date
				{	
					if (j==0xc6) 
					{
						d2=d2-1;	
					}
					if (j==0xc7) 
					{
						d1=d1-1;
						if (d1==-1) d1=9;
					}
					if (j==0xc9)
					{
						mo2=mo2-1;
						if (mo2==-1) mo2=1;
					}
					if (j==0xca)
					{
						mo1=mo1-1;
						if(mo1==-1) mo1=9;
					}
					if	(j==0xcc)
					{
						y4=y4-1;
						if (y4==-1) y4=9;
					}
					if (j==0xcd)
					{
						y3=y3-1;
						if(y3==-1) y3=9;
					}
					if (j==0xce)
					{
						y2=y2-1;
						if(y2==-1) y2=9;
					}
					if (j==0xcf)
					{
						y1=y1-1;
						if(y1==-1) y1=9;
					}
				}
			}
			d_=d2*10+d1;
			mo_=mo2*10+mo1;
			y_=(y4*1000)+(y3*100)+(y2*10)+y1;
			
		
			h_=h2*10+h1;
			m_=m2*10+m1;
			s_=s2*10+s1;
			n=1;                                // print the change on LCD screen
			
		}					
	}
}
/*********************************************************************************************************/

/***************************************** Page Counter ***************************************************/

/*
Print_PaCtr(): this Function Print how many clicks (hyperlink) were done in the siteweb on LCD screen.
*/


void Print_PaCtr(void)
{
int c1,c2;
int i=2;
			
    for(;;)
	{	OS_ThreadSleep(10);
	    if (trf)								// trf =1--> link is clicked
		{	
			FreeSem=1;							// let the Count to be shown on lcd (disable to print clock and date) 
			c2=cnt/10;
			c1=cnt-c2*10;
			
			
			write_command8_lcd(0x01);         	// clear display command
			delay1ms();                      	 // |
			delay1ms();                       	// |  wait 2 ms
			
			write_command8_lcd(0x0c);			// dispay on , cursor off , blink off
			
			write_command8_lcd(0x80+i);             
			write_char_lcd(0x50);    			//P	
			i++;	
			write_command8_lcd(0x80+i); 
			write_char_lcd(0x61);				//a 
			i++;	
			write_command8_lcd(0x80+i); 
			write_char_lcd(0x67); 				//g
			i++;  
			write_command8_lcd(0x80+i);             
			write_char_lcd(0x65);    			//e
			i++;
			write_command8_lcd(0x80+i);
			write_char_lcd(0xa0);				// (space)
			i++;
			write_command8_lcd(0x80+i);
			write_char_lcd(0x43);  				//C
			i++;
			write_command8_lcd(0x80+i);             
			write_char_lcd(0x6c);   			//l
			i++;
			write_command8_lcd(0x80+i);             
			write_char_lcd(0x6b);    			//k
			i++;
			write_command8_lcd(0x80+i);             
			write_char_lcd(0x3a);    			// :
			i++;	
			write_command8_lcd(0x80+i);
			write_char_lcd(0xa0);				// (space)
			i++;
			write_command8_lcd(0x80+i);     	//c2
			write_char_lcd(0x30+c2);
			i++;
			write_command8_lcd(0x80+i);			//c1
			write_char_lcd(0x30+c1);
			i=2;
			OS_ThreadSleep(150);				// 1.5s
			write_command8_lcd(0x01);         	// clear display command
			delay1ms();                       	// |
			delay1ms();                       	// |  wait 2 ms
			FreeSem=0;							// enable to print clock and date
			trf=0;
		}
	}
	
}  	
/********************************************************************************************************/



/************************************Functions To be implemented in threads *****************************/
/*
	These functions are going to be put when creating the threads 
    LCD_Led_Clk() 			: controls the clock and date
	Print_LCD_Led_Clk()		: controls LCD for Clock and date
	PageCall_LCD()          : controls LCD for Click Count  
*/
static void LCD_Led_Clk(void *arg)
{
  clock_date(h_ , m_ , s_,d_,mo_,y_);  //h m s
}

//--------------------------------------------------
static void  Print_LCD_Led_Clk(void *arg)
{
  
  initialize_lcd();
  configure_lcd();
  for(;;)
	{
		 OS_ThreadSleep(10);								 //100 ms
		if(n)                                             // if the characters are ready 
		{		
			Print_Date_Clock(h_,m_,s_,d_,mo_,y_);
		}
		
	}	
}
//-------------------------------------------------------
static void PageCall_LCD(void *arg)
{
  initialize_lcd();
  configure_lcd();
  Print_PaCtr();

} 	
//-------------------------------------------------------------
