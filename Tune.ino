/******************************************************************************
 *  Tune     -  Adapted from Pololu 32u4 Arduino library
 *              See https://github.com/pololu/balboa-32u4-arduino-library/blob/master/PololuBuzzer.cpp
 *              for the script syntax.
 *****************************************************************************/
// The notes are specified by the characters C, D, E, F, G, A, and
// B, and they are played by default as "quarter notes" with a
// length of 500 ms.  This corresponds to a tempo of 120
// beats/min.  Other durations can be specified by putting a number
// immediately after the note.  For example, C8 specifies C played as an
// eighth note, with half the duration of a quarter note. The special
// note R plays a rest (no sound).
//
// Various control characters alter the sound:
//   '>' plays the next note one octave higher
//
//   '<' plays the next note one octave lower
//
//   '+' or '#' after a note raises any note one half-step
//
//   '-' after a note lowers any note one half-step
//
//   '.' after a note "dots" it, increasing the length by
//       50%.  Each additional dot adds half as much as the
//       previous dot, so that "A.." is 1.75 times the length of
//       "A".
//
//   'O' followed by a number sets the octave (default: O4).
//
//   'T' followed by a number sets the tempo (default: T120).
//
//   'L' followed by a number sets the default note duration to
//       the type specified by the number: 4 for quarter notes, 8
//       for eighth notes, 16 for sixteenth notes, etc.
//       (default: L4)
//
//   'V' followed by a number from 0-15 sets the music volume.
//       (default: V15)
//
//   'MS' sets all subsequent notes to play staccato - each note is played
//       for 1/2 of its allotted time, followed by an equal period
//       of silence.
//
//   'ML' sets all subsequent notes to play legato - each note is played
//       for its full length.  This is the default setting.
//
//   '!' resets all persistent settings to their defaults.
//
// The following plays a c major scale up and back down:
//   play("L16 V8 cdefgab>cbagfedc");
//
// Here is an example from Bach:
//   play("T240 L8 a gafaeada c+adaeafa <aa<bac#ada c#adaeaf4");


struct tuneId {
  String name;
  char* script;
};
 

char tuneRhapsody[] = "O6 T40 L16 d#<b<f#<d#<f#<bd#f#"
  "T80 c#<b-<f#<c#<f#<b-c#8"
  "T180 d#b<f#d#f#>bd#f#c#b-<f#c#f#>b-c#8 c>c#<c#>c#<b>c#<c#>c#c>c#<c#>c#<b>c#<c#>c#"
  "c>c#<c#>c#<b->c#<c#>c#c>c#<c#>c#<b->c#<c#>c#"
  "c>c#<c#>c#f>c#<c#>c#c>c#<c#>c#f>c#<c#>c#"
  "c>c#<c#>c#f#>c#<c#>c#c>c#<c#>c#f#>c#<c#>c#d#bb-bd#bf#d#c#b-ab-c#b-f#d#";
  
// A longer song and its title.
char tuneFugue[] =
  "! T120O5L16agafaea dac+adaea fa<aa<bac#a dac#adaea f"
  "O6dcd<b-d<ad<g d<f+d<gd<ad<b- d<dd<ed<f+d<g d<f+d<gd<ad"
  "L8MS<b-d<b-d MLe-<ge-<g MSc<ac<a MLd<fd<f O5MSb-gb-g"
  "ML>c#e>c#e MS afaf ML gc#gc# MS fdfd ML e<b-e<b-"
  "O6L16ragafaea dac#adaea fa<aa<bac#a dac#adaea faeadaca"
  "<b-acadg<b-g egdgcg<b-g <ag<b-gcf<af dfcf<b-f<af"
  "<gf<af<b-e<ge c#e<b-e<ae<ge <fe<ge<ad<fd"
  "O5e>ee>ef>df>d b->c#b->c#a>df>d e>ee>ef>df>d"
  "e>d>c#>db>d>c#b >c#agaegfe fO6dc#dfdc#<b c#4";

