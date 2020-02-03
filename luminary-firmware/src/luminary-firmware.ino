/*
 * Project luminary-firmware
 * Description: Firmware for running "Luminary" pseudo-analog clock
 * Author: Kevin Conner
 * Date: 2020JAN31
 */

#include "Particle.h"
#include "neopixel.h"

#define PIXEL_COUNT 60
#define PIXEL_PIN D7
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel pixels(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);	

// particle cloud variables //
int timezone = -8;
int hand_hour_color = 0xff0000;
int hand_minute_color = 0x00ff00;
int hand_second_color = 0x0000ff;

// types
int setTimezone(String command);

// setup() runs once, when the device is first turned on.
void setup() {
  
  // register Particle Cloud variables and functions
  Particle.variable("timezone", timezone);
  Particle.variable("hand_hour_color", hand_hour_color);
  Particle.variable("hand_minute_color", hand_minute_color);
  Particle.variable("hand_second_color", hand_second_color);

  Particle.function("set_timezone", setTimezone);

  pixels.begin();

}

// loop() runs over and over again, as quickly as it can execute.
void loop() { 
  
  Time.zone(timezone);

  pixels.clear();

  int hourHand = ((Time.hour()%12)*5)+int(Time.minute()/12);
  int minuteHand = Time.minute();
  int secondHand = Time.second();
  pixels.setPixelColor(hourHand,255,0,0);
  pixels.setPixelColor(minuteHand,0,255,0);
  pixels.setPixelColor(secondHand,0,0,255);

  // setPixelColorHex(pixels, hourHand, hand_hour_color);
  // setPixelColorHex(pixels, minuteHand, hand_minute_color);
  // setPixelColorHex(pixels, secondHand, hand_second_color);

  pixels.show();

}

int setTimezone(String command){
  if (!isValidNumber(command)) { return -1; }
  timezone = command.toInt();
  return 1;
}

void setHandColors(){

}

void setPixelColorHex(Adafruit_NeoPixel neo, int pixelIndex, int hexColor){

  uint8_t r = (hexColor & 0xff0000 ) >> 16;
  uint8_t g = (hexColor & 0x00ff00 ) >> 8;
  uint8_t b = (hexColor & 0x0000ff );

  neo.setPixelColor(pixelIndex,r,g,b);

boolean isValidNumber(String str){
  for(byte i=0;i<str.length();i++){
    if(isDigit(str.charAt(i))) return true;
  }
   return false;
} 