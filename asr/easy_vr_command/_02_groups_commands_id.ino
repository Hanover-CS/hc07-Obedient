/*
 * This is the group and command ids.
 * Since each time eavyvr recognize a word, it will tranform that word into a integer that we can use to direct our Obedient
 * This module will holds all the constant number that represents for each word in the command library.
 */
//Groups and Commands
enum Groups {
  GROUP_0 = 0, //trigger
  GROUP_1 = 1, //Basic group
  GROUP_2 = 2, //Advanced commands group
  GROUP_3 = 3, //group of numbers
  GROUP_4 = 4, //MainMenu
  GROUP_5 = 5, //Sensor group
  GROUP_6 = 6, //List group
  GROUP_7 = 7, //Units group, Metric or Time
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

// pick a movement in Advanced group
enum Group2 {
  G2_FOWARD = 0,
  G2_BACKWARD = 1,
  G2_LEFTTURN = 2,
  G2_RIGHTTURN = 3,
  G2_PICKUNIT = 4,
  G2_MAINMENU = 5,
};

// pick a number as a parameter
enum Group3 {
   G3_1 = 0,
   G3_2 = 1,
   G3_3 = 2,
   G3_4 = 3,
   G3_5 = 4,
};

//MainMenu
enum Group4 {
  G4_BASIC = 0,
  G4_ADVANCED = 1,
  G4_SENSOR = 2,
  G4_LIST = 3,
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
  SENSOR_SPEEDUP = 9,
  SENSOR_SLOWDOWN = 10,
};

//List Group
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

//Unit group
enum Group7 {
  UNIT_SECOND = 0,
  UNIT_INCH = 1,
};
