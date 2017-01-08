/**
 * StageGuessButton.h - This is the second stage of the first flag.
 * It is a simple game which the user selects a button A, B, C, D or E.
 * The computer then comapres its pick against the players pick.
 * 20% likelihood that they win.  
 * 
 * Flag     : 1
 * Stage    : 2
 * 
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#ifndef StageGuessButton_h
#define StageGuessButton_h

#include <Arduino.h>
#include "Stage.h"
#include "Global.h"

class StageGuessButton: public Stage{
  private:
    boolean _outcome;
    int buttonNumber = 0;

  public:
    StageGuessButton();
    void setup();
    boolean process();
    char* getTitle();
};

#endif

