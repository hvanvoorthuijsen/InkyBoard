/*
 *    Matrix.cpp - A library for controling Leds with a MAX7219/MAX7221
 *    Copyright (c) 2007 Eberhard Fahle
 * 
 *    Permission is hereby granted, free of charge, to any person
 *    obtaining a copy of this software and associated documentation
 *    files (the "Software"), to deal in the Software without
 *    restriction, including without limitation the rights to use,
 *    copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the
 *    Software is furnished to do so, subject to the following
 *    conditions:
 * 
 *    This permission notice shall be included in all copies or 
 *    substantial portions of the Software.
 * 
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *    OTHER DEALINGS IN THE SOFTWARE.
 */


#include "Display.h"
#include <Arduino.h>
#include "numbers.h"

//the opcodes for the MAX7221 and MAX7219
#define OP_NOOP   0
#define OP_DIGIT0 1
#define OP_DIGIT1 2
#define OP_DIGIT2 3
#define OP_DIGIT3 4
#define OP_DIGIT4 5
#define OP_DIGIT5 6
#define OP_DIGIT6 7
#define OP_DIGIT7 8
#define OP_DECODEMODE  9
#define OP_INTENSITY   10
#define OP_SCANLIMIT   11
#define OP_SHUTDOWN    12
#define OP_DISPLAYTEST 15

/******************
 * CLASS DISPLAY **
 *****************/

Display::Display(int pMatrixDIN, int pMatrixCLK, int pMatrixLOAD, int deviceCount)
: matrix(pMatrixDIN,pMatrixCLK,pMatrixLOAD,deviceCount){
    this->deviceCount = deviceCount;
}

void Display::init(bool SPLASH){
    this->wakeup();
    this->matrix.setIntensity(this->ADDRESS,8); // medium intensity
    this->matrix.clearDisplay(this->ADDRESS); // clear display
    if(SPLASH){
        for(int i = -7; i <= 0; i++){
            this->image(LOGO, i, i*-0.5);
            delay(50);
        }
        delay(500);

        this->pixel(3,3,false);
        delay(100);
        this->pixel(3,3,true);
        delay(200);

        for(int i = 0; i < 8; i++){
            this->image(LOGO, i, i*-0.5);
            delay(30);
        }
    }
}

Display& Display::changeDevice(int deviceNumber){
    if(deviceNumber < this->deviceCount) this->ADDRESS = deviceNumber;
    return *this;
}

Display& Display::d(int deviceNumber){
    if(deviceNumber < this->deviceCount) this->ADDRESS = deviceNumber;
    return *this;
}

void Display::setAutoSend(bool autoSend){
    this->matrix.autoSend = autoSend;
}

void Display::send(){
    this->matrix.send();
}

void Display::clear(){
    this->matrix.clearDisplay(this->ADDRESS);
}

void Display::sleep(){
    this->matrix.shutdown(this->ADDRESS,true); //powerup
}

void Display::wakeup(){
    this->matrix.shutdown(this->ADDRESS,false); //powerup
}

void Display::intensity(int intensity){
    this->matrix.setIntensity(this->ADDRESS,intensity);
}

void Display::image(byte image[], bool add){
    this->matrix.setScreen(this->ADDRESS, image, add);
}

void Display::image(const byte image[], bool add){
    this->matrix.setScreen(this->ADDRESS, image, add);
}

void Display::image(byte image[], int offset_x, int offset_y, bool add){
    byte newImage[] = {0,0,0,0,0,0,0,0};
    int newRow;
    for (int row = 0; row < 8; row++){
        newRow = row + offset_y;
        if(newRow >= 8) continue;
        if(newRow < 0 ) continue;
        if(offset_x > 0) newImage[newRow] = image[row] >> offset_x;
        else if(offset_x < 0) newImage[newRow] = image[row] << (offset_x * -1);
        else newImage[newRow] = image[row];
    }
    
    this->image(newImage, add);
}

void Display::image(const byte image[], int offset_x, int offset_y, bool add){
    byte newImage[] = {0,0,0,0,0,0,0,0};
    for (int row = 0; row < 8; row++){
        newImage[row] = image[row];
    }
    
    this->image(newImage, offset_x, offset_y, add);
}

void Display::pixel(int x, int y, bool state){
    this->matrix.setLed(this->ADDRESS, y, x, state);
}

void Display::row(byte data, int rowNr, bool add){
    this->matrix.setRow(this->ADDRESS, rowNr, data, add);
}

void Display::column(byte data, int columnNr, bool add){
    this->matrix.setColumn(this->ADDRESS, columnNr, data, add);
}

void Display::shift(int direction, int amount){
    this->matrix.shift(this->ADDRESS, direction, amount);
}

