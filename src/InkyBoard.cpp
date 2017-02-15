/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   psb.cpp
 * Author: Henk-Jan <>
 * 
 * Created on 7 december 2016, 16:17
 */

#include <Arduino.h>
#include <avr/pgmspace.h>
#include "Display.h"
#include "InkyBoard.h"

InkyBoard::InkyBoard()
: display(InkyBoard::pMatrixDIN, InkyBoard::pMatrixCLK, InkyBoard::pMatrixLOAD){
    
}

void InkyBoard::init(){
    if(this->DEBUG){
        Serial.begin(9600);
    }
    this->initLED_Buttons();
    this->display.init(this->SPLASH);
    this->display.sleep();
}

void InkyBoard::initLED_Buttons(){
    
    // set LED and button pins
    for(int i = 0; i < 4; i++){
        pinMode(this->apLed[i], OUTPUT);
        digitalWrite(this->apLed[i],LOW); // LED OFF
        pinMode(this->apButton[i], INPUT);

        if(i < 3){
            pinMode(this->apRGB[i],OUTPUT);
            digitalWrite(this->apRGB[i], LOW);
        }
    }
    
}

void InkyBoard::initServo(){
    this->servo.attach(this->pServo, 600, 2400);
}


/**
 * Get potientiometer value
 * @param servoReady convert value to degrees (0-180)
 * @return position 0-1023 or 0-180
 */
void InkyBoard::setServo(int pos){
    static int prevServoPos = -1;
    if(prevServoPos == -1){
        this->initServo();
    }
    pos = 180-pos; // invert position
    if(prevServoPos != pos){
        prevServoPos = pos;
        this->servo.write(pos);
    }
}
/**
 * Get potientiometer value
 * @param servoReady convert value to degrees (0-180)
 * @return position 0-1023 or 0-180
 */
int InkyBoard::getPot(bool servoReady){
    /**
    * @todo: bij v1 bord zit de potmeter andersom! mag weg bij v2!
    */
    int potVal = 1023 - analogRead(this->pPot);
    
    if(servoReady){
        
        potVal = map(potVal, 0,1023,0,180); // map pot value to degrees
    }
    
    if(this->DEBUG){
        static int prevValue = -1;
        if(prevValue != potVal){
            prevValue = potVal;
            Serial.println(potVal);
        }
    }
    
    return potVal;
}
/**
 * Set led
 * @param ledNr number of led (not port!) (.TOP, .BOTTOM, .LEFT, .RIGHT)
 * @param state (.ON, .OFF, .TOGGLE(default) )
 */
void InkyBoard::setLED(int ledNr, int state){
    static int ledStates[4] = {0,0,0,0};
    
    if(state == -1){ // toggle
        state = 1 - ledStates[ledNr];
    }
    
    ledStates[ledNr] = state;
    digitalWrite(this->apLed[ledNr], state);
}
/**
* 
* @return state of knock
*/
bool InkyBoard::isKnock(){
    static unsigned long knockTimer = millis();
    
    int knockValue = analogRead(this->pKnock);

    if(knockValue >= this->knockThreshold && (millis() - knockTimer) > 20){ // debounce!
        knockTimer = millis();
        if(this->DEBUG) Serial.println(F("KNOCK!"));
        return true;
    }
    else{
        return false;
    }
}
/**
 * 
 * @param buttonNr number of button (not port!) (.TOP, .BOTTOM, .LEFT, .RIGHT)
 * @return state of button
 */
bool InkyBoard::isButton(int buttonNr){
    return (digitalRead(this->apButton[buttonNr]))?true:false;
}
/**
 * Set RGB LED
 * @param R value red 0-255
 * @param G value green 0-255
 * @param B value blue 0-255
 */
void InkyBoard::setRGB(int R, int G, int B){
    if(R >= 0) analogWrite(this->pRedLed, R);
    if(G >= 0) analogWrite(this->pGreenLed, G);
    if(B >= 0) analogWrite(this->pBlueLed, B);
}
/**
 * Get value light sensor
 * @param servoReady map naar 0-180
 * @return value light sensor 0-1023
 */
int InkyBoard::getLight(bool servoReady){
    int value = analogRead(this->pLight);
    if(servoReady){
        value = map(value, 0, 1023, 0, 180);
    }
    if(this->DEBUG){
        Serial.print(F("light sensor: "));
        Serial.println(value);
    }
    
    return value;
}
/**
 * get reflected light from RGB and write R, G and B value to .colorR, .colorG, .colorB
 */
void InkyBoard::getColor(bool continuous){
    static unsigned long colorTimer = millis();
    static int counter = 0;
    
    if(continuous){
        if((millis() - colorTimer) > this->colorTimer){
            colorTimer = millis();
            for (int i = 0; i < 3; i++){
                int value = (counter == i)?HIGH:LOW;
                digitalWrite(this->apRGB[i], value);
            }

            int color = analogRead(this->pLight);
            color = constrain(map(color, this->colorCalibration[counter+3], this->colorCalibration[counter], 0, 255),0,255);
            switch(counter){
                case 0:
                    this->colorR = color;
                    break;
                case 1:
                    this->colorG = color;
                    break;
                case 2:
                    this->colorB = color;
                    break;
            }

            counter ++;
            if(counter >= 3) counter = 0;
        }
    }
    else{
        for (int i = 1; i < 3; i++){
            digitalWrite(this->apRGB[i], LOW);
        }
        for (counter = 0; counter < 3; counter ++){
            if(counter > 0) digitalWrite(this->apRGB[counter-1], LOW);
            digitalWrite(this->apRGB[counter], HIGH);
            
            int color = analogRead(this->pLight);
            color = constrain(map(color, this->colorCalibration[counter+3], this->colorCalibration[counter], 0, 255),0,255);
            switch(counter){
                case 0:
                    this->colorR = color;
                    break;
                case 1:
                    this->colorG = color;
                    break;
                case 2:
                    this->colorB = color;
                    break;
            }
            delay(this->colorTimer);
        }
        counter = 0;
    }
    if(this->DEBUG && counter == 0){
        Serial.print(F("color sensor: R="));
        Serial.print(this->colorR);
        Serial.print(F(" G="));
        Serial.print(this->colorG);
        Serial.print(F(" B="));
        Serial.println(this->colorB);
    }
}
/**
 * Set RGB to predefined color
 * @param color predefined color array
 */
void InkyBoard::setColor(InkyBoard::Color color){
    analogWrite(this->pRedLed, color.R);
    analogWrite(this->pGreenLed, color.G);
    analogWrite(this->pBlueLed, color.B);
}
/**
 * reed sensor is parallel to right button!
 * @return state of reed sensor
 */
bool InkyBoard::isReed(){
    return true;
}
