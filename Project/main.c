#include <string.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

#define LED BIT6

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8

#define SWITCHES 15

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

void switch_interrupt_handler(){
  char p2val = switch_update_interrupt_sense();
  switches = ~p2val & SWITCHES;
}

void wdt_c_handler(){
  
}

int main(){
  P1DIR |= LED;
  P1OUT |= LED;
  configureClocks();
  lcd_init();
  switch_init();

  enableWDTInterrupts();
  configure_buttons();
  buzzer_init();
  
  or_sr(0x8);

  
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_WHITE);

  char* Mary = "Marry Had a little Lamb";

  fillRectangle(4,4,StrLength(Mary),10,COLOR_BLACK);

  drawString5x7(5,5, "Mary Had a little Lamb", COLOR_WHITE, COLOR_BLACK);

  // fillRectangle(30,30, 60, 60, COLOR_ORANGE);

}


void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if(P2IFG & SWITCHES){
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}
