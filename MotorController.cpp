#include "MotorController.h"
#include "Pins.h"

MotorController::MotorController() : AbstractIntervalTask(100) {
}

MotorController::~MotorController() {
}

void MotorController::init() {
  targetSpeed.init(PROP_TARGET_SPEED, 0);
  animatedSpeed.init(PROP_ANIMATED_SPEED, 0, 400, 1);
  realSpeed.init(PROP_REAL_SPEED, 0);
  
  motor = new L298N(MOTOR_EN, MOTOR_IN1, MOTOR_IN2);
  motor->forward();
  motor->stop();

  animatedSpeed.registerValueChangeListener(this);
}

void MotorController::update() {
  animatedSpeed.update();
}

void MotorController::onPropertyValueChange(uint8_t id, float newValue, float oldValue) {
  switch(id) {
    case PROP_ANIMATED_SPEED:
      uint8_t cSpeed = animatedSpeed.getValue();

      LOG_PRINT(F("Setting speed "));
      LOG_PRINTLN(cSpeed);

      if (cSpeed==0) {
        motor->stop();
      } else {
        motor->setSpeed(cSpeed);
        motor->forward();
      }

      realSpeed.setValue(cSpeed);
      
      break;
  }
}

void MotorController::registerListener(Property<uint8_t>::ValueChangeListener *listener) {
  targetSpeed.registerValueChangeListener(listener);
  realSpeed.registerValueChangeListener(listener);
}

uint8_t MotorController::getTargetSpeed() {
  return targetSpeed.getValue();
}

uint8_t MotorController::getRealSpeed() {
  return realSpeed.getValue();
}

void MotorController::setTargetSpeed(uint8_t thisTargetSpeed) {
  targetSpeed.setValue(constrain(thisTargetSpeed, 0, 255));
  animatedSpeed.setValue(targetSpeed.getValue());
}

void MotorController::increaseTargetSpeed() {
  if (targetSpeed.getValue()==255) return;
  setTargetSpeed(targetSpeed.getValue()+1);
}

void MotorController::decreaseTargetSpeed() {
  if (targetSpeed.getValue()==0) return;
  setTargetSpeed(targetSpeed.getValue()-1);
}


void MotorController::stop() {
  setTargetSpeed(0);
}
