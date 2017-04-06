/**
 * 
 */

#include <Servo.h>
#include <InkyBoard.h>
#include <Display.h>
#include <letters.h>

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

const static byte * hello [] = {L_H, L_E, L_L, L_L, L_O}; // een array met pointers naar de letters (de * geeft aan dat in de array pointers zitten naar een byte)

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
    //animation_5();
    //animation_6();
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

void animation_5(){
  static int i = 0; // een andere manier om een for loop te maken. static betekend dat hij maar één keer wordt geinitialiseerd als 0, hij blijft daarna beschikbaar.

  B.display.image(L_ALPHABET[i]); // laat de i-de letter zien van het alfabet
  delay(500);
  
  i++; // hoog i op
  if(i >= 26) i = 0; // meer dan 26 letters zijn er niet
}

void animation_6(){
  for(int i = 0; i < 5; i++){ // loop door de 5 letters heen van hello
    B.display.image(hello[i]); // laat de letter zien
    delay(200);
    B.display.clear();
    delay(50);
  }
  delay(500);
}
