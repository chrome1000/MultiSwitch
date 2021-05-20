#include "Arduino.h"
#include "Multiswitch.h"

MultiSwitch :: MultiSwitch(uint8_t pin){
  pinMode(pin,INPUT_PULLUP);
  _pin = pin;
  _PreviousSwitchState = (digitalRead(_pin) != _unpressedState);
  _previousMillis = millis();
}

MultiSwitch :: MultiSwitch(uint8_t pin, bool unpressedState){
  pinMode(pin,INPUT_PULLUP);
  _pin = pin;
  _unpressedState = unpressedState;
  _PreviousSwitchState = (digitalRead(_pin) != _unpressedState);
  _previousMillis = millis();
}

//Changes the time required to trigger a long hold
void MultiSwitch :: longPressTime(uint16_t holdWait){
  _holdWait = holdWait;
}

//Changes the maximum wait time for the second tap of a double tap
void MultiSwitch :: doubleTapTime(uint16_t doubleWait){
  _doubleWait = doubleWait;
}

bool MultiSwitch :: pressed(){
  return(_pressed);
}

bool MultiSwitch :: tap(){
  if(_tap){
    reset();
    return(true);
  } else return(false);
}

bool MultiSwitch :: doubleTap(){
  if(_doubleTap){
    reset();
    return(true);
  }
  else return(false);
}

bool MultiSwitch :: longHold(){
  if(_longHold){
    reset();
    return(true);
  }
  else return(false);
}

bool MultiSwitch :: XLongHold(){
  if(_XLongHold){
    _checkXLongHold = false;
    reset();
    return(true);
  }
  else return(false);
}

void MultiSwitch :: reset(){
  _firstTap = false;
  _tap = false;
  _longHold = false;
  _doubleTap = false;
  _checkLongHold = false;
  _checkDoubleTap = false;
  _XLongHold = false;
}

void MultiSwitch :: run(){
  bool _SwitchState = (digitalRead(_pin) != _unpressedState);
  //Switch activated
  if(_SwitchState && !_PreviousSwitchState){
    delay(10);  //db
    _pressed = true;
    _checkLongHold = true;
    _longHoldTimer = millis() + _holdWait;

    //Double tap
    if(_firstTap == true){  
      _doubleTap = true;
      _firstTap = false;
      _checkDoubleTap = false;
      _checkLongHold = false;
    }
    //Initial tap
    else{
      _firstTap = true;
    }   
  }
  //Switch released
  else if(!_SwitchState && _PreviousSwitchState){
    delay(10); //db
    _pressed = false;
    _checkLongHold = false;
    _checkXLongHold = false;
    if(_firstTap == true && _doubleWait > 0){
      _checkDoubleTap = true;
      _doubleTapTimer = millis() + _doubleWait;
    }
  }

  //Switch held
  else if(_SwitchState && _PreviousSwitchState){
    //Extra long hold
    if(_checkXLongHold == true && millis() > _longHoldTimer + 4000){
      _XLongHold = true;
    }
    //Long hold
    else if(_checkLongHold == true && millis() > _longHoldTimer){
      _longHold = true;
      _checkLongHold = false;
      _firstTap = false;
      //Set timer for extra long hold
      _checkXLongHold = true;
    }
  }
  
  //Single tap (switch continuously released)
  else if(_checkDoubleTap == true && millis() > _doubleTapTimer && _pressed == false && _firstTap == true){
    _firstTap = false;
    _checkDoubleTap = false;
    _tap = true;
  }
  _PreviousSwitchState = _SwitchState;
}