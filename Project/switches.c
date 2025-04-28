#include <msp430.h>
#include "switches.h"
#include "main.c"

int sw1Down = 0;
int sw2Down = 0;
int sw3Down = 0;
int sw4Down = 0;

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

  sw1Down = (p2val & SW1) ? 0 : 1;
  sw2Down = (p2val & SW2) ? 0 : 1;
  sw3Down = (p2val & SW3) ? 0 : 1;
  sw4Down = (p2val & SW4) ? 0 : 1;

  if(sw1Down){
    if(hover == 0)
      hover = 3;
    hover--;
  }
  else if(sw2Down){
    if(hover == 3)
      hover = 0;
    hover++;
  }
  
  switches = ~p2val & SWITCHES;
}
