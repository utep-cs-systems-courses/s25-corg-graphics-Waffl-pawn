#include <msp430.h>
#include "stateMachines.h"
#include "buzzer.h"
#include "notes.h"


//lost woods
void playSong3(){
  static char currNote = 0;
  //notes of song as list, 0 denotes a rest

  int notes[25] = {F,A,B,F,A,B,
		   F,A,B,E,D,B,C,B,G,E,D,E,G,E
		   ,F,A,B,F,A,B
		   ,F,A,B,E,D,B,C,E,C,G,B,G,D,E
		   ,F,G,A,B,C,D,E,F,G};
  int n = 25;
  if(currNote <n){
    buzzer_set_period(notes[currNote]);
    currNote++;
  }else{
    currNote = 0;
  }
    
}
