/**
 * potmeter
 * Lees de potmeter uit, doe wat wiskunde en de lampjes draaien (bijna) 10x rond voor een hele slag van de potmeter
 */

#include <Servo.h>
#include <InkyBoard.h>
#include <Display.h>

InkyBoard B; // definieer B als InkyBoard
void setup() {
  B.init(); // initieer het bord 
}

void loop() {
  int value = B.getPot(); // haal waarde van potmeter op
  value = value / 26; // deel deze door 26, resultaat ligt tussen 0 - 40
  int led = value%4; // modulo 4, wat rest ligt tussen 0 - 3, dit kunnen we als ledNr gebruiken
  turnOnLed(led); // doe de led aan
}

void turnOnLed(int ledNr){
  for(int i = 0; i < 4; i++){ // verander i van 0 - 3 (alle leds langsgaan)
    if(ledNr == i){ // als i hetzelfde is als het nummer van de led die aan moet
      B.setLED(i, B.ON); // doe de led aan
    }
    else{ // anders
      B.setLED(i, B.OFF); // doe de led uit
    }
  }
}



