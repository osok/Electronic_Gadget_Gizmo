/**
 * Flag.cpp - This is a base class for the Flags.
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#include "Flag.h"


//These need to be here, but should not be populated
// the concrete classes will implement them.
// Not having them cause a linking error
// "undefined reference to `vtable for"
// Define any virtual functions with empty bodies
void Flag::setup(){}
boolean Flag::process(){}


Flag::Flag(int id, Box* box){
  _id = id;
  _box = box;
  
}
Box* Flag::getBox(){
  return _box;
}



void Flag::addFailedAttempt(){
  _failedAttempts++;

  
  //TODO: Write to EEPROM

}

boolean Flag::tooManyFailedAttempts(){
  return _failedAttempts >= _failedAttemptMax;
}

void Flag::changeMaxFailedAttempts(int max){
  _failedAttemptMax = max;
}

void Flag::addStage(int stageId, Stage* stage){
  if(stageId >= 0 && stageId < MAX_STAGE_COUNT){
    _stage[stageId] = stage;
  }
}

Stage* Flag::getCurrentStage(){
  if(_currentStage >= 0 && _currentStage < MAX_STAGE_COUNT){
    return _stage[_currentStage];
  }

  return nullptr;
}

void Flag::stageCompleted(){
  _currentStage++;

  //TODO: Write to EEPROM
}

boolean Flag::allStagesComplete(){
  return _currentStage >= MAX_STAGE_COUNT;
}

char* Flag::getFlagString(){
  if(allStagesComplete()){
    
  }else{
    return FLAG_NOT_COMPLETE;
  }
}


void Flag::setCurrentStageId(int stageId){
  if(stageId >= 0 && stageId < MAX_STAGE_COUNT){
    _currentStage = stageId;
  }

  
}


