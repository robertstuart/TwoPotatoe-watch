const byte END_MARKER = 0xFF;
byte blinkOff[] = {0,END_MARKER};                   // Off
byte blinkSF[] = {1,0,0,0,0,0,0,0,END_MARKER} ;     // Slow flash
byte blinkFF[] = {1,0,END_MARKER};                  // Fast flash
byte blinkSB[] = {1,1,1,1,0,0,0,0,END_MARKER};      // Slow blink
byte blinkOn[] = {1,END_MARKER};                    // On
byte blink20[] = {1,1,0,0,0,0,0,0,0,0,END_MARKER};  // 20%
byte blink40[] = {1,1,1,1,0,0,0,0,0,0,END_MARKER};  // 40%
byte blink60[] = {1,1,1,1,1,1,0,0,0,0,END_MARKER};  // 60%
byte blink80[] = {1,1,1,1,1,1,1,1,0,0,END_MARKER};  // 80%


byte *blinkArray[] = {
  blinkOff,     // BLINK_OFF
  blinkSF,      // BLINK_SF
  blinkFF,      // BLINK_FF
  blinkSB,      // BLINK_SB
  blinkOn,      // BLINK_ON
  blink20,      // BLINK_20
  blink40,      // BLINK_40
  blink60,      // BLINK_60
  blink80,      // BLINK_80
};

byte * patternGn = blinkOn;;
byte * patternRe = blinkOn;
byte * patternBu = blinkOn;
byte * patternYe = blinkOn;
int blinkPtrGn = 0;
int blinkPtrRe = 0;
int blinkPtrBu = 0;
int blinkPtrYe = 0;

/*****************************************************************************-
 *   blinkLed()
 *****************************************************************************/
void blinkLed() {
  static unsigned long blinkTrigger = 0L;
  int b = 0;
  if (timeMilliseconds > blinkTrigger) {
    blinkTrigger = timeMilliseconds + 100;  // 10 per second

    // Blink Green
    b = (patternGn[blinkPtrGn++] == 1) ? HIGH : LOW;
    if (patternGn[blinkPtrGn] == END_MARKER) blinkPtrGn = 0;
    digitalWrite(LED_PIN_GN, b);

     // Blink Red
    b = (patternRe[blinkPtrRe++] == 1) ? HIGH : LOW;
    if (patternRe[blinkPtrRe] == END_MARKER) blinkPtrRe = 0;
    digitalWrite(LED_PIN_RE, b);
   
    // Blink Blue
    b = (patternBu[blinkPtrBu++] == 1) ? HIGH : LOW;
    if (patternBu[blinkPtrBu] == END_MARKER) blinkPtrBu = 0;
    digitalWrite(LED_PIN_BU, b);

    // Blink Yellow
    b = (patternYe[blinkPtrYe++] == 1) ? HIGH : LOW;
    if (patternYe[blinkPtrYe] == END_MARKER) blinkPtrYe = 0;
    digitalWrite(LED_PIN_YE, b);
  }
}



/*****************************************************************************-
 *   setBlink
 *****************************************************************************/
void setBlink(unsigned int color, unsigned int pattern) {
  if (pattern > (sizeof(blinkArray) / sizeof(byte*))) return;
  byte *p = blinkArray[pattern];
  switch (color) {
    case 0:
      if (p != patternGn) {
        patternGn = p;
        blinkPtrGn = 0;
      }
      break;
    case 1:
      if (p != patternRe) {
        patternRe = p;
        blinkPtrRe = 0;
      }
      break;
    case 2:
      if (p != patternBu) {
        patternBu = p;
        blinkPtrBu = 0;
      }
      break;
    case 3:
      if (p != patternYe) {
        patternYe = p;
        blinkPtrYe = 0;
        isRunning = (pattern == BLINK_ON) ? true : false;
      }
      break; 
  }
}
