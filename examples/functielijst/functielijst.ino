/**
 * functielijst
 * niet bedoeld als werkend programma!
 * 
 * gebruik functies, constanten en variabelen is altijd met B. ervoor!
 * Bijv: B.init();
 */

#include <Servo.h>
#include <bps.h>
#include <matrix.h>

BPS B; // definieer B als bord.programmeren.school


void setup(){
  
}

void loop(){
  
}

/****************
 *** FUNCTIES ***
 ***************/

 
/**
 * INIT BOARD
 */
void init();
/**
 * Set servo to pos
 * @param pos position in degrees
 */
void setServo(int pos);
/**
 * Get potientiometer value
 * @param servoReady convert value to degrees (0-180)
 * @return position 0-1023 or 0-180
 */
int getPot(bool servoReady = false);
/**
 * Set led
 * @param ledNr number of led (not port!) (.TOP, .BOTTOM, .LEFT, .RIGHT)
 * @param state (.ON, .OFF, .TOGGLE(default) )
 */
void setLED(int ledNr, int state = -1);
/**
 * 
 * @return state of knock
 */
bool isKnock();
/**
 * 
 * @param buttonNr number of button (not port!) (.TOP, .BOTTOM, .LEFT, .RIGHT)
 * @return state of button
 */
bool isButton(int buttonNr);
/**
 * Set RGB LED
 * @param R value red 0-255
 * @param G value green 0-255
 * @param B value blue 0-255
 */
void setRGB(int R = -1, int G = -1, int B = -1);
/**
 * Get value light sensor
 * @param servoReady map naar 0-180
 * @return value light sensor 0-1023
 */
int getLight(bool servoReady = false);
/**
 * get reflected light from RGB and write R, G and B value to .colorR, .colorG, .colorB
 * @param continuous wait for all colors or do it continuous
 */
void getColor(bool continuous = true);
/**
 * Set RGB to predefined color
 * @param color predefined color array
 */


/******************
 *** CONSTANTEN ***
 *****************/

const int TOP = 0;
const int RIGHT = 1;
const int BOTTOM = 2;
const int LEFT = 3;
const int ON = HIGH;
const int OFF = LOW;
const int TOGGLE = -1;

/**
 * Pinnummers
 */
const int pTopLed = 6;
const int pBottomLed = 7;
const int pLeftLed = 12;
const int pRightLed = 13;
const int pTopButton = A2;
const int pBottomButton = A3;
const int pLeftButton = A4;
const int pRightButton = A5;
const int pPot = A6;
const int pServo = 5;
const int pKnock = A7;
const int pRedLed = 9;
const int pGreenLed = 10;
const int pBlueLed = 11;
const int pLight = A1;
const int pMatrixDIN = 2;
const int pMatrixCLK = 4;
const int pMatrixLOAD = 8;

/******************
 *** VARIABELEN ***
 *****************/
int knockThreshold = 200; // drempelwaarde voor de analoge input van de klopsensor, lager = gevoeliger
int colorTimer = 50; // snelheid van kleurmeting
int colorR = 0; // bevat weerkaatsing rood licht (na uitlezen kleuren)
int colorG = 0; // bevat weerkaatsing groen licht (na uitlezen kleuren)
int colorB = 0; // bevat weerkaatsing blauw licht (na uitlezen kleuren)
bool DEBUG = false; // als deze true is dan wordt er via de seriele poort gedebugged 
