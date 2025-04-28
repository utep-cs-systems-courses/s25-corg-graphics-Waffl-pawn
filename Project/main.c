#include <msp430.h>
#include <string.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "buzzer.h"
#include "stateMachines.h"
#include "switches.h"

#define LED BIT6;

static int state = 0;
int hover = 0;
static char p2val;

/*
static char switch_update_interrupt_sense(){
  p2val = P2IN;
  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);
  return p2val;
}

void switch_init(){
  P2REN |= SWITCHES;
  P2IE |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  switch_update_interrupt_sense();
}

int switches = 0;
int sw1Down = 0;
int sw2Down = 0;
int sw3Down = 0;
int sw4Down = 0;

void switch_interrupt_handler(){
  p2val = switch_update_interrupt_sense();
  
  //check if the button has been pressed
  sw1Down = (p2val & SW1) ? 0 : 1;
  sw2Down = (p2val & SW2) ? 0 : 1;
  sw3Down = (p2val & SW3) ? 0 : 1;
  sw4Down = (p2val & SW4) ? 0 : 1;

  if(sw1Down){
    if(hover == 0)
      hover = 3;
    else
      hover--;
  }
  else if(sw2Down){
    if(hover == 3)
      hover = 0;
    else
      hover++;
  }
  
  char p2val = switch_update_interrupt_sense();
}
*/

u_char width = screenWidth, height = screenHeight;
static char* Mary = "Marry Had a little Lamb";
static char* Mc = "Old Mc Donald";
static char* Star = "Twinkle Little Star";
static char* Woods = "Lost Woods";

void __interrupt_vec(WDT_VECTOR) WDT(){
  static int counter = 0;
  counter++;

  
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
      
        fillRectangle(4,28, StrLength(Mc), 10, COLOR_WHITE);
	drawString5x7(29,5, "Twinkle Little Star", COLOR_BLACK, COLOR_WHITE);
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
      
        fillRectangle(4,28, StrLength(Mc), 10, COLOR_BLACK);
	drawString5x7(29,5, "Twinkle Little Star", COLOR_WHITE, COLOR_BLACK);
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
  drawString5x7(29,5, "Twinkle Little Star", COLOR_WHITE, COLOR_BLACK);
  
  fillRectangle(4,40, StrLength(Woods), 10, COLOR_BLACK);
  drawString5x7(41,5, "Lost Woods", COLOR_WHITE, COLOR_BLACK);
  
  
  
  P1OUT &= ~LED;
  or_sr(0x10);
  P1OUT |= LED;

}

/*
void __interrupt_vec(PORT2_VECTOR) Port_2(){  
    if(P2IFG & SW1){
      P2IFG &= ~BIT0;
      switch_interrupt_handler();
    }

    if(P2IFG & SW2){    
      P2IFG &= ~BIT1;
      switch_interrupt_handler();
    }
}
*/
