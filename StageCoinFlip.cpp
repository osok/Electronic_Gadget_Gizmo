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
  Serial.print("Stage StageCoinFlip  setup, stageId = ");
  Serial.println(getStageId());
  
  printAddress("In StageCoinFlip.setup() Method",getBox()); 

}


boolean StageCoinFlip::process(){
  Serial.print("Stage StageCoinFlip  process, stageId = ");
  Serial.println(getStageId());

  int num = random(1,3);  //pick 1 or 2
  Serial.print("  Random number = ");
  Serial.println(num);

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
    box->paintScreen(false); // Show Stage Screen
    
    guess = box->getButton(useButtons, labels);
    Serial.print("Guess  = ");
    Serial.println(guess);

    if((guess + 1)==num){
      //Correct
      box->updateStatus("Correct!");
      box->paintScreen(false);
      delay(5000);
      done = true;
      success = true;
    }else{
      //Incorrect
      box->updateStatus("Incorrect :-(");
      box->paintScreen(false);
      delay(5000);
      done = true;
      success = false;
    }
  }
  Serial.print("Stage StageCoinFlip process is complete, stageId = ");
  Serial.println(getStageId());
  return success;
  
}

