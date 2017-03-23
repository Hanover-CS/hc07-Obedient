#include "Arduino.h"
#include <Obedient.h>
#include <QueueArray.h>

#if !defined(SERIAL_PORT_MONITOR)
  #error "Arduino version not supported. Please update your IDE to the latest version."
#endif

#if defined(SERIAL_PORT_USBVIRTUAL)
  // Shield Jumper on HW (for Leonardo and Due)
  #define port SERIAL_PORT_HARDWARE
  #define pcSerial SERIAL_PORT_USBVIRTUAL
#else
  // Shield Jumper on SW (using pins 12/13 or 8/9 as RX/TX)
  #include "SoftwareSerial.h"
  SoftwareSerial port(12, 13);
  #define pcSerial SERIAL_PORT_MONITOR
#endif

#include "EasyVR.h"

EasyVR easyvr(port);

//Groups and Commands
enum Groups {
  GROUP_0 = 0, //trigger
  GROUP_1 = 1, //basic
  GROUP_2 = 2, //direction
  GROUP_3 = 3, //group of numbers
  GROUP_4 = 4, //basicOrAdvanced
  GROUP_5 = 5, //sensor
  GROUP_6 = 6, //list of commands
};

//Trigger command idx's
enum Group0 {
  G0_OBEDIENT = 0,
};

//Basic command idx's
enum Group1 {
  G1_FOWARD = 0,
  G1_BACKWARD = 1,
  G1_LEFTTURN = 2,
  G1_RIGHTTURN = 3,
  G1_BACKLEFT = 4,
  G1_TURNBACKRIGHT = 5,
  G1_STOP = 6,
  G1_MAINMENU = 7,
};

// pick a movement
enum Group2 {
  G2_FOWARD = 0,
  G2_BACKWARD = 1,
  G2_LEFTTURN = 2,
  G2_RIGHTTURN = 3,
  G2_MAINMENU = 4,
};

// pick a number as a parameter
enum Group3 {
   G3_1 = 0,
   G3_2 = 1,
   G3_3 = 2,
   G3_4 = 3,
   G3_5 = 4,
};

//Basic or Advanced?
enum Group4 {
  G4_BASIC = 0,
  G4_ADVANCED = 1,
  G4_SENSOR = 2,
};

// Sensor commands
enum Group5 {
  SENSOR_FOWARD = 0,
  SENSOR_BACKWARD = 1,
  SENSOR_LEFTTURN = 2,
  SENSOR_RIGHTTURN = 3,
  SENSOR_BACKLEFT = 4,
  SENSOR_TURNBACKRIGHT = 5,
  SENSOR_STOP = 6,
  SENSOR_MAINMENU = 7,
};

//List of commands
enum Group6 {
  LIST_FOWARD = 0,
  LIST_BACKWARD = 1,
  LIST_LEFTTURN = 2,
  LIST_RIGHTTURN = 3,
  LIST_BACKLEFT = 4,
  LIST_TURNBACKRIGHT = 5,
  LIST_MAINMENU = 7,
  LIST_GO = 8,
};

// variable group to keep track of the current group within action function
// variable idx to keep track of the commands in each group within subfunctions of action function
// Declares variable id for the direction function here
int8_t group, idx, id;

// Declares obedient
Obedient obedient(10, 11);

void setup() {
  obedient.attachServo();
  // setup PC serial port
  pcSerial.begin(9600);

  // bridge mode?
  int mode = easyvr.bridgeRequested(pcSerial);
  switch (mode)
  {
  case EasyVR::BRIDGE_NONE:
    // setup EasyVR serial port
    port.begin(9600);
    // run normally
    pcSerial.println(F("---"));
    pcSerial.println(F("Bridge not started!"));
    break;
    
  case EasyVR::BRIDGE_NORMAL:
    // setup EasyVR serial port (low speed)
    port.begin(9600);
    // soft-connect the two serial ports (PC and EasyVR)
    easyvr.bridgeLoop(pcSerial);
    // resume normally if aborted
    pcSerial.println(F("---"));
    pcSerial.println(F("Bridge connection aborted!"));
    break;
    
  case EasyVR::BRIDGE_BOOT:
    // setup EasyVR serial port (high speed)
    port.begin(115200);
    // soft-connect the two serial ports (PC and EasyVR)
    easyvr.bridgeLoop(pcSerial);
    // resume normally if aborted
    pcSerial.println(F("---"));
    pcSerial.println(F("Bridge connection aborted!"));
    break;
  }

  while (!easyvr.detect())
  {
    Serial.println("EasyVR not detected!");
    delay(1000);
  }

  easyvr.setPinOutput(EasyVR::IO1, LOW);
  Serial.println("EasyVR detected!");
  easyvr.setTimeout(5);
  easyvr.setLanguage(0);

  group = EasyVR::TRIGGER; //<-- start group (customize)
}

void action();

void loop() {
  if (easyvr.getID() < EasyVR::EASYVR3)
    easyvr.setPinOutput(EasyVR::IO1, HIGH); // LED on (listening)

  Serial.print("Say a command in Group ");
  Serial.println(group);
  easyvr.recognizeCommand(group);

  do {
    // can do some processing while waiting for a spoken command
  }
  while (!easyvr.hasFinished());
  
  if (easyvr.getID() < EasyVR::EASYVR3)
    easyvr.setPinOutput(EasyVR::IO1, LOW); // LED off

  idx = easyvr.getWord();
  if (idx >= 0) {
    // built-in trigger (ROBOT)
    // group = GROUP_X; <-- jump to another group X
    return;
  }
  idx = easyvr.getCommand();
  if (idx >= 0) {
    // print debug message
    uint8_t train = 0;
    char name[32];
    Serial.print("Command: ");
    Serial.print(idx);
    if (easyvr.dumpCommand(group, idx, name, train))
    {
      Serial.print(" = ");
      Serial.println(name);
    }
    else
      Serial.println();
      
    // perform some action
    action();
  }
  // errors or timeout or not recognized words
   else {
      if (easyvr.isTimeout())
         Serial.println("Timed out, try again...");
      int16_t err = easyvr.getError();
      if (err >= 0) {
         Serial.print("Error ");
         Serial.println(err, HEX);
   }
  }
}


