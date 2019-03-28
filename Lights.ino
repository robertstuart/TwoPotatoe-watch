
/**************************************************************************.
 *  blink() 
 **************************************************************************/
//void blinkLed() {
//  static int routeCycle = 0; //
//  static int routeOffCount = 0;
//  static unsigned long blinkTrigger = 0L;
//  if (timeMilliseconds > blinkTrigger) {
//    blinkTrigger = timeMilliseconds + 100;  // 10 per second
//
//    // Blink the Blue and Green
//    int b = (patternBlue[blinkPtrBlue++] == 1) ? HIGH : LOW;
//    if (patternBlue[blinkPtrBlue] == END_MARKER) blinkPtrBlue = 0;
//    digitalWrite(BLUE_LED_PIN, b);
//    if (isMotorDisable) b = LOW;
//    digitalWrite(GREEN_LED_PIN, b);
//
//    // Blink the Yellow
//    b = (patternYellow[blinkPtrYellow++] == 1) ? HIGH : LOW;
//    if (patternYellow[blinkPtrYellow] == END_MARKER) blinkPtrYellow = 0;
//    digitalWrite(YELLOW_LED_PIN, b);
//
//    // Blink route number on red
//    if (isLiftDisabled) {
//      digitalWrite(RED_LED_PIN, HIGH);
//    } else {
//      if (++routeOffCount >=5) {
//        routeOffCount = 0;
//        if (routeCycle <= routeTablePtr) {
//          digitalWrite(RED_LED_PIN, HIGH);
//        }
//        routeCycle++;
//        if (routeCycle >= (routeTablePtr + 3)) {
//          routeCycle = 0;
//        }
//      } else if (routeOffCount == 2) {
//        digitalWrite(RED_LED_PIN, LOW);
//      }
//    }
//  }  
//}
//

