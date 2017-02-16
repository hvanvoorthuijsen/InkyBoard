/**
 * servo
 * Lees de potmeter uit en laat de servo de potmeter volgen
 */

#include <Servo.h>
#include <InkyBoard.h>
#include <Display.h>

InkyBoard B; // definieer B als InkyBoard
void setup() {
  B.init(); // initieer het bord (de vier led's knipperen 1x bij opstaren)
}

void loop() {
  B.setServo( B.getPot(true) ); // de functie getPot heeft een optionele parameter, als deze waar (true) is dan wordt de standaard waarde (0-1023) omgezet naar graden (0-180)

  //B.setServo( B.getLight(true) ); // de functie getLight heeft dezelfde optionele parameter als getPot
}





