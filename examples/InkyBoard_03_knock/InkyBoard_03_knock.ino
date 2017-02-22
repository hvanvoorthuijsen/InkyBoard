/**
 * knock
 * Als er op het bord getikt wordt dan gaat er een LED aan
 * De leds branden op volgorde
 */

#include <Servo.h>
#include <InkyBoard.h>
#include <Display.h>

InkyBoard B; // definieer B als InkyBoard

void setup() {
  B.init(); // initieer het bord 
}

void loop() {
    /**
     * Een static variabele wordt niet verwijderd aan het eind van de functie zoals een 'gewone' variabele. De variabele is elke keer weer beschikbaar (alleen in deze functie!).
     * De waarde die erachter staat wordt alleen de eerste keer toegewezen, daarna niet meer.
     */
  static int ledCounter = 0; // Counter om bij te houden welke led aan moet.
  
  if(B.isKnock()){ // Als er een tik is gedetecteerd
    B.setLED(ledCounter, B.ON); // LED aan
    delay(200); // Even aan laten
    B.setLED(ledCounter, B.OFF); LED uit
    ledCounter++; // Volgende LED
    if(ledCounter >= 4) ledCounter = 0; // Er zijn maar 4 LED's (0-3)
  }
}
