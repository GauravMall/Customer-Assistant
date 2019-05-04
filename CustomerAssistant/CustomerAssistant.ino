#include "Adafruit_GFX.h"
#include "MCUFRIEND_kbv.h"

#include "Fonts/FreeSans9pt7b.h" // when you want other fonts
#include "Fonts/FreeSans12pt7b.h" // when you want other fonts
#include "Fonts/FreeSerif12pt7b.h" // when you want other fonts
#include "FreeDefaultFonts.h" // when you want other fonts

//Colors
#define BLACK 0x0000
#define LIGHTGREY 0xC618
#define DARKGREY 0x7BEF
#define BLUE 0x001F
#define GREEN 0x07E0
#define RED 0xF800
#define WHITE 0xFFFF
#define ORANGE 0xFD20

//Motor Definitions
#define MotorForward 35
#define MotorBack 33
#define MotorRight 32
#define MotorLeft 34

//Sensor Pins
#define trig_pin_forward 37 
#define echo_pin_forward 36 

#define trig_pin_top 49
#define echo_pin_top 48

#define trig_pin_right 43
#define echo_pin_right 42

#define trig_pin_left 45
#define echo_pin_left 44

#define trig_pin_backTop 41
#define echo_pin_backTop 40

#define trig_pin_backBottom 39
#define echo_pin_backBottom 38

#define trig_pin_backRight 51
#define echo_pin_backRight 50

#define trig_pin_backLeft 47
#define echo_pin_backLeft 46

#define PI 3.1415926535897932384626433832795


MCUFRIEND_kbv tft(A3, A2, A1, A0, A4);

int screenWidth;
int screenHeight;

boolean isNavigating;
int _time; // Tells us if this is the first time the robot got started, or not, so we can determine to show or not the welcome screen.
String destination;

//Detection Variables
boolean detected;
int forwardDistance;
int forwardDistanceTop;

//The map
String tokens[] = {"0",
                   "0",
                   "13",
                   "0",
                   "6.5",
                   "0",
                   "Nothing",
                   "13",
                   "0",
                   "13",
                   "28",
                   "13",
                   "14",
                   "library",
                  };

//Custom Objects

#include "LoadingAnimation.h"
#include "Eyes.h"
#include "Robot.h"

LoadingAnimation loadingAnimation(0, 0);
Eyes eyesAnimation(0, 0);
Robot robotPosition(0, 0, 10, 25);

#include "Map.h"
Map robotMap(0);

void setup() {
  //Serial Initialization
  Serial.begin(9600);
  Serial.println("CustomerAssistant --- has started --- the project is on.");

  //Screen Initialization
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.fillScreen(BLACK);
  tft.setRotation(3);

  screenWidth = tft.width();
  screenHeight = tft.height();

  //Motor Initialization
  pinMode(MotorForward, OUTPUT);
  pinMode(MotorBack, OUTPUT);
  pinMode(MotorRight, OUTPUT);
  pinMode(MotorLeft, OUTPUT);

  //Sensor Initialization
  pinMode(echo_pin_forward, INPUT);
  pinMode(trig_pin_forward, OUTPUT);

  pinMode(echo_pin_top, INPUT);
  pinMode(trig_pin_top, OUTPUT);

  pinMode(echo_pin_right, INPUT);
  pinMode(trig_pin_right, OUTPUT);

  pinMode(echo_pin_left, INPUT);
  pinMode(trig_pin_left, OUTPUT);

  pinMode(echo_pin_backTop, INPUT);
  pinMode(trig_pin_backTop, OUTPUT);

  pinMode(echo_pin_backBottom, INPUT);
  pinMode(trig_pin_backBottom, OUTPUT);
  
  pinMode(echo_pin_backRight, INPUT);
  pinMode(trig_pin_backRight, OUTPUT);
  
  pinMode(echo_pin_backLeft, INPUT);
  pinMode(trig_pin_backLeft, OUTPUT);
  
  //Loading of the map
  robotMap = Map(2 * 7); // Change the number of connections here.

  //Definitions
  isNavigating = false;
  _time = 0;
  detected = false;
  forwardDistance = 0;
  forwardDistanceTop = 0;
  
  loadingAnimation = LoadingAnimation(screenWidth, screenHeight);
  loadingAnimation.loadParameters(tft);

  eyesAnimation = Eyes(screenWidth, screenHeight);
}

void loop() {
  if (!isNavigating) {
    if (_time == 0) {
      tft.setCursor(screenWidth / 2 - 105, screenHeight / 2 - 20);
      tft.setTextColor(WHITE); //setTextColor(uint16_t t)
      tft.setTextSize(5);
      tft.println("WELCOME");

      delay(2000);

      loadingAnimation.loadAnimation(tft);
      _time = 1;
    }

    tft.fillScreen(BLACK);
    eyesAnimation.createEyes(tft);

    //If heard something in microphone then: isNavigating = true;
    //SIMULATION: Heard that customer wants to go to library.
    destination = "library";
    isNavigating = true;
  }

  else {
    tft.fillScreen(BLACK);
    
    robotMap.drawMap(tft, tokens);
    robotMap.drawRobot(tft, robotPosition);

    detected = robotMap.Detect();
    robotMap.driveTo(robotPosition, destination, tokens);
    Serial.println(robotPosition.X);
    Serial.println(robotPosition.Y);
    delay(100);
  }
}
