/*****************************************************************************-
                       TwoPotatoe-watch
                 Teensy 3.2 running at 72 MHz
 *****************************************************************************/

#include "Ma_Watch.h"

const int LED_PIN =       13;  // LED connected to digital pin 13
const int LED_PIN_GN =    19;
const int LED_PIN_RE =    20;
const int LED_PIN_BU =    21;
const int LED_PIN_YE =    22;

const int SW_PIN_GN =      3;   // Green switch
const int SW_PIN_RE =      4;   // Red switch
const int SW_PIN_BU =      5;   // Blue switch
const int SW_PIN_YE =      6;   // Yellow switch

const int SLEEP_PIN =      17;
const int SPEAKER_PIN =    18;   //
const int BATT_PIN =       A0;   // pin14

unsigned int timeMilliseconds = 0;
unsigned int lastWatchMs = 0;
boolean isMotorOn = false;
char message[100] = "";
float battVolt = 0.0;
bool isRunning = false;



/*****************************************************************************-
 * setup()
 *****************************************************************************/
void setup() {
  Serial.begin(115200);          // debug
  Serial1.begin(115200);         // Teensy 3.6 Main processor 

  pinMode(LED_PIN, OUTPUT);      // board LED
  pinMode(LED_PIN_GN, OUTPUT);
  pinMode(LED_PIN_RE, OUTPUT);
  pinMode(LED_PIN_BU, OUTPUT);
  pinMode(LED_PIN_YE, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  pinMode(SLEEP_PIN, OUTPUT);
  digitalWrite(SLEEP_PIN, HIGH);  // High is motor off.

  pinMode(BATT_PIN, INPUT);
  analogReference(INTERNAL);

  pinMode(SW_PIN_GN, INPUT_PULLUP);
  pinMode(SW_PIN_RE, INPUT_PULLUP);
  pinMode(SW_PIN_BU, INPUT_PULLUP);
  pinMode(SW_PIN_YE, INPUT_PULLUP);

  timeMilliseconds = millis();
  delay(2000);
  battery();
  Serial.println(battVolt);
  addScript(T_UP1);
  lastWatchMs = timeMilliseconds;
  isMotorOn = false;
  digitalWrite(SLEEP_PIN, HIGH);     // Turn motor off.
}



/*****************************************************************************-
 * loop()
 *****************************************************************************/
void loop() {
  timeMilliseconds = millis();
  readMain();  // Get message from Teensy 3.6 Main processor
  tune();
  switches();
  blink13();
  blinkLed();
  battery();
  checkWatch();
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
  static const float minV = 3.5 * 6;
  static unsigned long batteryTrigger = 0L;
  static const float fullV = ((4.2 * 6.0) - minV);
  if (timeMilliseconds > batteryTrigger) {
    batteryTrigger = timeMilliseconds + 1000;  // 1 per second
    battVolt = ((float) analogRead(BATT_PIN)) * .0602;

    if      (battVolt < 21.00)   setBlink(LED_SW_GN, BLINK_OFF);
    else if (battVolt < 22.08)   setBlink(LED_SW_GN, BLINK_20);
    else if (battVolt < 22.68)   setBlink(LED_SW_GN, BLINK_40);
    else if (battVolt < 23.10)   setBlink(LED_SW_GN, BLINK_60);
    else if (battVolt < 23.95)   setBlink(LED_SW_GN, BLINK_80);
    else                         setBlink(LED_SW_GN, BLINK_ON);

    if (!isRunning) {
      if ((battVolt > 6.0) && (battVolt < 21.0))     addScript(T_ALARM);
    }
    sendMaMsg(RCV_BATT, battVolt);
    Serial.println(battVolt);
  }
}



/*****************************************************************************-
 * checkWatch()  If we haven't received a WATCH message in ?? milliseconds,
 *               the imu-controlled timing loop on the main processor isn't
 *               working: turn off the motors.
 *****************************************************************************/
void checkWatch() {
  if ((lastWatchMs + 20) > timeMilliseconds) {  // Recent WATCH message?
    if (!isMotorOn) {
      digitalWrite(SLEEP_PIN, LOW);  // Turn motor on.
      isMotorOn = true;
    }
  } else if (isMotorOn) {
    digitalWrite(SLEEP_PIN, HIGH);  // Turn motor off.
    isMotorOn = false;
  }
}
