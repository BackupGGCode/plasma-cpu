/*--------------------------------------------------------------------
 * TITLE: header file for vga
 * AUTHOR: Ali Diouri (alidiouri@gmail.com)
 * DATE CREATED: 15/03/2010
 * FILENAME: vga.h
 * PROJECT: Plasma RTOS application 
 * COPYRIGHT: Software placed into the public domain by the author.
 *    Software 'as is' without warranty.  Author liable for nothing.
 * DESCRIPTION:
 *    Functions to be used in vga main file
 *--------------------------------------------------------------------*/



/************************GPIO0_out***********************************/
/*0 1 2 3 4 5 6 7 8 9 10 1 2 3 4 5 6 7 8 9 20 1 2 3 4 5 6 7 8 9 30 1*/
/*|  0--7  led  | E R R |  SF_D | |    VGA   |  		            |*/
/*|  			|   W S	|  LCD  | |B G R H V |		                |*/
/*|             |     	|  DATA | |L R E S S |                      |*/
/*|             | L C D |       | |U E D Y Y |                      |*/
/*|             |       |       | |E E   N N |                      |*/
/*|             |       |       | |  N   C C |                      |*/
/********************************************************************/			


//************** Clock = 12.5 MHz   / 80 ns *************************/

///******************   Time Functions ********************************/

///***** Hsync Timing ****/

void delay640ns(void) {                
  int i;
  for (i =4; i>0; --i) { }
  }
 // delay 1.92 µs
void delay1_92us(void) {
  int i;
  for (i = 20; i>0; --i) {}
}
// delay 3,84 us
void delay3_84us(void) {
  int i;
  for (i = 44; i>0; --i) { }
}
// delay 25,6 µs
void delay25_6us(void) {
  int i;
  for (i = 316; i>0; --i) {}
}

///***** Vsync Timing ****/

// delay 320 µs
void delay320us(void) {
  int i;
  for (i = 16000/4; i>0; --i) { }
}
// delay 928 µs
void delay928us(void) {
  int i;
  for (i = 46400/4; i>0; --i) {}
}
// delay 64 us
void delay64us(void) {
  int i;
  for (i = 800; i>0; --i) { }
}
/*************************/
void delay_x80ns(int x)
{
	int i;
	for(i=x;i>0;--i){}
}
///***************************   Hsync Function ***********************/
void Hsync_signal(void)
{
int hsync;
	// Back Porch
            hsync=1<<19;
            MemoryWrite(GPIO0_OUT,hsync);
            delay1_92us();	
       
    // active video
            delay25_6us();
       
    // Front Porch
            delay640ns();
        
    // Sync Pulse
            MemoryWrite(GPIO0_CLEAR, hsync);
            delay3_84us();
}
///**************************  Character generator ********************/
void char_generator(uint8_t mot[][],int R_pixel,int char_choice)
{
	int Nl,i;
	
	for(Nl=0;Nl<16;Nl++)			    								// 480 lines @ 31.25 khz --> y-axis
	  {
	// Back Porch
		hsync=1<<19;
		MemoryWrite(GPIO0_OUT,hsync);
		delay1_92us();	
   
	///*** Horizontal active video***
		delay_x80ns(320-8-R_pixel);										// Left of the colored area 320-Npixel-R_pixel
			for(i=0;i<8;i++)
			{
				if(mot[Nl+char_choice][i])								// pixel = 1
				{
					MemoryWrite(GPIO0_OUT,r);
					delay_x80ns(1);
					MemoryWrite(GPIO0_CLEAR, r);
				}
				else delay_x80ns(1);									// pixel = 0
			}
	   delay_x80ns(R_pixel);
	///******************************
	// Front Porch
		delay640ns();
	
	// Sync Pulse
		MemoryWrite(GPIO0_CLEAR, hsync);
		delay3_84us();
	  }
}

///********************* Affichage sur l'ecran ************************/
void affichage(int Npixel, int Nline, int R_pixel, int U_lines,int r,int g,int b)
{
  
  int vsync=1<<20;
  int hsync=1<<19;
  int Nl;
  int Np;
  int i;
  int rgb;
  
  r=r<<18;
  g=g<<17;
  b=b<<16;
  rgb=r|g|b;
  ///----------------------Frame start---------------------------
      // Vertical Sync Pulse
				MemoryWrite(GPIO0_CLEAR, vsync);
				for(i=0;i<2;i++)
					Hsync_signal();
				
				
		  // Vertical Back Porch
			MemoryWrite(GPIO0_OUT,vsync);
			for(i=0;i<28;i++)
			  Hsync_signal();
			  

	///**********Vertical active video *****
				
			  for(Nl=0;Nl<(480-Nline-U_lines);Nl++)						//above the colored area
			  	   Hsync_signal();
			 	     
			 ///****************************************
			 for(Nl=0;Nl<Nline;Nl++)			   						// 480 lines @ 31.25 khz --> y-axis
			  {
			// Back Porch
				hsync=1<<19;
				MemoryWrite(GPIO0_OUT,hsync);
				delay1_92us();	
		   
			///*** Horizontal active video******
				delay_x80ns(320-Npixel-R_pixel);						// Left of the colored area
				MemoryWrite(GPIO0_OUT,rgb);
				delay_x80ns(Npixel);
				MemoryWrite(GPIO0_CLEAR,rgb);
				delay_x80ns(R_pixel);									// right of the colored area
				//delay_x80ns(320-Npixel);
			///*********************************
			// Front Porch
				delay640ns();
			
			// Sync Pulse
				MemoryWrite(GPIO0_CLEAR, hsync);
				delay3_84us();
			  }
			  ///**************************************
			   for(Np=0;Np<U_lines;Np++)								// below  the colored area
					Hsync_signal();
///*************************************************************		
			
			// vertical Front Porch
				MemoryWrite(GPIO0_OUT,vsync);
				for(i=0;i<11;i++)
					Hsync_signal();
	///--------------------------End Frame-------------------------	
}
/*********************************************************************************/
