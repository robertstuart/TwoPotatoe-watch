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

  // Green press transition.
  if (gnState && (!oldGnState)) {
    sendMaMsg(RCV_SWITCH,LED_SW_GN, 1);
    addScript(T_BUTTONB);
  }
  
  // Red press transition
  if (reState && (!oldReState)) {
    sendMaMsg(RCV_SWITCH,LED_SW_RE, 1);
    addScript(T_BROWNOUT);
  }

  // Blue press transition.
  if (buState && (!oldBuState)) {
    sendMaMsg(RCV_SWITCH,LED_SW_BU, 1);
    addScript(T_ALARM);
  }

  // Yellow press transition
  if (yeState && (!oldYeState)) {
    sendMaMsg(RCV_SWITCH,LED_SW_YE, 1);
//   addScript(T_FUGUE);
  }

  oldBuState = buState;
  oldYeState = yeState;
  oldReState = reState;
  oldGnState = gnState; 
}
