#include <Servo.h>
#include <InkyBoard.h>
#include <Display.h>

InkyBoard B; // definieer B als InkyBoard

void setup() {
  // put your setup code here, to run once:
  B.init();
  B.display.wakeup();
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 99; i++){
    B.display.number(i);
    delay(250);
  }
}
