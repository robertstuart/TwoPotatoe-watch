/*****************************************************************************-
 *                     TwoPotatoe-watch
 *               Teensy 3.2 running at 72 MHz
 *****************************************************************************/

#include "Watch.h"

const int LED_PIN =       13;  // LED connected to digital pin 13
const int LED_PIN_GN =    19;
const int LED_PIN_RE =    20;
const int LED_PIN_BU =    21;
const int LED_PIN_YE =    22;

const int SW_PIN_GN =      3;   // Green switch
const int SW_PIN_RE =      4;   // Red switch
const int SW_PIN_BU =      5;   // Blue switch
const int SW_PIN_YE =      6;   // Yellow switch

const int SPEAKER_PIN =    18;   // 
const int BATT_PIN =       A0;   // pin14

unsigned int timeMilliseconds = 0;
char message[100] = "";
float battVolt = 0.0; 



/*****************************************************************************-
 * setup()
 *****************************************************************************/
void setup() {
  Serial.begin(115200);          // debug 
  Serial1.begin(115200);         // Teensy 3.6
 
  pinMode(LED_PIN,OUTPUT);  // Status LED, also blue LED
  pinMode(LED_PIN_GN,OUTPUT);
  pinMode(LED_PIN_RE,OUTPUT);
  pinMode(LED_PIN_BU,OUTPUT);
  pinMode(LED_PIN_YE, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  
  pinMode(BATT_PIN, INPUT);
  
  pinMode(SW_PIN_GN, INPUT_PULLUP);
  pinMode(SW_PIN_RE, INPUT_PULLUP);
  pinMode(SW_PIN_BU, INPUT_PULLUP);
  pinMode(SW_PIN_YE, INPUT_PULLUP);

  timeMilliseconds = millis();
  delay(2000);
  battery();
  Serial.println(battVolt);
  addScript(MUSIC_UP);
}



/*****************************************************************************-
 * loop()
 *****************************************************************************/
void loop() {
  timeMilliseconds = millis();
  readMain();  // Get message from Teensy 3.6 Main processor
  music();
  switches();
  blink13();
  blinkLed();
  battery();
}



/*****************************************************************************-
 * blink13()
 *****************************************************************************/
void blink13() {
  static unsigned long blinkTrigger = 0;
  static bool toggle = false;
  if (timeMilliseconds > blinkTrigger) {
    blinkTrigger = timeMilliseconds + 100;
    toggle = !toggle;
    digitalWrite(LED_PIN, toggle ? HIGH : LOW);
//    sendMaMsg(RCV_SWITCH, LED_SW_YE, 1);  
  }
}



/*****************************************************************************-
 * battery()
 *****************************************************************************/
void battery() {
  static unsigned long batteryTrigger = 0L;
  if (timeMilliseconds > batteryTrigger) {
    batteryTrigger = timeMilliseconds + 1000;  // 1 per second
    battVolt = ((float) analogRead(BATT_PIN)) * .0602;
//    Serial.print(analogRead(BATT_PIN)); Serial.print(" "); Serial.println(battVolt);
  }
}



/*****************************************************************************-
 * dprint???()  Convenience functions for debug printouts.
 *****************************************************************************/
void dPrint(String s, int i) {
  Serial.print(s);
  Serial.print(i);
}
void dPrintln(String s, int i) {
  Serial.print(s);
  Serial.println(i);
}
void dPrint(String s, float f, int precision) {
  Serial.print(s);
  Serial.print(f, precision);
}
void dPrintln(String s, float f, int precision) {
  Serial.print(s);
  Serial.println(f, precision);
}
void dPrint(String s1, char* s2) {
  Serial.print(s1);
  Serial.print("\"");
  Serial.print(s2);
  Serial.print("\"");
}
void dPrintln(String s1, char* s2) {
  Serial.print(s1);
  Serial.print("\"");
  Serial.print(s2);
  Serial.println("\"");
}
