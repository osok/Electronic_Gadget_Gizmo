/**
 * Flag.cpp - This is a base class for the Flags.
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#include "Flag.h"


Flag::Flag(int id){
  _id = id;
  
}

void Flag::addFailedAttempt(){
  _failedAttempts++;
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
}

boolean Flag::allStagesComplete(){
  return _currentStage >= MAX_STAGE_COUNT;
}

char* Flag::getFlag(){
  if(allStagesComplete()){
    
  }else{
    return FLAG_NOT_COMPLETE;
  }
}




