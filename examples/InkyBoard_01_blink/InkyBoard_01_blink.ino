/**
 * button
 * Als er op de bovenste knop gedrukt wordt, doe de bovenste LED aan
 */

#include <Servo.h>
#include <InkyBoard.h>
#include <Display.h>

InkyBoard B; // definieer B als InkyBoard
void setup() {
  B.init(); // initieer het bord 
}

void loop() {
  B.setLED(B.TOP); // wissel top led van status (aan wordt uit, uit wordt aan)
  delay(500);

  /**
   * Haal de // weg voor deze functie en plaats dat voor de regels hierboven zodat alleen de functie rotate() aangeroepen wordt.
   */
  //rotate();
}

/**
 * Doe alle 4 de LEDS om de beurt aan en weer uit
 */
void rotate(){
  for (int i = 0; i < 4; i++){
    B.setLED(i, B.ON); // zet de i'de LED aan (0 = top, 1 = right, 2 = bottom, 3 = left)
    delay(300);
    B.setLED(i, B.OFF); // zet de i'de LED uit
  }
}

