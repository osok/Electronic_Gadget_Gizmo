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

#include "StageGuessButton.h"

StageGuessButton::StageGuessButton(){}


char* StageGuessButton::getTitle(){
  return "Button Guess";
}

void StageGuessButton::setup(){
//  Serial.print("Stage StageGuessButton  setup, stageId = ");
//  Serial.println(getStageId());
  if(!isInitialized()){
    buttonNumber = random(1,6);  //pick 1 - 5
  }
  initialized();

}


boolean StageGuessButton::process(){
//  Serial.print("Stage StageGuessButton  process, stageId = ");
//  Serial.println(getStageId());
//
//  Serial.print("  Random number = ");
//  Serial.println(buttonNumber);

  int guess = -1;
  Box* box = getBox();
  box->clearOutput();
  box->writeOutput("Can you guess, which", "button A-E to press?");
  boolean done = false;
  boolean success = false;
  boolean useButtons[] = {true,true,true,true,true,false};
  char* labels[] = {"A","B","C","D","E","K"};
  
  while( !done ){

    box->updateStatus("");
    box->clearUserInput();
    box->paintScreen(DISPLAY_USER_SCREEN); // Show Stage Screen
    
    guess = box->getButton(useButtons, labels);
//    Serial.print("Guess  = ");
//    Serial.println(guess);

     if((guess + 1)==buttonNumber){
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
//  Serial.print("Stage StageGuessButton process is complete, stageId = ");
//  Serial.println(getStageId());
  return success;
  
}

