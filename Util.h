/**
 * Util.h - This class is manages a number of utility  
 * functions like generating Random String for Flags.
 * Base64 Encoding strings and the such
 * 
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#ifndef Util_h
#define Util_h

#include <Arduino.h>

class Util {
  private:
    char* characterSet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    
  public:
    Util();
    int getRandomNumber(int lower, int upper);
    char* getRandomString(int length);
    void wait(int seconds);
};


#endif

