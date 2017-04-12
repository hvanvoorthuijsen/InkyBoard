/**
 * rgb led
 * Hier laten we we rgb led kleuren weergeven
 */

#include <Servo.h>
#include <InkyBoard.h>
#include <Display.h>

InkyBoard::Color mixed_1 = {50, 100, 150}; // definieer de kleur mixed_1 direct
InkyBoard::Color mixed_2; // we definieren mixed_2 nog niet, doen we later

InkyBoard B; // definieer B als InkyBoard
void setup() {
  B.init(); // initieer het bord 

  // Hier zetten we de kleuren voor mixed2
  mixed_2.R = 150;
  mixed_2.G = 100;
  mixed_2.B = 50;
}

void loop() {
  B.setLED(B.GREEN, B.ON);
  B.setColor(B.GREEN); // Je kan de rgb dezelfde kleuren laten geven als de LED's, dus: B.YELLOW, B.GREEN, B.RED, B.BLUE
  delay(500);
  B.setLED(B.GREEN, B.OFF);
  
  B.setColor(B.cPurple); // Er zitten een aantal kleuren standaard ingebakken: cBlue, cGreen, cLightblue, cOrange, cPink, cPurple, cRed, cWhite, cYellow
  delay(500);
  
  B.setColor(mixed_1); // Je kunt natuurlijk ook zelf een kleur definiëren en laten zien
  delay(500);
  
  mixed_2.R += 100; // laten we rood aanpassen
  if(mixed_2.R > 255) mixed_2.R = mixed_2.R - 255; // kleur waardes liggen tussen 0 en 255
  B.setColor(mixed_2); // en deze kleuren kunnen on-the-fly aangepast worden
  delay(500);
}
