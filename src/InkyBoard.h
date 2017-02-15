/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   psb.h
 * Author: Henk-Jan <>
 *
 * Created on 7 december 2016, 16:17
 */

#ifndef INKYBOARD_H
#define INKYBOARD_H

#ifndef ARDUINO_ARCH_AVR
#define ARDUINO_ARCH_AVR
#endif

#include <Arduino.h>
#include <avr/pgmspace.h>
#include <Servo.h>
#include "Display.h"

class InkyBoard {
public:
    struct Color {
        byte R;
        byte G;
        byte B;
    };
    InkyBoard();
    /**
     * INIT
     */
    void init();
    /**
     * init servo, needs to be called if servo is not used with this library
     */
    void initServo();
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
    void setColor(Color color);
    /**
     * reed sensor is parallel to right button!
     * @return state of reed sensor
     */
    bool isReed();
    
    // LEDS
    const int pTopLed = 6;
    const int pBottomLed = 7;
    const int pLeftLed = 12;
    const int pRightLed = 13;

    const int apLed[4] = {pTopLed,pRightLed,pBottomLed,pLeftLed}; // Array with all LED pins

    // BUTTONS
    const int pTopButton = A2;
    const int pBottomButton = A3;
    const int pLeftButton = A4;
    const int pRightButton = A5;

    const int apButton[4] = {pTopButton,pRightButton,pBottomButton,pLeftButton}; // Array with all Button pins

    // POSITIONS 
    const int TOP = 0;
    const int RIGHT = 1;
    const int BOTTOM = 2;
    const int LEFT = 3;
    
    // ON / OFF
    const int ON = HIGH;
    const int OFF = LOW;
    const int TOGGLE = -1;
    
    // POTMETER
    const int pPot = A6;

    // SERVO
    const int pServo = 5;
    Servo servo;
    
    // KLOP SENSOR
    const int pKnock = A7;
    int knockThreshold = 200;

    // RGB LED
    const int pRedLed = 9;
    const int pGreenLed = 10;
    const int pBlueLed = 11;

    const int apRGB[3] = {pRedLed,pGreenLed,pBlueLed};

    // LIGHT SENSOR
    const int pLight = A1;
    int colorCalibration[6] = {970,840,1020,200,220,220};
    unsigned int colorTimer = 50;
    int colorR = 0;
    int colorG = 0;
    int colorB = 0;

    // LED MATRIX DISPLAY
    const int pMatrixDIN = 2;
    const int pMatrixCLK = 4;
    const int pMatrixLOAD = 8;
    Display display;
    
    // DEBUG
    bool DEBUG = false;
    bool SPLASH = true;
    
    // colors
    //http://www.computerhope.com/htmcolor.htm
    const Color cRed  = {0xFF,0x00,0x00};
    const Color cBlue = {0x00,0x00,0xFF};
    const Color cCyan = {0x00,0xFF,0x00};
    const Color cDarkblue = {0x00,0x00,0xA0};
    const Color cLightblue = {0xAD,0xD8,0xE6};
    const Color cPurple = {0x80,0x00,0x80};
    const Color cYellow = {0xFF,0xFF,0x00};
    const Color cGreen = {0x00,0xFF,0x00};
    const Color cMagenta = {0xFF,0x00,0xFF};
    const Color cWhite = {0xff,0xff,0xff};
    const Color cSilver = {0xC0,0xC0,0xC0};
    const Color cGray = {0x80,0x80,0x80};
    const Color cOrange = {0xFF,0xA5,0x00};
    const Color cBrown = {0xA5,0x2A,0x2A};
    const Color cMaroon = {0x80,0x00,0x00};
    const Color cDarkgreen = {0x00,0x80,0x00};
    const Color cOlive = {0x80,0x80,0x00};
    
private:
    void initLED_Buttons();
};

#endif /* INKYBOARD_H */

