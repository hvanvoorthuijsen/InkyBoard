/**
 * Alle functies worden hiermee getest.
 */

#include <Servo.h>
#include <InkyBoard.h>
#include <Display.h>

const static byte image_star [] = {B00010000,B00010000,B10111011,B11111110,B01111100,B00111000,B01101100,B11000110} ; 

InkyBoard B; // definieer B als InkyBoard
void setup() {
  B.init(); // initieer het bord 
  B.display.wakeup();
}

void loop() {
    buttons();
    B.setServo( B.getPot(true) );
    knock();
    color();
}

void buttons(){
    for(int i = 0; i < 4; i++){ 
        if(B.isButton(i)){ 
            B.setLED(i, B.ON); 
        }
        else{ // anders
            B.setLED(i, B.OFF);
        }
    }
}

void knock(){
    if(B.isKnock()){ 
        B.display.image(image_star);
        delay(100);
        B.display.clear();
    }
}

void color(){
    B.getColor(true);
    B.display.clear();
    
    colorToBar(B.colorR, 1);
    colorToBar(B.colorG, 3);
    colorToBar(B.colorB, 5);
}

byte colorToBar(int color, int y){
    color = map(color, 0, 255, 0, 9);
    
    for(int x = 0; x < color-1; x++){
        B.display.pixel(x, y, true);
    }
}