char tuneUp1[] = "!T240 L8 r>c>f";
char tuneUp2[] = "!T240 L8 r>>c>>f";
char tuneUp3[] = "T240 L8 cfdgeafbg>c";
char tuneDn[] = "!T240 L8 r>f>c";
char tuneWarble[] = "!T100 L8 efefefefefef";
char tuneBach[] = "!T240 L8 a gafaeada c+adaeafa <aa<bac#ada c#adaeaf4";
char tuneFugue2[] = "!T240 L8 agafaea dac+adaea fa<aa<bac#a dac#adaea f4";
char tuneScale[] = "!L16 V8 cdefgab>cbagfedc";
char tuneBrownout[] = "<c8";
char tuneWelcome[] = ">g32>>c32";
char tuneThankYou[] = ">>c32>g32";
char tuneButtonA[] = "!c32";
char tuneButtonB[] = "!e32";
char tuneButtonC[] = "!g32";  
char tuneAlarm[] = "!T240 L8 O05 cdcd";

tuneId tuneList[] = {
  {"Rhapsody", tuneRhapsody},
  {"Fugue", tuneFugue},
  {"Beep Up 1", tuneUp1},
  {"Beep Up 2", tuneUp2},
  {"Beep Up 3", tuneUp3},
  {"Down", tuneDn},
  {"Warble", tuneWarble},
  {"Bach", tuneBach},
  {"Fuge 2", tuneFugue2},
  {"Scale", tuneScale},
  {"Brownout", tuneBrownout},
  {"Welcome", tuneWelcome},
  {"Thank You", tuneThankYou},
  {"Button A", tuneButtonA},
  {"Button B", tuneButtonB},
  {"Button C", tuneButtonC},
  {"Alarm", tuneAlarm}
};

//char *scriptArray[] = {
//  musicUp,
//  musicUp2,
//  musicUp3,
//  musicpWarble,
//  musicFugue2,
//  musicBach,
//  musicFugue,
//  musicScale,
//  musicDn,
//  beepBrownout,
//  beepButtonA,
//  beepButtonB,
//  musicAlarm
//};
const int TUNE_LIST_SIZE = sizeof(tuneList) / sizeof(tuneId);

const int MUSIC_QUEUE_SIZE = 100;
unsigned int musicQueue[MUSIC_QUEUE_SIZE];
unsigned int musicQueuePtr = 0;
unsigned int musicQueueEnd = 0;  // Always points to the one after the last.
unsigned long musicTrigger = 0;  // zero indicates no script being played.
char *scriptPtr = 0;

/******************************************************************************
    music() - Polled
                Plays the next note if it is running a script.
                Sets up the next script if the script ends.
 *****************************************************************************/
void tune() {
  if (musicQueuePtr != musicQueueEnd) {
    if (musicTrigger == 0) {  // Indicates end of last script
      int q = musicQueue[musicQueuePtr];
      scriptPtr = tuneList[q].script;
      musicTrigger = 1;  // Causes script to start.
    }
    if (timeMilliseconds > musicTrigger) {
      musicTrigger = 0; // Set so that has to be unset.
      nextNote();
    }
  }
}



/******************************************************************************
    addScript() Adds a script to the queue
 *****************************************************************************/
void addScript(unsigned int script) {
  if (script >= TUNE_LIST_SIZE) return; // Error
  if ((musicQueueEnd + 1) % TUNE_LIST_SIZE == musicQueuePtr) return; // full?
  musicQueue[musicQueueEnd] = script;
  musicQueueEnd++;
  musicQueueEnd = musicQueueEnd % TUNE_LIST_SIZE;
}



/******************************************************************************
    nextNote() Returns false if the last note in a script has been played.
 *****************************************************************************/
