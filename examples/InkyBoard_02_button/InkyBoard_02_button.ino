/**
 * button
 * Als er op de bovenste knop gedrukt wordt, doe de bovenste LED aan
 * 
 * allButtons(): zelfde als hierboven maar dan voor alle knopjes
 */

#include <Servo.h>
#include <InkyBoard.h>
#include <Display.h>

InkyBoard B; // definieer B als InkyBoard
void setup() {
  B.init(); // initieer het bord 
}

void loop() {
  if(B.isButton(B.TOP)){ // als de button ingedrukt is
    B.setLED(B.TOP, B.ON); // doe de led aan
  }
  else{ // anders
    B.setLED(B.TOP, B.OFF); // doe de led uit
  }
  
  /**
   * Doe hetzelfde als hierboven maar dan voor alle knopjes
   */
  //allButtons();
}

void allButtons(){
  for(int i = 0; i < 4; i++){ // ver ander i van 0 - 3
    if(B.isButton(i)){ // als de i'de button waar is (0 = TOP, 1 = RIGHT, 2 = BOTTOM, 3 = LEFT)
      B.setLED(i, B.ON); // zet de i'de led aan
    }
    else{ // anders
      B.setLED(i, B.OFF); // zet de i'de led uit
    }
  }
}



