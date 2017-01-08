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

#include "StageGuessNumber.h"

StageGuessNumber::StageGuessNumber(){}




char* StageGuessNumber::getTitle(){
  return "Just Guess";
}

void StageGuessNumber::setup(){
//  Serial.print("Stage StageGuessNumber  setup, stageId = ");
//  Serial.println(getStageId());
  if(!isInitialized()){
    randomNumber = random(1,32);  //pick 1 - 31
  }
  initialized();

}


boolean StageGuessNumber::process(){
//  Serial.print("Stage StageGuessNumber  process, stageId = ");
//  Serial.println(getStageId());
//
//  Serial.print("***** Random number = ");
//  Serial.print(randomNumber);
//  Serial.println("  ********************* ");

  
  int guess = -1;
  Box* box = getBox();
  box->clearOutput();
  box->writeOutput("Press any combo of", "buttons A-E");
  boolean done = false;
  boolean success = false;
  boolean useButtons[] = {true,true,true,true,true,false};
  char* labels[] = {"A","B","C","D","E","K"};
  
  while( !done ){

    box->updateStatus("");
    box->clearUserInput();
    box->paintScreen(DISPLAY_USER_SCREEN); // Show Stage Screen
    
    guess = box->getButtons(STAGE_TIME, 5, useButtons, labels);
//    Serial.print("Guess  = ");
//    Serial.println(guess);

    if(guess==randomNumber){
      //Correct
      box->updateStatus("Correct!");
      box->paintScreen(DISPLAY_USER_SCREEN);
      delay(3000);
      done = true;
      success = true;
    }else if (guess<randomNumber){
      //Incorrect
      box->updateStatus("Not Enough");
      box->paintScreen(DISPLAY_USER_SCREEN);
      delay(3000);
      done = true;
      success = false;
    }else{
      //Incorrect
      box->updateStatus("Too Much");
      box->paintScreen(DISPLAY_USER_SCREEN);
      delay(3000);
      done = true;
      success = false;
      
    }
  }
//  Serial.print("Stage StageGuessNumber process is complete, stageId = ");
//  Serial.println(getStageId());
  return success;
  
}