void nextNote() {
  // music settings and defaults
  static unsigned char octave = 4;                 // the current octave
  static unsigned int wholeNoteDuration = 2000;  // the duration of a whole note
  static unsigned int noteType = 4;               // 4 for quarter, etc
  static unsigned int duration = wholeNoteDuration / noteType;   // duration in ms
  //static unsigned int volume = 15;                 // the note volume
  static bool staccato = false;               // true if playing staccato
  static unsigned int staccatoRestDuration = 0;  // duration of a staccato rest,

  int note = 0;  // halftones with zero as lowest C
  int octaveInc = 0;
  int tmpDuration = duration;
  int tmpInt = 0;
  bool isNote = false;
  bool rest = false;
  char currentScriptChar = 0;

  // Statccato, rest part
  if (staccato && staccatoRestDuration) {
    noTone(SPEAKER_PIN);
    musicTrigger = staccatoRestDuration + timeMilliseconds;
    staccatoRestDuration = 0;
    return;
  }

  do {
    currentScriptChar = getNextScriptChar();  
    scriptPtr++;
    switch (currentScriptChar) {
      case 0:  // End of script. 
        noTone(SPEAKER_PIN);
        musicQueuePtr++;
        musicQueuePtr = musicQueuePtr % TUNE_LIST_SIZE;
        musicTrigger = 0;
        return;
      case '<': // octave lower
        octaveInc--;
        break;
      case '>':
        octaveInc++;
        break;
      case 'c':
        note = 0;
        isNote = true;
        break;
      case 'd':
        note = 2;
        isNote = true;
        break;
      case 'e':
        note = 4;
        isNote = true;
        break;
      case 'f':
        note = 5;
        isNote = true;
        break;
      case 'g':
        note = 7;
        isNote = true;
        break;
      case 'a':
        isNote = true;
        note = 9;
        break;
      case 'b':
        isNote = true;
        note = 11;
        break;
      case 'l':
        noteType = getNumber();
        duration = wholeNoteDuration / noteType;
        break;
      case 'm':  // Stacato or legato
        if (getNextScriptChar() == 'l') {
          staccato = false;
        } else {
          staccato = true;
          staccatoRestDuration = 0;
        }
       scriptPtr++;
       break;
      case 'o':  // change octave permanently.
        tmpInt = getNumber();
        if (tmpInt < 10) octave = tmpInt;
        break;
      case 'r':  // rest
        rest = true;
        isNote = true;
      break;
      case 't':   // tempo, this is for a quarter note only, fixed
        wholeNoteDuration = (1000 * 4 * 60) / getNumber();
        duration = wholeNoteDuration / noteType;
        break;
      case 'v':   // volume (noop)
        getNumber();
        break;
      case '!':
        octave = 4;
        wholeNoteDuration = 2000;
        noteType = 4;
        // volume = 15;
        staccato = false;
        duration = wholeNoteDuration / noteType;
        break;

      default: //  all errors
        musicQueuePtr++;
        musicQueuePtr %=  MUSIC_QUEUE_SIZE;
    }

    // Have note. Read note modifiers.
     currentScriptChar = getNextScriptChar();

    // Sharps
    while (currentScriptChar == '+' || currentScriptChar == '#') {
      scriptPtr++;
      currentScriptChar = getNextScriptChar();
      note ++;
    }

    // Flats
    while (currentScriptChar == '-') {
      scriptPtr++;
      currentScriptChar = getNextScriptChar();
      note --;
    }

    // Duration (just this note)
    // If the input is 'c16', make it a 16th note, etc.
    if (currentScriptChar >= '0' && currentScriptChar <= '9') {
      tmpDuration = wholeNoteDuration / getNumber();
    }

    // Dotted notes
    // The first dot adds 50%, and each
    // additional dot adds 50% of the previous dot.
    int dot_add = tmpDuration / 2;
    while (currentScriptChar == '.') {
      scriptPtr ++;
      currentScriptChar = getNextScriptChar();
      tmpDuration += dot_add;
      dot_add /= 2;
    }

    if (staccato) {
      staccatoRestDuration = tmpDuration / 2;
      tmpDuration -= staccatoRestDuration;
    }
  } while (isNote == false);

  note = note + ((octave + octaveInc) * 12);
  // Now we have the note & timing.
  int hz = (int) (16.351599D * pow(2.0D, ((double) note) / 12.0D));
  if (rest) noTone (SPEAKER_PIN);
  else tone(SPEAKER_PIN, hz);
  musicTrigger = timeMilliseconds + tmpDuration;
}



/******************************************************************************
    getNextScriptChar()
            Gets the current character, converting to lower-case and skipping
            spaces.  For any spaces, this automatically increments sequence!
 *****************************************************************************/
char getNextScriptChar() {
  char c = 0;

  while (true) {
    c = tolower(*scriptPtr);
    if (c != ' ') break;
    scriptPtr++;
  }
  return c;
}



/******************************************************************************
    getNumber()
             Returns the numerical argument specified at buzzerSequence[0] and
             increments sequence to point to the character immediately after the
             argument.
*****************************************************************************/
unsigned int getNumber() {
  unsigned int arg = 0;
  char c = getNextScriptChar();

  // read all digits, one at a time
  while (c >= '0' && c <= '9') {
    arg *= 10;
    arg += c - '0';
    scriptPtr++;
    c = getNextScriptChar();
  }

  return arg;
}
