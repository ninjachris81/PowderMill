/* META INFOS
target_package=arduino
target_platform=avr
board=mega
*/

#include "TaskManager.h"

#include "MotorController.h"
#include "DisplayController.h"
#include <LogHelper.h>

TaskManager taskManager;

MotorController motorController;
DisplayController displayController;

void setup () {
  LOG_INIT();
  
  taskManager.registerTask(&motorController);
  taskManager.registerTask(&displayController);

  taskManager.init();
}

void loop()
{
  taskManager.update();
  delay(10);
}



/*
//-- Setup
void setup(void) {
  

  initializeButtons();
  
  // Border

  drawBorder();
  
  // Initial screen
  
  tft.setCursor (55, 50);
  tft.setTextSize (3);
  tft.setTextColor(RED);
  tft.println("SPFD5408");
  tft.setCursor (65, 85);
  tft.println("Library");
  tft.setCursor (55, 150);
  tft.setTextSize (2);
  tft.setTextColor(BLACK);
  tft.println("Calibration");

  tft.setCursor (80, 250);
  tft.setTextSize (1);
  tft.setTextColor(BLACK);
  tft.println("Touch to proceed");

  // Wait touch

  waitOneTouch();

  // Calibrate it
  
  //calibrate_TS();

  // Wait touch

  waitOneTouch();

  // Calibration

  showCalibration();
}
*/

/*
TSPoint waitOneTouch() {
  
  TSPoint p;
  
  do {
    p= ts.getPoint(); 
  
    pinMode(XM, OUTPUT); //Pins configures again for TFT control
    pinMode(YP, OUTPUT);
  
  } while((p.z < MINPRESSURE )|| (p.z > MAXPRESSURE));

  return mapPoint(p);
}
*/

/*
// Draw a border
void drawBorder () {

  uint16_t width = tft.width() - 1;
  uint16_t height = tft.height() - 1;
  uint8_t border = 10;

  tft.fillScreen(RED);
  tft.fillRect(border, border, (width - border * 2), (height - border * 2), WHITE);
  
}
*/

/*
// Show a screen of calibration
void showCalibration() {
  
  // Clear
  
  tft.fillScreen(BLACK);
  tft.setTextSize (1);

  // Header
  
  tft.fillRect(0, 0, width, 10, RED);

  tft.setCursor (40, 0);
  tft.setTextColor(WHITE);
  tft.println("*** Test of calibration ***");

  // Footer

  TSPoint p; // Only for show initial values
  p.x=0;
  p.y=0;
  p.z=0;
  
  showTouched(p);

  // Buttons

  for (uint8_t i=0; i<3; i++) {
      buttons[i].drawButton();
  }
  
}
*/

/*
// Show the coordinates     

void showTouched(TSPoint p) {

  uint8_t w = 40; // Width
  uint8_t h = 10; // Heigth
  uint8_t x = (width - (w*2)); // X
  uint8_t y = 11; // Y
  
  tft.fillRect(x, y, w*2, h, WHITE); // For cleanup

  tft.drawRect(x, y, w, h, RED); // For X
  tft.drawRect(x+w+2, y, w*2, h, RED); // For Y

  tft.setTextColor(BLACK);
  tft.setCursor(x+2, y + 1);
  tft.print("X: ");
  showValue(p.x);
  
  tft.setCursor(x+2+w+2, y + 1);
  tft.print("Y: ");
  showValue(p.y);

}
*/

/*
// Show a value of TSPoint

void showValue (uint16_t value) {

  if (value < 10)
    tft.print("00");
  if (value < 100)
    tft.print("0");
    
  tft.print(value);
  
}
*/

/*
// Show results of calibration

void showResults() {

  tft.fillScreen(BLACK);
  
  // Header
  
  tft.fillRect(0, 0, width, 10, RED);

  tft.setCursor (40, 0);
  tft.setTextColor(WHITE);
  tft.println("*** Results of calibration ***");

  // Results
  
  tft.setCursor(5, 30);
  tft.setTextSize(2);
  tft.println("After calibration: ");
  tft.print("TS_MINX= ");tft.println(TS_MINX);
  tft.print("TS_MINY= ");tft.println(TS_MINY);
  tft.println();
  tft.print("TS_MAXX= ");tft.println(TS_MAXX);
  tft.print("TS_MAXY= ");tft.println(TS_MAXY);

}
*/

/*
// Map the coordinate X
TSPoint mapPoint(TSPoint p) {
  TSPoint returnP;

  Serial.print(p.x);
  Serial.print(" x ");
  Serial.println(p.y);

  Serial.println("->");

  returnP.x = map(TS_MAXY - (p.y - TS_MINY), TS_MINX, TS_MAXX, 0, tft.width());
  returnP.y = map(TS_MAXX - (p.x - TS_MINX), TS_MINY, TS_MAXY, 0, tft.height());

  Serial.print(returnP.x);
  Serial.print(" x ");
  Serial.println(returnP.y);

  return returnP;
}
*/
