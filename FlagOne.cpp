/**
 * FlagOne.cpp - This is the First Flag, it will contain three simple games  
 * 
 * Flag     : 1
 * 
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#include "FlagOne.h"
#include "StageCoinFlip.h"

#define FLAGONE_MAX_FAILED_ATTEMPTS 10

void FlagOne::setup(){
  StageCoinFlip coinFlipStage1(STAGE_ID_ONE, getBox());
  StageCoinFlip coinFlipStage2(STAGE_ID_TWO, getBox());
  StageCoinFlip coinFlipStage3(STAGE_ID_THREE, getBox());

  addStage(STAGE_ID_ONE, &coinFlipStage1); 
  addStage(STAGE_ID_TWO, &coinFlipStage2); 
  addStage(STAGE_ID_THREE, &coinFlipStage3); 
  
  changeMaxFailedAttempts(FLAGONE_MAX_FAILED_ATTEMPTS);
  
}


boolean FlagOne::process(){
  Stage* currentStage;
  
  while(!allStagesComplete()){
    currentStage = getCurrentStage();
    currentStage->setup();

    if(currentStage->process()){
      stageCompleted();
    }else{
      addFailedAttempt();
    }
  }
  
}

