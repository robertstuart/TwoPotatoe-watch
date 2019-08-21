/*****************************************************************************-
 *  readMain()    Read messages from Teensy 3.6 main processor.
 *****************************************************************************/
void readMain() { 
  const int MAIN_BUFFER_SIZE = 10;
  static char msgStr[MAIN_BUFFER_SIZE];
  static bool isMessageInProgress = false;
  static int msgPtr = 0;
  static int msgCmd = 0;
  
  while (Serial1.available()) {
    byte b = Serial1.read();
    if (b >= 128) {
      msgPtr = 0;
      msgCmd = b;
      isMessageInProgress = true;
    } else {
      if (isMessageInProgress) {
        if (msgPtr >= MAIN_BUFFER_SIZE) {
          isMessageInProgress = false;
        } else if (b == 0) {  // end of message?
          msgStr[msgPtr] = 0;
          doMsg(msgCmd, msgStr, msgPtr);
          isMessageInProgress = false;
        } else {
          msgStr[msgPtr++] = b;
        }
      } else {
        Serial.print("Main serial error: "); Serial.println(b);
      }
    }
  }
}



/*****************************************************************************-
 *  doMsg() Act on messages from Teensy 3.6 main controller.
 *****************************************************************************/
void doMsg(int cmd, char msgStr[], int count) {
  int intVal;

  msgStr[count] = 0; // Just to be sure.

  switch (cmd) {
    case SEND_WATCH:
      lastWatchMs = timeMilliseconds;
      break;
    case SEND_BLINK:
      setBlink((unsigned int) (msgStr[0] - '0'), (unsigned int) (msgStr[1] - '0'));
      break;
    case SEND_BEEP:
      if (sscanf(msgStr, "%d", &intVal) > 0) {
        addScript(intVal);
      }
      break;
    default:
      Serial.print("Illegal message received: "); Serial.println(cmd);
      break;
  }
}



/*****************************************************************************-
 *  sendMaMsg()  Send a message to the main processor.
 *****************************************************************************/
void sendMaMsg(int cmd, int v1, int v2) {
  Serial1.write((byte) cmd);
  Serial1.print(v1);
  Serial1.print(v2);
  Serial1.write((byte) 0);
}
  
void sendMaMsg(int cmd, float val) {
  Serial1.write((byte) cmd); 
  Serial1.print(val); 
  Serial1.write((byte) 0);
}
