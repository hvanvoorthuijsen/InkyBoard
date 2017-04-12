/*
 * We don't need inkyboard, only the display library
 */
#include <Display.h>

const static byte dots [] = {B00000000,B00011000,B00011000,B00000000,B00000000,B00011000,B00011000,B00000000} ;

// Set the pins and number of devices (displays)
const int DIN = 2;
const int CLK = 4;
const int LOAD = 8;
const int deviceCount = 8; // you need to connect 4 or 7 other displays to show the time (5 or 8 total with the buildin display)

/**
 * A little class to keep track of the time. Uses the millis() function, time is set on complile time.
 */
class Time{
  public:
    Time();
    void calculate();
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
  private:
    unsigned long lastCheck = 0;
};

/**
 * This constructor gets the time of compiling and convert it to hours, minutes and seconds
 */
Time::Time(){
  char time[] = __TIME__; // __TIME__ holds the time is this format 10:23:56 (hh:mm:ss)
  this->hours = (time[0] - '0') * 10; // to convert the character to an integer you substract the character '0'
  this->hours += time[1] - '0';
  this->minutes = (time[3] - '0') * 10;
  this->minutes += time[4] - '0';
  this->seconds = (time[6] - '0') * 10;
  this->seconds += time[7] - '0';
}

/**
 * calculates the time with the millis() function
 */
void Time::calculate(){
  this->seconds += (millis() - lastCheck)/1000;
  lastCheck = millis();
  
  this->minutes += this->seconds / 60;
  this->hours += (this->minutes / 60) % 24;
  
  this->seconds = this->seconds % 60;
  this->minutes = this->minutes % 60;

  Serial.print(this->hours);
  Serial.print(":");
  Serial.print(this->minutes);
  Serial.print(":");
  Serial.println(this->seconds);
}


Display display = Display(DIN, CLK, LOAD, deviceCount); // init the display
Time time = Time(); // init timekeeping

void setup() {
  Serial.begin(9600);
  Serial.println(__DATE__);
  /**
   * initialize all the displays
   */
  for(int i = 0; i < deviceCount; i++){
    /**
     * display.changeDevice(i).init(false); 
     *    is the same as:
     * display.changeDevice(i);
     * display.init(false);
     */
    display.changeDevice(i).init(false); 
  }
}

void loop() {
  static unsigned long timing = millis();
  static bool dotsOn = false;
  /**
   * keep track of the timing, after a second update the time
   */
  if( (millis() - timing) > 1000){
    timing = millis();
    time.calculate(); // calculate the time
    display.d(0).number(time.hours / 10); // display.d() is the same as display.changeDevice()
    display.d(1).number(time.hours % 10);
    display.d(3).number(time.minutes / 10);
    display.d(4).number(time.minutes % 10);
    display.d(2).image(dots);
    
    if(deviceCount == 8){ // only display seconds if there are 8 displays connected
      display.d(6).number(time.seconds / 10);
      display.d(7).number(time.seconds % 10);
      display.d(5).image(dots);
    }
    
    dotsOn = true;
  }
  else if( ((millis() - timing) > 500) && dotsOn){ // and after 0.5 seconds delete dots
    display.d(2).clear();
    if(deviceCount == 8){
      display.d(5).clear();
    }
    dotsOn = false;
  }
}
