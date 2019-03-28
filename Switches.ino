

/**************************************************************************.
 * switches()
 *      Toggle TP_STATE_RUN_READY on yellow switch.  1 sec dead period.
 **************************************************************************/
void switches() {
  static unsigned int gnTimer = 0;
  static boolean gnState = false;
  static boolean oldGnState = false;
  
  static unsigned int reTimer = 0;
  static boolean reState = false;
  static boolean oldReState = false;

  static unsigned int buTimer = 0;
  static boolean buState = false;
  static boolean oldBuState = false;

  static unsigned int yeTimer = 0;
  static boolean yeState = false;
  static boolean oldYeState = false;

  bool b;
  
  // Debounce Green (back switch)
  boolean gn = digitalRead(SW_PIN_GN) == LOW;
  if (gn) gnTimer = timeMilliseconds;
  if ((timeMilliseconds - gnTimer) > 50) gnState = false;
  else gnState = true;
  
  // Debounce Red
  boolean re = digitalRead(SW_PIN_RE) == LOW;
  if (re) reTimer = timeMilliseconds;
  if ((timeMilliseconds - reTimer) > 50) reState = false;
  else reState = true;

  
  // Debounce Blue
  boolean bu = digitalRead(SW_PIN_BU) == LOW;
  if (bu) buTimer = timeMilliseconds;
  if ((timeMilliseconds - buTimer) > 50) buState = false;
  else buState = true;
  
  // Debounce Yellow
  boolean ye = digitalRead(SW_PIN_YE) == LOW;
  if (ye) yeTimer = timeMilliseconds;
  if ((timeMilliseconds - yeTimer) > 50) yeState = false;
  else yeState = true;

  // Red press transition
  if (reState && (!oldReState)) {
    b = digitalRead(LED_PIN_RE) == HIGH;
    digitalWrite(LED_PIN_RE, b ? LOW : HIGH);
    Serial.println("red");
   addScript(MUSIC_FUGUE);
 }

  // Blue press transition. Toggle route enable.
  if (buState && (!oldBuState)) {
    b = digitalRead(LED_PIN_BU) == HIGH;
    digitalWrite(LED_PIN_BU, b ? LOW : HIGH);
    Serial.println("blue");
    addScript(MUSIC_WARBLE);
  }

  // Green press transition.  Start route.
  if (gnState && (!oldGnState)) {
    b = digitalRead(LED_PIN_GN) == HIGH;
    digitalWrite(LED_PIN_GN, b ? LOW : HIGH);
    Serial.println("green");
    addScript(MUSIC_BACH);
  }

  // Yellow press transition
  if (yeState && (!oldYeState)) {
    b = digitalRead(LED_PIN_YE) == HIGH;
    digitalWrite(LED_PIN_YE, b ? LOW : HIGH);
    Serial.println("yellow");
   addScript(MUSIC_FUGUE2);
  }

  oldBuState = buState;
  oldYeState = yeState;
  oldReState = reState;
  oldGnState = gnState; 
}


