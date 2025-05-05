#include <msp430.h>
#include <string.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "buzzer.h"
#include "stateMachines.h"
#include "switches.h"

#define LED BIT6;

int play = 0;
int hover= 0;
static char p2val;


u_char width = screenWidth, height = screenHeight;
static char* Mary = "Marry Had a little Lamb";
static char* Mc = "Old Mc Donald";
static char* Star = "Ponyo";
static char* Woods = "Lost Woods";

void __interrupt_vec(WDT_VECTOR) WDT(){
  static int counter = 0;
  counter++;
  
  if(play == 1){
    if(counter == 125 && counter == 250){
	switch(hover){
	case 2:
	  playSong2();
	  break;
	case 3:
	  playSong3();
	  break;
	}
      }
  }
  
  //this code will alternate the color between black and white with the
  //corisponding hover state which just means which song is being hovered
  if(counter == 125){
    switch(hover){
    case 0://Mary had a little lamb

	fillRectangle(4,4,StrLength(Mary),10,COLOR_WHITE);
	drawString5x7(5,5, "Mary Had a little Lamb", COLOR_BLACK, COLOR_WHITE);
	break;
    case 1://Old Mc Donald
      
	fillRectangle(4,16, StrLength(Mc), 10, COLOR_WHITE);
	drawString5x7(17,5, "Old Mc Donald", COLOR_BLACK, COLOR_WHITE);
	break;
    case 2://Twinkle little star
      playSong2();
        fillRectangle(4,28, StrLength(Mc), 10, COLOR_WHITE);
	drawString5x7(29,5, "Ponyo", COLOR_BLACK, COLOR_WHITE);
	break;
    case 3://Lost woods
      playSong3();
        fillRectangle(4,40, StrLength(Woods), 10, COLOR_WHITE);
	drawString5x7(41,5, "Lost Woods", COLOR_BLACK, COLOR_WHITE);
	break;
    }

    
  }

  //inverts color back to normal
  if(counter == 250){
    
    switch(hover){
    case 0://Mary had a little lamb

	fillRectangle(4,4,StrLength(Mary),10,COLOR_BLACK);
	drawString5x7(5,5, "Mary Had a little Lamb", COLOR_WHITE, COLOR_BLACK);
	break;
    case 1://Old Mc Donald
      
	fillRectangle(4,16, StrLength(Mc), 10, COLOR_BLACK);
	drawString5x7(17,5, "Old Mc Donald", COLOR_WHITE, COLOR_BLACK);
	break;
    case 2://Twinkle little star
      playSong2();
        fillRectangle(4,28, StrLength(Mc), 10, COLOR_BLACK);
	drawString5x7(29,5, "Ponyo", COLOR_WHITE, COLOR_BLACK);
	break;
    case 3://Lost woods
       playSong3();
        fillRectangle(4,40, StrLength(Woods), 10, COLOR_BLACK);
	drawString5x7(41,5, "Lost Woods", COLOR_WHITE, COLOR_BLACK);
	break;
    }
    counter = 0;
    
  }
}


int main(){
  P1DIR |= LED;
  P1OUT |= LED;
  configureClocks();
  lcd_init();
  switch_init();

  enableWDTInterrupts();
  buzzer_init();
  or_sr(0x8);  
  
  clearScreen(COLOR_WHITE);

  //drawing the main screen
  fillRectangle(4,4,StrLength(Mary),10,COLOR_BLACK);
  drawString5x7(5,5, "Mary Had a little Lamb", COLOR_WHITE, COLOR_BLACK);

  fillRectangle(4,16, StrLength(Mc), 10, COLOR_BLACK);
  drawString5x7(17,5, "Old Mc Donald", COLOR_WHITE, COLOR_BLACK);
  
  fillRectangle(4,28, StrLength(Star), 10, COLOR_BLACK);
  drawString5x7(29,5, "Ponyo", COLOR_WHITE, COLOR_BLACK);
  
  fillRectangle(4,40, StrLength(Woods), 10, COLOR_BLACK);
  drawString5x7(41,5, "Lost Woods", COLOR_WHITE, COLOR_BLACK);


  while(play == 0){
    if(play == 1){
      fillRectangle(30,50,10,20, COLOR_BLACK);
    }else{
      
    }
  } 
  
  P1OUT &= ~LED;
  or_sr(0x10);
  P1OUT |= LED;

}
