/**
 * FlagOne.h - This is the First Flag, it will contain three simple games  
 * 
 * Flag     : 1
 * 
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */
 
#ifndef FlagOne_h
#define FlagOne_h

#include <Arduino.h>
#include "Flag.h"

class FlagOne: public Flag{
  protected:

   public:
    FlagOne(int id, Box* box) : Flag(id, box){};  //Calls the parent constructor
    void setup();
    boolean process();

};

#endif
