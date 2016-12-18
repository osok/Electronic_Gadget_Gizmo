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

void FlagOne::setupStages(){
  StageCoinFlip coinFlipStage1(STAGE_ID_ONE);
  StageCoinFlip coinFlipStage2(STAGE_ID_TWO);
  StageCoinFlip coinFlipStage3(STAGE_ID_THREE);

  addStage(STAGE_ID_ONE, &coinFlipStage1); 
  addStage(STAGE_ID_TWO, &coinFlipStage2); 
  addStage(STAGE_ID_THREE, &coinFlipStage3); 
  
  changeMaxFailedAttempts(FLAGONE_MAX_FAILED_ATTEMPTS);
  
}

