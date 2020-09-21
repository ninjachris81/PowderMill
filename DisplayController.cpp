#include "DisplayController.h"
#include "TaskIDs.h"
#include "TaskManager.h"
#include "MotorController.h"
#include "Pins.h"
#include <LogHelper.h>

DisplayController::DisplayController() : AbstractIntervalTask(100) {
  
}

DisplayController::~DisplayController() {
}

void DisplayController::init() {
  tft = new Adafruit_TFTLCD(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
  tft->reset(); 
  tft->begin(0x9341);
  tft->setRotation(3); // Need for the Mega, please changed for your choice or rotation initial

  width = tft->width() - 1;
  height = tft->height() - 1;

  LOG_PRINTLN(F("TFT LCD test"));
  LOG_PRINT("TFT size is "); 
  LOG_PRINT(tft->width()); 
  LOG_PRINT("x"); 
  LOG_PRINTLN(tft->height());

  ts = new TouchScreen(XP, YP, XM, YM, SENSIBILITY);

  tft->fillScreen(WHITE);

  initializeButtons();

  MotorController* motorController = taskManager->getTask<MotorController*>(MOTOR_CONTROLLER);
  motorController->registerListener(this);
  
  refreshScreen();
}

void DisplayController::update() {

  TSPoint p = waitOneTouch();

  MotorController* motorController = taskManager->getTask<MotorController*>(MOTOR_CONTROLLER);

  for (uint8_t b=0; b<BUTTON_COUNT; b++) {
    if (buttons[b]->contains(p.x, p.y)) {
        // Action
        switch  (b) {
          case BUTTON_FASTER:
            LOG_PRINTLN("FASTER");
            motorController->increaseTargetSpeed();
            break;
          case BUTTON_SLOWER:
            motorController->decreaseTargetSpeed();
            LOG_PRINTLN("SLOWER");
            break;
          case BUTTON_STOP:
            motorController->stop();
            LOG_PRINTLN("STOP");
            break;
        }
    }
  }
}

void DisplayController::onPropertyValueChange(uint8_t id, uint8_t newValue, uint8_t oldValue) {
  LOG_PRINTLN(F("PROPERTY CHANGED"));
  refreshScreen();
}

void DisplayController::refreshScreen() {
  MotorController* motorController = taskManager->getTask<MotorController*>(MOTOR_CONTROLLER);

  tft->fillRect(0, 10, width, 50, WHITE);
  tft->setTextColor(BLACK);
  tft->setTextSize(6);
  tft->setCursor(20, 10);
  tft->print(motorController->getTargetSpeed());
  
  tft->setCursor(200, 10);
  tft->print(motorController->getRealSpeed());
}

void DisplayController::initializeButtons() {
  uint16_t w = 90;
  uint16_t h = 50;
  uint16_t x = 20;
  uint16_t offset = 20;
  uint16_t y = height - h - offset;

  uint8_t spacing_x = 6;
  
  uint8_t textSize = 2;

  char buttonlabels[BUTTON_COUNT][20] = {"FASTER", "SLOWER", "STOP"};
  uint16_t buttoncolors[BUTTON_COUNT] = {BLUE, BLUE, RED};

  for (uint8_t b=0; b<BUTTON_COUNT; b++) {
    LOG_PRINTLN(F("Init button"));
    buttons[b] = new Adafruit_GFX_Button();

    buttons[b]->initButton(tft,                           // TFT object
                  x+b*(w+spacing_x),  y,                  // x, y,
                  w, h, BLACK, buttoncolors[b], BLACK,    // w, h, outline, fill, 
                  buttonlabels[b], textSize);             // text
                  
    buttons[b]->drawButton();
  }

  // Save the y position to avoid draws
  
  buttons_y = y;
}


TSPoint DisplayController::waitOneTouch() {
  
  TSPoint p;
  uint8_t cycles = 0;
  
  do {
    p= ts->getPoint(); 
  
    pinMode(XM, OUTPUT); //Pins configures again for TFT control
    pinMode(YP, OUTPUT);

    cycles++;

    if (cycles>10) return p;  
  } while((p.z < MINPRESSURE )|| (p.z > MAXPRESSURE));

  return mapPoint(p);
}

// Map the coordinate X
TSPoint DisplayController::mapPoint(TSPoint p) {
  TSPoint returnP;

  LOG_PRINT(p.x);
  LOG_PRINT(" x ");
  LOG_PRINTLN(p.y);

  LOG_PRINTLN("->");

  returnP.x = map(TS_MAXY - (p.y - TS_MINY), TS_MINX, TS_MAXX, 0, tft->width());
  returnP.y = map(TS_MAXX - (p.x - TS_MINX), TS_MINY, TS_MAXY, 0, tft->height());

  LOG_PRINT(returnP.x);
  LOG_PRINT(" x ");
  LOG_PRINTLN(returnP.y);

  return returnP;
}
