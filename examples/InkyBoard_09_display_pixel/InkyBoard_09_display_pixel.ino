/**
 * 
 */

#include <Servo.h>
#include <InkyBoard.h>
#include <Display.h>

InkyBoard B; // definieer B als InkyBoard
void setup() {
    B.SPLASH = false; // laat inky niet zien bij opstarten
    B.init(); // initieer het bord
    B.display.wakeup(); // display aan
}

void loop() {
    fill();
    //random_pixel();
}

void fill(){
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            B.display.pixel(x,y,true); // pixel aan
            delay(50);
        }
    }
    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
            B.display.pixel(x,y,false); // pixel uit
            delay(50);
        }
    }
}

void random_pixel(){
    static bool firstTime = true;
    
    if(firstTime){
        randomSeed(B.getLight()); // de eerste keer een willekeurige waarde in de randomSeed functie zetten zodat de waardes voor random willekeuriger zijn.
        firstTime = false;
    }
    
    int x = random(0,8); // een getal van 0 - 7
    int y = random(0,8);
    B.display.pixel(x, y, true);
    delay(50);
    B.display.pixel(x, y, false);
}