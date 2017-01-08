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

StageCoinFlip::StageCoinFlip(){}

char* StageCoinFlip::getTitle(){
  return "Coin Flip";
}

void StageCoinFlip::setup(){
//  Serial.print("Stage StageCoinFlip  setup, stageId = ");
//  Serial.println(getStageId());
  if(!isInitialized()){
    coinSide = random(1,3);  //pick 1 or 2
  }
  initialized();

}


boolean StageCoinFlip::process(){
//  Serial.print("Stage StageCoinFlip  process, stageId = ");
//  Serial.println(getStageId());
//
//  Serial.print("  Random number = ");
//  Serial.println(coinSide);

  int guess = -1;
  Box* box = getBox();
  box->clearOutput();
  box->writeOutput("A=Heads, B=Tails", "Heads or Tails?");
  boolean done = false;
  boolean success = false;
  boolean useButtons[] = {true,true,false,false,false,false};
  char* labels[] = {"Heads","Tails","C","D","E","K"};
  
  while( !done ){

    box->updateStatus("");
    box->clearUserInput();
    box->paintScreen(DISPLAY_USER_SCREEN); // Show User Screen
    
    guess = box->getButton(useButtons, labels);
//    Serial.print("Guess  = ");
//    Serial.println(guess);

    if((guess + 1)==coinSide){
      //Correct
      box->updateStatus("Correct!");
      box->paintScreen(DISPLAY_USER_SCREEN);
      delay(3000);
      done = true;
      success = true;
    }else{
      //Incorrect
      box->updateStatus("Incorrect...");
      box->paintScreen(DISPLAY_USER_SCREEN);
      delay(3000);
      done = true;
      success = false;
    }
  }
//  Serial.print("Stage StageCoinFlip process is complete, stageId = ");
//  Serial.println(getStageId());
  return success;
  
}

