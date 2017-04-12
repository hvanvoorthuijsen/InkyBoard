#include <Servo.h>
#include <InkyBoard.h>
#include <Display.h>

InkyBoard B; // definieer B als InkyBoard

byte simonList[32];
int simonLengthToWin;
int simonListCount;

void setup() {
  B.init();
  Serial.begin(9600);
  simonStart();
}

void loop() {
  simonList[0] = simonWaits();

  simonListCount = 1;
  simonSays();
  delay(1000);
}

void simonStart(){
  randomSeed(analogRead(B.pLight)); // make sure the random function is random
  random(1000); // start up the random function (weird arduino stuff)
  simonLengthToWin = 10;
}

void simonSays(){
  B.setLED(simonList[0], B.OFF);
  delay(1000);
  
  Serial.println("simon says...");
  for(int i = simonListCount; i < simonLengthToWin; i++){
    simonDisplaySequence();
    if(!simonCheckPlayerInput()) return;
    simonAddToSequence();
  }
}

/**
 * 
 */
int simonWaits(){
  unsigned int refreshRate = 100;
  unsigned long refreshTimer = millis();
  int ledCounter = 0;
  while(1){
    if( (millis() - refreshTimer) > refreshRate){
      refreshTimer = millis();
      B.setLED(ledCounter,B.OFF); // turn off the current led
      ledCounter ++;
      if(ledCounter > 3) ledCounter = 0;
      B.setLED(ledCounter,B.ON); // turn on next led
    }

    // check if one of the buttons is pressed
    if(simonCheckButtons() >= 0) return ledCounter;
          
  }
}

void simonDisplaySequence(){
  
  for (int i = 0; i < simonListCount; i++){
    B.setLED(simonList[i], B.ON);
    delay(200);
    B.setLED(simonList[i], B.OFF);
    delay(200);
    Serial.print(simonList[i]);
    Serial.print(" ");
  }
  Serial.println("simon is done saying");
  delay(200);
}

bool simonCheckPlayerInput(){
  for (int i = 0; i < simonListCount; i++){
    unsigned long timer = millis();
    while(1){
      if( (millis() - timer) > 3000){
        Serial.println("timeout");
        return false; // timeout
      }

      int button = simonCheckButtons();
      if(button >= 0){
        if(simonList[i] != button){
          Serial.println("wrong button");
          return false; // wrong button
        }
        B.setLED(button, B.ON);
        delay(200); // debounce
        
        B.setLED(button, B.OFF);
        break; // break while loop
      }
    }
  }
  delay(500);
  return true;
}

void simonAddToSequence(){
  simonList[simonListCount] = random(0,4);
  simonListCount ++;
}

int simonCheckButtons(){
  for(int i = 0; i < 4; i++){
    if(B.isButton(i)) return i;
  }
  return -1;
}

