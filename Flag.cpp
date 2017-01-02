/**
 * Flag.cpp - This is a base class for the Flags.
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#include "Flag.h"

void Flag::setup(){
  //Empty must be overridden
}

Flag::Flag(){
  Serial.print("Flag created");
}

void Flag::setFlagId(int flagId){
  Serial.print("Flag setFlagId,  flagId = ");
  Serial.println(getFlagId());
  _flagId = flagId;
}

int Flag::getFailedAttempts(){
  return _failedAttempts;
}
int Flag::getMaxFailedAttempts(){
  return _failedAttemptMax;
}

boolean Flag::process(){
  Stage* currentStage;
  Serial.print("Flag process started, flagId = ");
  Serial.println(getFlagId());

  while(!allStagesComplete()){

    Serial.println("All stages are not yet completed.");
    
    if(tooManyFailedAttempts()){
      Serial.println("Too many failed attempts.");
      return false;
    }

    Serial.println("Getting current stage..");
    currentStage = getCurrentStage();
    
    Serial.println("Got current stage..");
    currentStage->setup();

    // Set the rest of the title screen up
    getBox()->setTitle(currentStage->getTitle());
    getBox()->setAttempts(getFailedAttempts(), getMaxFailedAttempts());
    getBox()->setCurrentFlag(getFlagId(), currentStage->getStageId());
    getBox()->setCommand("Press any button");  
   
    Serial.println("Painting Screen...");
    getBox()->paintScreen(true); //show Title Screen

    // Wait for user to press any button
    int button = getBox()->getButton();
    Serial.print("Button pressed = ");
    Serial.println(button);

    if(currentStage->process()){
      Serial.println("stage completed.");
      stageCompleted();
    }else{
      Serial.println("stage failed.");
      addFailedAttempt();
    }
  }
  Serial.print("Flag process complete, flagId = ");
  Serial.println(getFlagId());

  return true;
  
}

int Flag::getFlagId(){
  return _flagId;
}


void Flag::setFailedAttempts(int attempts){
  _failedAttempts = attempts;
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
    Serial.print("Adding a Stage, flagId = ");
    Serial.print(getFlagId());
    Serial.print(", stageId = ");
    Serial.println(stageId);
    
    stage->setFlagId(getFlagId());
    stage->setStageId(stageId);
    
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
    Serial.print("  currentStage = ");
    Serial.println(_currentStage);
    Serial.print("  MAX_STAGE_COUNT = ");
    Serial.println(MAX_STAGE_COUNT);
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
    Serial.print("Setting the current stageId, flagId = ");
    Serial.println(getFlagId());
    Serial.print(", stageId = ");
    Serial.println(stageId);
    _currentStage = stageId;
  }

  
}


