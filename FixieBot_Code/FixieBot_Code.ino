/* 
 *  GGJ 2020
 *  by: Br
 * 
 * Inspired by the Tamaguino project by Alojz Jakob 
 * <http://jakobdesign.com>
 * 
 */


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> 
/*make sure to edit the ssd1306 library config to specify 
a 128x64 px screen
*/

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

const int encoderTurnPin = 9;
const int encoderPressPin = 8;

int referenceVoltagePin = A0;
int pot1Pin = A3;
int pot2Pin = A2;
int sliderPin = A1;

int referenceVoltageValue = 0;
int sliderValue = 0;
int pot1Value = 0;
int pot2Value = 0;


int sliderTarget = 100; //target in pixels from 1-119
int pot1Target = 1;
int pot2Target = 50;


const int sound = 6;
int encoderTurn = 2;

float power = 0;


void setup() {
  // put your setup code here, to run once:
//splash tone

  /*pinMode(sound, OUTPUT);
  
  tone(sound,500,200);
  delay(200);
  tone(sound,1000,200);
  delay(400);
  tone(sound,700,200);
  delay(200);
  tone(sound,1100,200);
*/



  pinMode(13,OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  
//Encoder Setup
  // make the pushbutton's pin an input:
  pinMode(encoderTurn, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderTurn), turn, RISING);
}



void loop() {

  
  // put your main code here, to run repeatedly:
  //display.clearDisplay();
  //display.setCursor(0,0);
  //display.drawRect(10,10,10,10,SSD1306_WHITE);
  //display.fillRect(1,1,display.width()-2,27,BLACK);
  //delay(1000);
  //display.display();


//Display Loop
  display.clearDisplay();
  
//Bars mini game
display.drawRect(0,0,128,64,WHITE); //Screen Frame

//Get values from pots
pot1Value = analogRead(pot1Pin);
  delay(10);// this delay is to help the ADC differentiate the 3 signals
  pot1Value = analogRead(pot1Pin);
  
  pot2Value = analogRead(pot2Pin);
  delay(10);
  pot2Value = analogRead(pot2Pin);
  
  sliderValue = analogRead(sliderPin);
  delay(10);
  sliderValue = analogRead(sliderPin);

  referenceVoltageValue = analogRead(referenceVoltagePin);
  delay(10);
  referenceVoltageValue = analogRead(referenceVoltagePin);

//the balance lines
display.drawLine(4,20,123,20,WHITE); 
display.drawLine(4,37,123,37,WHITE);
display.drawLine(4,54,123,54,WHITE);

//the target cursors
display.drawRect((121-2)/100*sliderTarget+2,15,5,11,WHITE);
display.drawRect((121-2)/100*pot1Target+2,32,5,11,WHITE);
display.drawRect((121-2)/100*pot2Target+2,49,5,11,WHITE);

int sliderPixel = (123-4)*(sliderValue/(float)referenceVoltageValue);
int pot1Pixel = (123-4)*(pot1Value/(float)referenceVoltageValue);
int pot2Pixel = (123-4)*(pot2Value/(float)referenceVoltageValue);


//Current Values
display.drawLine(sliderPixel+4,17,sliderPixel+4,23,WHITE);
display.drawLine(pot1Pixel+4,34,pot1Pixel+4,40,WHITE);
display.drawLine(pot2Pixel+4,51,pot2Pixel+4,57,WHITE);

//Power Bar
  //display.drawRect(1,44,126,20,WHITE);
  //display.fillRect(3,46,122*power/100,16,WHITE);

//text example
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(4, 4);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  
  

/*
  Print current values
  display.print(F("Balance the scales"));
  display.print(pot1Value);
  display.print(",");
  display.print(pot2Value);
  display.print(",");
  display.print(sliderValue);
  display.print(",");
  display.print(referenceVoltageValue);
*/


  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(1);
  if (power > 0) {
  power = power - 0.05;
  }
}

void turn() {
  if (power < 100) {
  power = power + 0.2;
  }
}

void drawBar(float value){
  display.fillRect(72,19,48*value/100,3,WHITE);
}
