/**
 * 
 */

#include <Servo.h>
#include <InkyBoard.h>
#include <Display.h>

const static byte image_inky [] = {
    B00011100,
    B00100010,
    B01000001,
    B01010101,
    B01000001,
    B01000001,
    B01101011,
    B01010101
};

const static byte image_square [] = {B11111111,B10000001,B10000001,B10000001,B10000001,B10000001,B10000001,B11111111} ;
const static byte image_smile [] = {B00000000,B00000000,B00100100,B00000000,B00100100,B00011000,B00000000,B00000000} ;
const static byte image_boat [] = {B00000000,B00000000,B00000000,B00100000,B00110000,B00110000,B10100100,B11111000} ;

InkyBoard B; // definieer B als InkyBoard
void setup() {
    B.SPLASH = false; // laat inky niet zien bij opstarten
    B.init(); // initieer het bord 
    B.display.wakeup();

    randomSeed(B.getLight());
    
}

void loop() {
    animation_1();
    //animation_2();
    //animation_3();
    //animation_4();
}

void animation_1(){
    B.display.image(image_inky);  // afbeelding laten zien
    delay(500);
    B.display.clear(); // scherm leegmaken
    delay(500);
}

void animation_2(){
    B.display.image(image_smile); // afbeelding laten zien, overschrijf hele scherm
    delay(300);
    B.display.image(image_square, true); // afbeelding laten zien, voeg toe
    delay(300);
    B.display.clear(); // scherm leegmaken
    delay(300);
}

void animation_3(){
    for(int x = -6; x < 8; x++){ // positie x aanpassen zodat boot voorbij komt varen
        B.display.image(image_boat, x, 0); // afbeelding laten zien, op positie x (y blijft 0)
        delay(100);
    }
}

void animation_4(){
    B.display.image(image_smile); // afbeelding laten zien
    delay(100);
    B.display.shift(B.TOP, 2); // scherm opschuiven
    //B.display.shift(random(0,4), random(1,2)); // scherm opschuiven in willekeurige richting en met één of twee posities
    delay(300);
}
