#include <msp430.h>
#include <string.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "buzzer.h"

#define LED BIT6

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8

#define SWITCHES 15

static int state = 0;
static int hover = 0;

static char switch_update_interrupt_sense(){
  char p2val = P2IN;
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

void switch_interrupt_handler(){
  char p2val = switch_update_interrupt_sense();
  switches = ~p2val & SWITCHES;
}

u_char width = screenWidth, height = screenHeight;


void wdt_c_handler(){
  static int counter = 0;
  counter++;

  
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

  char* Mary = "Marry Had a little Lamb";
  fillRectangle(4,4,StrLength(Mary),10,COLOR_BLACK);
  drawString5x7(5,5, "Mary Had a little Lamb", COLOR_WHITE, COLOR_BLACK);

  char* Mc = "Old Mc Donald";
  fillRectangle(4,16, StrLength(Mc), 10, COLOR_BLACK);
  drawString5x7(17,5, "Old Mc Donald", COLOR_WHITE, COLOR_BLACK);
  
  
  switch(state){
  case 0:
    if(hover == 0){
      
    }
    if(hover == 1){

    }
    break;
  case 1:
    break;
  }

  
  //enableWDTInterrupts();
  
  P1OUT &= ~LED;
  or_sr(0x10);
  P1OUT |= LED;

}


void __interrupt_vec(PORT2_VECTOR) Port_2(){  
    if(P2IFG & SW1){
      if(state == 0){
	hover = 1;
      }else{
	state = 1;
      }
	
      P2IFG &= ~BIT0;
      switch_interrupt_handler();
    }

    if(P2IFG & SW2){
      if(state == 0){
	hover = 0;
      }else{
	state = 1;
      }
      
      P2IFG &= ~BIT1;
      switch_interrupt_handler();
    }
}
