/**
 * StageCoinFlip.h - This is the first stage of the first flag.
 * It is a simple game which the user selects button A or Button B.
 * The computer then comapres its pick against the players pick.
 * 50:50 likelihood that they win.  
 * 
 * Flag     : 1
 * Stage    : 1
 * 
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#ifndef StageCoinFlip_h
#define StageCoinFlip_h

#include <Arduino.h>
#include "Stage.h"
#include "Global.h"

class StageCoinFlip: public Stage{
  private:
    boolean _outcome;
    

  public:
    StageCoinFlip();
    void setup();
    boolean process();
};

#endif

