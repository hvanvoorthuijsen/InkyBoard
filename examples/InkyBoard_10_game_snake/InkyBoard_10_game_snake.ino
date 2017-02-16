#include <Servo.h>
#include <InkyBoard.h>
#include <Display.h>

InkyBoard B; // definieer B als InkyBoard

// structure for holding coordinates
struct snakePart{
  int x;
  int y;
};

unsigned long snakeRefreshRate; // refreshrate of snake (higher means longer to refresh = slower snake)
volatile snakePart parts[64]; // array to hold snakeparts, max 64 => no more dots on screen
int snakeLength; // length of the snake
int p_parts; // pointer for snake array
int snakeDirection; // direction of this snake
snakePart apple; // location of the apple
boolean appleEaten; // 
boolean ghost; // in ghost mode, snake can go through walls

int highScore = 0;

const static byte PRIZE [] = {B01111110,B10111101,B10111101,B01111110,B00111100,B00011000,B00011000,B00111100};

void setup() {
  B.init();
  B.display.wakeup();
  
  snakeStart(); // initialize the snake
  
  Serial.begin(9600);
}

void loop() {
  snake(); // run the snake code
}

/**
 * Initialize the snake
 */
void snakeStart(){
  snakeLength = 5; // startup length of the snake
  parts[0].x = 0; // starting x position
  parts[0].y = 0; // starting y position
  snakeDirection = 1; // starting direction
  snakeRefreshRate = 100; // starting speed
  ghost = true; // gost mode
  
  randomSeed(analogRead(B.pLight)); // make sure the random function is random
  random(1000); // start up the random function (weird arduino stuff)

  // make sure the tail is not on the screen on startup
  for(int i=(65-snakeLength); i< 64; i++){
    parts[i].x = -1;
    parts[i].y = -1;
  }
  
  p_parts = 1; // reset the pointer to 1
  appleEaten = true; // make sure a new apple is created 
}

/**
 * Main snake function
 */
void snake(){
  static unsigned long snakeTimer = millis(); // start the snake timer

  checkSnakeDirection(); // check direction change (and do this every loop!)
  
  if((millis() - snakeTimer) > snakeRefreshRate){ // check if 
    snakeTimer = millis();
    
    checkSnakeSpeed(); // check speed change
    moveSnake(); // move snake 1 step in direction
    drawSnake(); // draw new snake
    makeApple(); // make and draw an apple
  }
}

/**
 * Check if button is pressed and change direction accordingly
 */
void checkSnakeDirection(){
  for(int i = 0; i < 4; i++){ // check all 4 buttons
    if(digitalRead(B.apButton[i])){ // if button is high
      if(i != (snakeDirection + 2) && i != (snakeDirection -2)){ // only change direction if the snake won't turn backwards
        snakeDirection = i; // change direction
      }
    }
    else{
      digitalWrite(B.apLed[i], LOW); // LED's off
    }
  }
  digitalWrite(B.apLed[snakeDirection], HIGH); // Direction LED on
}

/**
 * Check and changes snakespeed (or actualy refresh rate)
 */
void checkSnakeSpeed(){
  snakeRefreshRate = map(B.getPot(),0,1023,300,50); // get pot value and use it to set snake speed (lower is faster)
  B.setServo(B.getPot(true)); // show speed with the servo
}

/**
 * Draw the snake
 */
void drawSnake(){
  B.display.clear();  // clear display
  
  int pos;
  int headPos = p_parts - 1; // get position of the head in the array with snake parts
  if(headPos >= 64) pos = 0; // array is only 64 items big

  boolean collision = false;
  
  snakePart head = {parts[headPos].x, parts[headPos].y}; // the head of the snake
  
  for(int i = 0; i < snakeLength; i++){ // go through every snake part
    pos = p_parts - snakeLength + i; // this is the position in the array
    if(pos < 0) pos = 64 + pos; // cant be smaller than 0
    else if(pos >= 64) pos = pos - 64; // and bigger than 63

    if(parts[pos].x == head.x && parts[pos].y == head.y && headPos != pos){ // check if the x and y of this part is not the same as the head
      collision = true; // if they are the same: collision with itself!
    }
    
    B.display.pixel(parts[pos].x, parts[pos].y); // display snake part
  }

  if(collision){
    snakeRestart(); // the snake is dead, so restart
  }
}

/**
 * Move the snake (remove tail and make new head)
 */
void moveSnake(){
  boolean collision = false;
  
  int pos = p_parts -1; // current array position
  if(pos < 0) pos = 64 + pos; // smaller than 0 is not possible
  else if(pos >= 64) pos = pos - 64; // bigger than 63 neither

  snakePart p = {parts[pos].x, parts[pos].y}; // current head
  switch(snakeDirection){ 
    case 0:
      p.y--; // up (y starts at the top with 0 so up is a number closer to zero
      break;
    case 1:
      p.x++; // right
      break;
    case 2:
      p.y++; // left
      break;
    case 3:
      p.x--; // down
      break;
  }
  
  
  if(p.x >= 8){ // collision with the wall
    collision = true;
    p.x=0;
  }
  else if(p.x < 0){ // collision with the wall
    collision = true;
    p.x=7;
  }
  if(p.y >= 8){ // collision with the wall
    collision = true;
    p.y=0;
  }
  else if(p.y < 0){ // collision with the wall
    collision = true;
    p.y=7;
  }
  if(!ghost && collision == true){ // only restart if there is a collision with the wall and ghost-mode is off
    snakeRestart();
    return;
  }

  if(p.x == apple.x && p.y == apple.y){ // if the new head position is same as apple position
    snakeLength++; // increase lenght of the snake
    appleEaten = true; // the snake at an apple
  }
  
  parts[p_parts].x = p.x; // add new head to the array (x)
  parts[p_parts].y = p.y; // add new head to the array (y)
  p_parts++; // increase array pointer
  if(p_parts >= 64) p_parts = 0; // pointer can't be bigger than 63
}

/**
 * create a new apple (if nessesary)
 */
void makeApple(){
  if(appleEaten){ // only make a new one if the current apple is eaten
    apple.x = random(0,8); // new random position (x)
    apple.y = random(0,8); // new random position (y)

    appleEaten = false; // this apple is not eaten yet
  }
  B.display.pixel(apple.x, apple.y); // display the apple
}

/**
 * game over, restart the game
 */
void snakeRestart(){
  for(int i=7; i>=0; i--){ // decrease the intensity of the screen
    B.display.intensity(i);
    delay(100);
  }
  
  B.display.clear(); // clear screen
  B.display.intensity(8); // set intensity back to default

  delay(300);
  
  showScore(); // show score
  
  snakeStart(); // start a new game
  
  delay(200);
}

/**
 * show the score
 */
void showScore(){
  if(snakeLength > highScore){ // if this score is better than highscore
    highScore = snakeLength; // score is the new highscore

    for(int i = 0; i < 2; i++){ // display score + prize 2 times
      B.display.number(snakeLength); // display score
      delay(1000);
      B.display.image(PRIZE); // display prize
      delay(1000);
    }
    
  }
  else{ // no highscore
    B.display.number(snakeLength); // display score
    delay(2000);
  }
}

