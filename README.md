# MultiSwitch

A simple Arduino library for detecting various switch / button / touch sensor interactions:

  -press : True when switch is engaged. False when released.
  
  -tap : true when switch has been enged and released. There is a small delay while waiting for 
   double-tap detection. If double-tap function isn't needed, setting its wait time to 0 will 
   eliminate the delay.
  
  -double-tap : Maximum wait time between taps is user definable. Default is 140 milliseconds.
  
  -long hold : Wait time for long hold detection is user definable. Default is 600 milliseconds.
  
  -extra long hold : Wait time is 3 seconds longer than long hold.
  
Tap, double-tap, and long-hold functions are mutually exclusive. All reset to false after
returning true. Extra long hold is NOT mutually exclusive from long-hold. If
long-hold is used, it will return true while waiting for the extra-long-hold timeout.
