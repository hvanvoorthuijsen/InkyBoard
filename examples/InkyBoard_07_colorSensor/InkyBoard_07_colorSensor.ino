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
  B.init(); // initieer het bord 

  B.calibrateColor(B.CALIBRATE_BLACK); // zwart kalibreren, als debug aanstaat wordt er eerst 3 sec gewacht zodat je tijd hebt om papier voor de sensor te doen
  delay(1000);
  B.calibrateColor(B.CALIBRATE_WHITE); // ook wit kalibreren
}

void loop() {
    B.getColor(); // waardes worden weggeschreven naar seriele poort als debug aan staat
    
    /**
     * de waardes van de kleuren bevinden zich in:
     * B.colorR -> rood
     * B.colorG -> groen
     * B.colorB -> blauw
     */
    
    delay(500);
}