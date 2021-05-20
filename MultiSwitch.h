
#ifndef MultiSwitch_h
#define MultiSwitch_h

#include "Arduino.h"
#include "SimpleTimer.h"

class MultiSwitch
{
  public:
    MultiSwitch(uint8_t pin);  //Default pin state is HIGH
    MultiSwitch(uint8_t pin, bool unpressedState);
    void run();
    void longPressTime(uint16_t holdWait);    //Hold duration (in ms) to trigger a long hold
    void doubleTapTime(uint16_t doubleWait);  //Max ms between double taps. 0 to ignore double taps
    bool pressed();
    bool tap();
    bool doubleTap();
    bool longHold();
    bool XLongHold();
    void reset();
    
  private:
    uint8_t _pin;
    bool _unpressedState = HIGH;        //default pin state 
    long _longHoldTimer;
    long _doubleTapTimer;
    uint16_t _holdWait = 600;               //default duration to trigger a long hold
    uint16_t _doubleWait = 140;             //default max interval between double taps
    long _currentMillis;
    long _previousMillis;
    bool _PreviousSwitchState;
    bool _firstTap = false;
    bool _tap = false;
    bool _doubleTap = false;
    bool _longHold = false;
    bool _pressed = false;
    bool _released = true;
    bool _checkLongHold = false;
    bool _checkDoubleTap = false;
    bool _XLongHold = false;
    bool _checkXLongHold = false;   
};

#endif