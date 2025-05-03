#include <msp430.h>
#include "stateMachines.h"
#include "buzzer.h"
#include "notes.h"

//Ponyo Theme
void playSong2(){
  static char currNote = 0;
  //notes of song as list, 0 denotes a rest

  int notes[20] = {BSH4,BSH4,D5,F5,F5,D5,BSH4,
		   C5,D5,D5,C5,BSH4,C5,D5,
		   F5,D5,BSH4,G4,A4,BSH4};
  int n = 20;
  if(currNote <n){
    buzzer_set_period(notes[currNote]);
    currNote++;
  }else{
    currNote = 0;
  }
}

//lost woods
void playSong3(){
  static char currNote = 0;
  //notes of song as list, 0 denotes a rest

  int notes[25] = {F,A,B,B,F,A,B,B,
		   F,A,B,E,D,0,B,C,B,G,E,D,E,G,E
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