void Display::number(int number, int offset_x, int offset_y){
    this->clear(); // clear display
    if(number > 99){ // can't show number greater than 99
      return;
    }
    if(number > 9){ // if number is greater then 9
        offset_x += 2;
        int tens = number / 10; // then show tens seperatly
        this->number(tens, offset_x - 4, offset_y); // show tens
        number = number % 10; // replace number
    }

    switch(number){ // show the right number
      case 0:
        this->image(N_0_small, offset_x,offset_y,true);
        break;
      case 1:
        this->image(N_1_small, offset_x,offset_y,true);
        break;
      case 2:
        this->image(N_2_small, offset_x,offset_y,true);
        break;
      case 3:
        this->image(N_3_small, offset_x,offset_y,true);
        break;
      case 4:
        this->image(N_4_small, offset_x,offset_y,true);
        break;
      case 5:
        this->image(N_5_small, offset_x,offset_y,true);
        break;
      case 6:
        this->image(N_6_small, offset_x,offset_y,true);
        break;
      case 7:
        this->image(N_7_small, offset_x,offset_y,true);
        break;
      case 8:
        this->image(N_8_small, offset_x,offset_y,true);
        break;
      case 9:
        this->image(N_9_small, offset_x,offset_y,true);
        break;

    }
}

void Display::rotate(int rotation){
    this->matrix.rotate(this->ADDRESS, rotation);
}

/********************
 * SUBCLASS MATRIX **
 *******************/

Matrix::Matrix(int dataPin, int clkPin, int csPin, int numDevices) {
    SPI_MOSI=dataPin;
    SPI_CLK=clkPin;
    SPI_CS=csPin;
    if(numDevices<=0 || numDevices>8 )
        numDevices=8;
    maxDevices=numDevices;
    pinMode(SPI_MOSI,OUTPUT);
    pinMode(SPI_CLK,OUTPUT);
    pinMode(SPI_CS,OUTPUT);
    digitalWrite(SPI_CS,HIGH);
    SPI_MOSI=dataPin;
    for(int i=0;i<64;i++) 
        status[i]=0x00;
    for(int i=0;i<maxDevices;i++) {
        spiTransfer(i,OP_DISPLAYTEST,0);
        //scanlimit is set to max on startup
        setScanLimit(i,7);
        //decode is done in source
        spiTransfer(i,OP_DECODEMODE,0);
        clearDisplay(i);
        //we go into shutdown-mode on startup
        shutdown(i,true);
    }
}

int Matrix::getDeviceCount() {
    return maxDevices;
}

void Matrix::shutdown(int addr, bool b) {
    if(addr<0 || addr>=maxDevices)
        return;
    if(b)
        spiTransfer(addr, OP_SHUTDOWN,0);
    else
        spiTransfer(addr, OP_SHUTDOWN,1);
}

void Matrix::setScanLimit(int addr, int limit) {
    if(addr<0 || addr>=maxDevices)
        return;
    if(limit>=0 && limit<8)
        spiTransfer(addr, OP_SCANLIMIT,limit);
}

void Matrix::setIntensity(int addr, int intensity) {
    if(addr<0 || addr>=maxDevices)
        return;
    if(intensity>=0 && intensity<16)	
        spiTransfer(addr, OP_INTENSITY,intensity);
}

void Matrix::clearDisplay(int addr) {
    int offset;

    if(addr<0 || addr>=maxDevices)
        return;
    offset=addr*8;
    for(int i=0;i<8;i++) {
        status[offset+i]=0;
        if(this->autoSend) spiTransfer(addr, i+1,status[offset+i]);
    }
}

void Matrix::setLed(int addr, int row, int column, boolean state) {
    int offset;
    byte val=0x00;

    if(addr<0 || addr>=maxDevices)
        return;
    if(row<0 || row>7 || column<0 || column>7)
        return;
    offset=addr*8;
    val=B10000000 >> column;
    if(state)
        status[offset+row]=status[offset+row]|val;
    else {
        val=~val;
        status[offset+row]=status[offset+row]&val;
    }
    if(this->autoSend) spiTransfer(addr, row+1,status[offset+row]);
}

void Matrix::setRow(int addr, int row, byte value,boolean noClear) {
    int offset;
    if(addr<0 || addr>=maxDevices)
        return;
    if(row<0 || row>7)
        return;
    offset=addr*8;
    if(noClear){
        status[offset+row] = status[offset+row] | value;
    }
    else{
        status[offset+row]=value;
    }
    if(this->autoSend) spiTransfer(addr, row+1,status[offset+row]);
}

void Matrix::setScreen(int addr, byte value[], boolean noClear){
    if(addr<0 || addr>=maxDevices)
        return;
    for(int row = 0; row < 8; row++){
        if(noClear && !value[row]) continue;
        setRow(addr, row, value[row], noClear);
    }
}

void Matrix::setScreen(int addr, const byte value[], boolean noClear){
    if(addr<0 || addr>=maxDevices)
        return;
    for(int row = 0; row < 8; row++){
        if(noClear && !value[row]) continue;
        setRow(addr, row, value[row], noClear);
    }
}

void Matrix::setColumn(int addr, int col, byte value, boolean noClear) {
    byte val;
    if(addr<0 || addr>=maxDevices)
        return;
    if(col<0 || col>7) 
        return;
    for(int row=0;row<8;row++) {
        val=value >> (7-row);
        val=val & 0x01;
        if(noClear && !val) continue;
        setLed(addr,row,col,val);
    }
}

