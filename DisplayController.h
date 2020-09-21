#ifndef DISPLAYCONTROLLER_H
#define DISPLAYCONTROLLER_H

#include <AbstractIntervalTask.h>
#include "TaskIDs.h"
#include "Property.h"

#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPFD5408_TouchScreen.h>     // Touch library

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define BUTTON_COUNT 3
#define BUTTON_FASTER 0
#define BUTTON_SLOWER 1
#define BUTTON_STOP 2

// Calibrates value
#define SENSIBILITY 300
#define MINPRESSURE 10
#define MAXPRESSURE 1000

//These are the pins for the shield!
#define YP A1 
#define XM A2 
#define YM 7  
#define XP 6 

/*
//Macros replaced by variables
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940
*/

class DisplayController : public AbstractIntervalTask, public Property<uint8_t>::ValueChangeListener {
public:
  DisplayController();
  ~DisplayController();
  
  void init();

  void update();

  void onPropertyValueChange(uint8_t id, uint8_t newValue, uint8_t oldValue);

private:
  void initializeButtons();

  TSPoint waitOneTouch();

  TSPoint DisplayController::mapPoint(TSPoint p);

  void refreshScreen();
  
  Adafruit_GFX_Button* buttons[BUTTON_COUNT];

  TouchScreen *ts;

  Adafruit_TFTLCD* tft;

  uint16_t width = 0;
  uint16_t height = 0;

  uint16_t buttons_y = 0;

  short TS_MINX=150;
  short TS_MINY=110;
  short TS_MAXX=900;
  short TS_MAXY=890;

};


#endif
