/**
 * color
 * 
 */

#include <Servo.h>
#include <InkyBoard.h>
#include <Display.h>

InkyBoard B; // definieer B als InkyBoard
void setup() {
  B.DEBUG = true; // laat debug zien (via seriele poort)
  B.init(); // initieer het bord (de vier led's knipperen 1x bij opstaren)

  B.calibrateColor(B.CALIBRATE_BLACK); // zwart kalibreren, als debug aanstaat wordt er eerst 3 sec gewacht zodat je tijd hebt om papier voor de sensor te doen
  B.calibrateColor(B.CALIBRATE_WHITE); // ook wit kalibreren
}

void loop() {
  
}
