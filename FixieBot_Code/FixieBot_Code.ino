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

int pot1Pin = A3;
int pot2Pin = A2;
int sliderPin = A1;

int pot1Value = 0;
int pot2Value = 0;
int sliderValue = 0;

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

//Power Bar
  display.drawRect(1,44,126,20,WHITE);
  display.fillRect(3,46,122*power/100,16,WHITE);

//text example
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  pot1Value = analogRead(pot1Pin);
  display.print(pot1Value);

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
