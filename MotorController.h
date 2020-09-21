#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <AbstractIntervalTask.h>
#include "TaskIDs.h"
#include "AnimatedProperty.h"
#include <L298N.h>

#define PROP_TARGET_SPEED 0
#define PROP_ANIMATED_SPEED 1
#define PROP_REAL_SPEED 2

class MotorController : public AbstractIntervalTask, public Property<float>::ValueChangeListener  {
public:
  MotorController();
  ~MotorController();
  
  void init();

  void update();

  void onPropertyValueChange(uint8_t id, float newValue, float oldValue);

  uint8_t getTargetSpeed();

  uint8_t getRealSpeed();

  void setTargetSpeed(uint8_t thisTargetSpeed);

  void increaseTargetSpeed();
  void decreaseTargetSpeed();

  void registerListener(Property<uint8_t>::ValueChangeListener *listener);
  
  void stop();
private:
  Property<uint8_t> targetSpeed;
  AnimatedProperty<float> animatedSpeed;
  Property<uint8_t> realSpeed;

  L298N* motor;
};


#endif
