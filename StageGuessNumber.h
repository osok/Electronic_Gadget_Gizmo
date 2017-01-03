/**
 * StageGuessNumber.h - This is the third stage of the first flag.
 * 
 *          LOOK AWAY - SPOILER ALERT
 *          IF YOU READ FURTHER YOU WILL UNCOVER A HINT
 *          
 * It is a simple game which the user one or more buttons 
 * A, B, C, D and/or E.  A = 1, B = 2, C = 4, D = 8, E = 16
 * So the user can select 1 to 31. The computer then comapres 
 * its pick against the players pick. 3.2% likelihood that they win.  
 * 
 * Flag     : 1
 * Stage    : 3
 * 
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#ifndef StageGuessNumber_h
#define StageGuessNumber_h

#include <Arduino.h>
#include "Stage.h"
#include "Global.h"

class StageGuessNumber: public Stage{
  private:
    boolean _outcome;
    

  public:
    StageGuessNumber();
    void setup();
    boolean process();
    char* getTitle();
};

#endif

