/**
 * functielijst
 * niet bedoeld als werkend programma!
 * 
 * gebruik functies, constanten en variabelen is altijd met B. ervoor!
 * Bijv: B.init();
 */

#include <Servo.h>
#include <InkyBoard.h>
#include <Display.h>

InkyBoard B; // definieer B als InkyBoard


void setup(){
    B.init();
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
void getColor(bool continuous = false);
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
const int RED = 0;
const int YELLOW = 1;
const int GREEN = 2;
const int BLUE = 3;
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
int knockThreshold = 100; // drempelwaarde voor de analoge input van de klopsensor, lager = gevoeliger
int colorTimer = 50; // snelheid van kleurmeting
int colorR = 0; // bevat weerkaatsing rood licht (na uitlezen kleuren)
int colorG = 0; // bevat weerkaatsing groen licht (na uitlezen kleuren)
int colorB = 0; // bevat weerkaatsing blauw licht (na uitlezen kleuren)
bool DEBUG = false; // als deze true is dan wordt er via de seriele poort gedebugged 
bool SPLASH = true; // als deze false is wordt er geen splash (inky) getoond bij opstarten. Moet voor init worden veranderd!


/***************
 *** DISPLAY ***
 **************/

/*
 Het display wordt automatisch geinitialiseerd als B.display
 */

/**
 * Clear display
 */
void clear();
/**
 * Put display in sleep mode => default!
 */
void sleep();
/**
 * Wakeup display
 */
void wakeup();
/**
 * Set intensity
 * @param intensity
 */
void intensity(int intensity);

/**
 * Set an image on the screen.
 * @param image byte array with array of 8 rows
 * @param offset_x 
 * @param offset_y
 * @param add if true: image is overlayed on current screen
 */
void image(byte image[], bool add = false);
void image(byte image[], int offset_x, int offset_y, bool add = false);

/**
 * Set pixel on screen
 * @param x
 * @param y
 * @param state state of the pixel
 */
void pixel(int x, int y, bool state = true);
/**
 * Set row
 * @param data Every bit in this byte is a pixel in that row
 * @param rowNr
 * @param add if true: image is overlayed on current row
 */
void row(byte data, int rowNr, bool add = false);
/**
 * Set column (this is slower than row, because this is an non-native function)
 * @param data Every bit in this byte is a pixel in that column
 * @param columnNr
 * @param add if true: image is overlayed on current column
 */
void column(byte data, int columnNr, bool add = false);
/**
 * Shift screen
 * @param direction .TOP, .BOTTOM, .LEFT, .RIGHT
 * @param amount
 */
void shift(int direction, int amount = 1);

/**
 * show Number
 * @param number 0-99
 * @param offset_x
 * @param offset_y
 */
void number(int number, int offset_x = 3, int offset_y = 2);

/**
 * Rotate the current visible display
 * @param rotation display. + ROTATE_90, ROTATE_180, ROTATE_270, FLIP_H, FLIP_V
 */
void rotate(int rotation);

/**
 * Send to display(s) directly after each command or wait for send
 * @param autoSend
 */
void setAutoSend(bool autoSend);

/**
 * if autosend = false this function sends the buffer to the display(s)
 */
void send();