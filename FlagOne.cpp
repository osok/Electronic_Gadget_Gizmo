/**
 * FlagOne.cpp - This is the First Flag, it will contain three simple games  
 * 
 * Flag     : 1
 * 
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */


#include "FlagOne.h"
#include "Global.h"


#define FLAGONE_MAX_FAILED_ATTEMPTS 10

FlagOne::FlagOne(){}

void FlagOne::setup(){
//  Serial.print("Flag setup, flagId = ");
//  Serial.println(getFlagId());

  printAddress("In FlagOne.setup() Method",getBox()); 

  addStage(STAGE_ID_ONE, &stage1); 
  addStage(STAGE_ID_TWO, &stage2); 
  addStage(STAGE_ID_THREE, &stage3); 
  
  changeMaxFailedAttempts(FLAGONE_MAX_FAILED_ATTEMPTS);

//  Serial.println("Flag setup complete.");
  
}



