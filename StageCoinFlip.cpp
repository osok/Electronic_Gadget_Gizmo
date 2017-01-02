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
  char title[MAX_OUTPUT_LINE_LENGTH+1];
  char command[MAX_OUTPUT_LINE_LENGTH+1];
  
  Serial.print("Stage StageCoinFlip  setup, stageId = ");
  Serial.println(getStageId());
  
  printAddress("In StageCoinFlip.setup() Method",getBox()); 

  Box* box = getBox();
  Serial.print("Address of box = ");
  Serial.println(uint32_t(box), DEC);
  box->setTitle("Coin Flip");
  box->setAttempts(getErrorCount());
  box->setCommand("Press any button");
 
}



boolean StageCoinFlip::process(){
  Serial.print("Stage StageCoinFlip  process, stageId = ");
  Serial.println(getStageId());

  int num = random(1,3);  //pick 1 or 2

  int guess = -1;
  Box* box = getBox();
  
  while(guess < 0 && guess > 1){
    box->paintScreen(false); // Show Stage Screen
    guess = box->getButton();
    if((guess + 1)==num){
      //Correct
      Serial.println("Correct!");
      box->updateStatus("Correct!");
      box->paintScreen(false);
      delay(5000);
      return true;
    }else{
      //Incorrect
      Serial.println("Incorrect :-(");
      box->updateStatus("Incorrect :-(");
      box->paintScreen(false);
      delay(5000);
      return false;
    }
  }
  
}

