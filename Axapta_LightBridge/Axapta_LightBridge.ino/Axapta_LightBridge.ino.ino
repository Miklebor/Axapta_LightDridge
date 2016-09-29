#include <Adafruit_NeoPixel.h>
#define PIN            6
#define NUMPIXELS      16   //How many NeoPixels are attached to the Arduino?

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int led_num;        // Указатель нужного LED
int br_G = 20;     // яркость по каналам
int br_B = 20;
int br_R = 20;
int delayval = 50; // delay for half a second

void setup() {
  led_num = 0;
  void all_off();
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
  for(int j=0;j<NUMPIXELS;j++){
    led_num = j;
    on_number_green();
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
  for(int j=0;j<NUMPIXELS;j++){
    led_num = j;
    on_number_red();
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
  for(int j=0;j<NUMPIXELS;j++){
    led_num = j;
    on_number_blue();
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
}

void on_number_green() {
    all_off(); // сначала все выключаем
    pixels.setPixelColor(led_num, pixels.Color(0,br_G,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
}
void on_number_red() {
    all_off(); // сначала все выключаем
    pixels.setPixelColor(led_num, pixels.Color(br_R,0,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
}
void on_number_blue() {
    all_off(); // сначала все выключаем
    pixels.setPixelColor(led_num, pixels.Color(0,0,br_B)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
}

void all_off() {
  for(int i=0;i<NUMPIXELS;i++){    
    pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(0); // Delay for a period of time (in milliseconds).
  }
}