void Matrix::setDigit(int addr, int digit, byte value, boolean dp) {
    int offset;
    byte v;

    if(addr<0 || addr>=maxDevices)
        return;
    if(digit<0 || digit>7 || value>15)
        return;
    offset=addr*8;
    v=pgm_read_byte_near(charTable + value); 
    if(dp)
        v|=B10000000;
    status[offset+digit]=v;
    if(this->autoSend) spiTransfer(addr, digit+1,v);
}

void Matrix::setChar(int addr, int digit, char value, boolean dp) {
    int offset;
    byte index,v;

    if(addr<0 || addr>=maxDevices)
        return;
    if(digit<0 || digit>7)
        return;
    offset=addr*8;
    index=(byte)value;
    if(index >127) {
        //no defined beyond index 127, so we use the space char
        index=32;
    }
    v=pgm_read_byte_near(charTable + index); 
    if(dp)
        v|=B10000000;
    status[offset+digit]=v;
    if(this->autoSend) spiTransfer(addr, digit+1,v);
}

void Matrix::spiTransfer(int addr, volatile byte opcode, volatile byte data) {
    //Create an array with the data to shift out
    int offset=addr*2;
    int maxbytes=maxDevices*2;

    for(int i=0;i<maxbytes;i++)
        spidata[i]=(byte)0;
    //put our device data into the array
    spidata[offset+1]=opcode;
    spidata[offset]=data;
    //enable the line 
    digitalWrite(SPI_CS,LOW);
    //Now shift out the data 
    for(int i=maxbytes;i>0;i--)
        shiftOut(SPI_MOSI,SPI_CLK,MSBFIRST,spidata[i-1]);
    //latch the data onto the display
    digitalWrite(SPI_CS,HIGH);
}    

void Matrix::shift(int addr, int direction, int amount){
    int offset;
    if(addr<0 || addr>=maxDevices)
            return;
    offset=addr*8;
    
    if(amount > 8){
        this->clearDisplay(addr);
    }
    
    int newRow;
    switch(direction){
        case 0:
            for (int row = 0; row <8; row++){
                newRow = row + amount;
                if(newRow >= 8) status[offset+row] = 0;
                else status[offset+row] = status[offset+newRow];

                if(this->autoSend) spiTransfer(addr, row+1,status[offset+row]);
            }
            break;
        case 2:
            for (int row = 7; row >= 0; row--){
                newRow = row - amount;
                if(newRow < 0) status[offset+row] = 0;
                else status[offset+row] = status[offset+newRow];

                if(this->autoSend) spiTransfer(addr, row+1,status[offset+row]);
            }
            break;
        case 1:
            for (int row = 0; row < 8; row++){
                status[offset+row] = status[offset+row] >> amount;
                if(this->autoSend) spiTransfer(addr, row+1,status[offset+row]);
            }
            break;
        case 3:
            for (int row = 0; row < 8; row++){
                status[offset+row] = status[offset+row] << amount;
                if(this->autoSend) spiTransfer(addr, row+1,status[offset+row]);
            }
            break;
    }
    
}

void Matrix::rotate(int addr, int rotation){
    int offset;
    if(addr<0 || addr>=maxDevices)
            return;
    offset=addr*8;
    
    byte newStatus[] = {0,0,0,0,0,0,0,0};
    switch(rotation){
        case 1: // rotate 90 degrees cw
            for(int row = 0; row < 8; row++){
                for(int column = 0; column < 8; column++){
                    if(status[offset+row] & 1 << column) newStatus[7-column] = newStatus[7-column] | 1 << (row);
                }
            }
            break;
        case 2: //rotate 180
            for(int row = 0; row < 8; row++){
                for(int column = 0; column < 8; column++){
                    if(status[offset+row] & 1 << column) newStatus[7-row] = newStatus[7-row] | 1 << (7-column);
                }
            }
            break;
        case 3: // rotate 270 cw
            for(int row = 0; row < 8; row++){
                for(int column = 0; column < 8; column++){
                    if(status[offset+row] & 1 << column) newStatus[column] = newStatus[column] | 1 << (7-row);
                }
            }
            break;
        case 4: // flip horizontal
            for(int row = 0; row < 8; row++){
                newStatus[row] = status[offset+7-row];
            }
            break;
        case 5: // flip vertical
            for(int row = 0; row < 8; row++){
                for(int column = 0; column < 8; column++){
                    if(status[offset+row] & 1 << column) newStatus[row] = newStatus[row] | 1 << (7-column);
                }
            }
            break;
    }
    
    for(int row = 0; row < 8; row++){
        status[offset+row] = newStatus[row];
        if(this->autoSend) spiTransfer(addr, row+1, status[offset+row]);
    }
}

void Matrix::send(){
    if(this->autoSend) return;
    for(int d = 0; d < this->maxDevices; d++){
        for(int row = 0; row < 8; row++){
            spiTransfer(d, row+1,status[(d*8)+row]);
        }
    }
}