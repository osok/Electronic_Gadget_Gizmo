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
#include "StageCoinFlip.h"

class FlagOne: public Flag{

  private:
    /** These are only here to reserve the memory for them
     *  they should always be reference from the Flags stages
     *  pointer array.
     */
    StageCoinFlip coinFlipStage1;
    StageCoinFlip coinFlipStage2;
    StageCoinFlip coinFlipStage3;

  public:
    FlagOne();  
    void virtual setup(); 
};

#endif
