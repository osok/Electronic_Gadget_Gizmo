/**
 * StageCoinFlip.cpp - This is the first stage of the first flag.
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


#include "StageCoinFlip.h"

void StageCoinFlip::setup(){
  char* buffer;

  buffer = getBox()->createBufferFromString("Coin Flip");
  addOutput(buffer);
  buffer = getBox()->createBufferFromString("Press A or B");
  addOutput(buffer);
  buffer = getBox()->createEmptyBuffer();
  addOutput(buffer);
  
}



boolean StageCoinFlip::process(){

  
  return 1;
}

