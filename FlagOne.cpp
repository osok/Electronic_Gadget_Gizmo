/**
 * FlagOne.cpp - This is the First Flag, it will contain three simple games  
 * 
 * Flag     : 1
 * 
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#include "Game.h"
#include "FlagOne.h"
#include "StageCoinFlip.h"

#define FLAGONE_MAX_FAILED_ATTEMPTS 10

void FlagOne::setup(){
  Serial.print("Flag setup, ");
  Serial.println(getFlagId());

  printAddress("In FlagOne.setup() Method",getBox()); 


  StageCoinFlip coinFlipStage1(getFlagId(),STAGE_ID_ONE);
  StageCoinFlip coinFlipStage2(getFlagId(),STAGE_ID_TWO);
  StageCoinFlip coinFlipStage3(getFlagId(), STAGE_ID_THREE);

  addStage(STAGE_ID_ONE, &coinFlipStage1); 
  addStage(STAGE_ID_TWO, &coinFlipStage2); 
  addStage(STAGE_ID_THREE, &coinFlipStage3); 
  
  changeMaxFailedAttempts(FLAGONE_MAX_FAILED_ATTEMPTS);

  Serial.println("Flag setup complete.");
  
}



