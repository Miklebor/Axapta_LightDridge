/*
  Arduino Yún Bridge example
  This example for the Arduino Yún shows how to use the
  Bridge library to access the digital and analog pins
  on the board through REST calls. It demonstrates how
  you can create your own API when using REST style
  calls through the browser.
  Possible commands created in this shetch:
  "/arduino/digital/13"     -> digitalRead(13)
  "/arduino/digital/13/1"   -> digitalWrite(13, HIGH)
  "/arduino/analog/2/123"   -> analogWrite(2, 123)
  "/arduino/analog/2"       -> analogRead(2)
  "/arduino/mode/13/input"  -> pinMode(13, INPUT)
  "/arduino/mode/13/output" -> pinMode(13, OUTPUT)
  This example code is part of the public domain
  http://www.arduino.cc/en/Tutorial/Bridge
*/

#include <Bridge.h>
#include <BridgeServer.h>
#include <BridgeClient.h>

#define PIN            6
#define NUMPIXELS      16   //How many NeoPixels are attached to the Arduino?
int led_num;        // Указатель номера нужного LED (начиная с нуля)
int br_G = 25;     // яркость по каналам
int br_B = 25;
int br_R = 25;
int delayval = 50; // delay for half a second
// Listen to the default port 5555, the Yún webserver
// will forward there all the HTTP requests you send
BridgeServer server;
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void all_off() {
  for(int i=0; i<NUMPIXELS; i++){    
    pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(10); // Delay for a period of time (in milliseconds).
  }
}  
  
void reset() {
  for(int i=0; i<NUMPIXELS; i++){    
    pixels.setPixelColor(i, pixels.Color(br_R,0,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(10); // Delay for a period of time (in milliseconds).
    all_off();
  }
}

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  led_num = 0;
  reset();
  //all_off();
  pinMode(2, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();  // Bridge startup Listen for incoming connection only from localhost
  // (no one from the external network could connect)
  server.listenOnLocalhost();
  server.begin();
}

void loop() {
  
  BridgeClient client = server.accept(); // Get clients coming from server
  if (client) { // There is a new client?
    process(client); // Process request
    client.stop(); // Close connection and free resources.
  }
  delay(50); // Poll every 50ms
}

void process(BridgeClient client) {
  
  String command = client.readStringUntil('/'); // read the command

   if (command == "red") { // is "digital" command?
    redCommand(client);
  }
   if (command == "blue") { // is "digital" command?
    blueCommand(client);
  }
   if (command == "green") { // is "digital" command?
    greenCommand(client);
  }
//  if (command == "digital") { // is "digital" command?
//    digitalCommand(client);
//  }
  if (command == "analog") {  // is "analog" command?
    analogCommand(client);
  }
  if (command == "mode") {  // is "mode" command?
    modeCommand(client);
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
    pixels.setPixelColor(led_num, pixels.Color(0,0,br_R)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
}


void greenCommand(BridgeClient client) {
  int pin, value;
  pin = client.parseInt();  // Read pin number
  led_num = pin;
  client.println(pin);
  if (client.read() == '/') {  // If the next character is a '/' it means we have an URL with a value like: "/digital/13/1"
    value = client.parseInt();
    client.println(value);
    //digitalWrite(pin, value);
    on_number_green();
    }
 
  else {
    value = digitalRead(pin);
    reset();
    }

  client.print(F("Pin D")); // Send feedback to client
  client.print(pin);
  client.print(F(" set to "));
  client.println(value);

  String key = "D";  // Update datastore key with the current pin value
  key += pin;
  Bridge.put(key, String(value));
}
void redCommand(BridgeClient client) {
  int pin, value;
  pin = client.parseInt();  // Read pin number
  led_num = pin;
  client.println(pin);
  if (client.read() == '/') {  // If the next character is a '/' it means we have an URL with a value like: "/digital/13/1"
    value = client.parseInt();
    client.println(value);
    //digitalWrite(pin, value);
    on_number_red();
    }
 
  else {
    value = digitalRead(pin);
    reset();
    }

  client.print(F("Pin D")); // Send feedback to client
  client.print(pin);
  client.print(F(" set to "));
  client.println(value);

  String key = "D";  // Update datastore key with the current pin value
  key += pin;
  Bridge.put(key, String(value));
}
void blueCommand(BridgeClient client) {
  int pin, value;
  pin = client.parseInt();  // Read pin number
  led_num = pin;
  client.println(pin);
  if (client.read() == '/') {  // If the next character is a '/' it means we have an URL with a value like: "/digital/13/1"
    value = client.parseInt();
    client.println(value);
    //digitalWrite(pin, value);
    on_number_blue();
    }
 
  else {
    value = digitalRead(pin);
    reset();
    }

  client.print(F("Pin D")); // Send feedback to client
  client.print(pin);
  client.print(F(" set to "));
  client.println(value);

  String key = "D";  // Update datastore key with the current pin value
  key += pin;
  Bridge.put(key, String(value));
}

void analogCommand(BridgeClient client) {
  int pin, value;

  pin = client.parseInt();  // Read pin number

  if (client.read() == '/') { // If the next character is a '/' it means we have an URL with a value like: "/analog/5/120"
    // Read value and execute command
    value = client.parseInt();
    analogWrite(pin, value);

    client.print(F("Pin D"));  // Send feedback to client
    client.print(pin);
    client.print(F(" set to analog "));
    client.println(value);

    String key = "D"; // Update datastore key with the current pin value
    key += pin;
    Bridge.put(key, String(value));
  } else {
      value = analogRead(pin);  // Read analog pin
      client.print(F("Pin A"));  // Send feedback to client
      client.print(pin);
      client.print(F(" reads analog "));
      client.println(value);
    
    String key = "A"; // Update datastore key with the current pin value
    key += pin;
    Bridge.put(key, String(value));
  }
}

void modeCommand(BridgeClient client) {
  int pin;

  pin = client.parseInt();  // Read pin number

  if (client.read() != '/') {  // If the next character is not a '/' we have a malformed URL
    client.println(F("error"));
    return;
  }

  String mode = client.readStringUntil('\r');

  if (mode == "input") {
    pinMode(pin, INPUT);
    // Send feedback to client
    client.print(F("Pin D"));
    client.print(pin);
    client.print(F(" configured as INPUT!"));
    return;
  }

  if (mode == "output") {
    pinMode(pin, OUTPUT);
    client.print(F("Pin D")); // Send feedback to client
    client.print(pin);
    client.print(F(" configured as OUTPUT!"));
    return;
  }

  client.print(F("error: invalid mode "));
  client.print(mode);
}

/*

void loop_loop() {
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

*/

