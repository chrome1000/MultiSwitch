#include "MultiSwitch.h"

MultiSwitch TouchSense(D0, LOW);  //(pin, unpressed state)

void setup(){
  Serial.begin(9600);
  Serial.println("Starting");
}

void loop(){
  TouchSense.run();

  if(TouchSense.doubleTap() == true){
    Serial.println("Double tap");
  }
  if(TouchSense.tap() == true){
    Serial.println("Tap");
  }
  if(TouchSense.longHold() == true){
    Serial.println("Hold");
  }
  if(TouchSense.XLongHold() == true){
    Serial.println("XL Hold");
  }
}