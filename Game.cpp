/**
 * Game.cpp - This is the main class for the game, the INO will create this class
 *          then interact with it to manage the lifecycle of the game.
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#include "Game.h"



Game::Game(){}

void Game::setup(){
  Serial.println("Game is setting up...");

  addFlag(FLAG_ONE, &flag1);
  addFlag(FLAG_TWO, &flag2);
  addFlag(FLAG_THREE, &flag3);
  addFlag(FLAG_FOUR, &flag4);
  addFlag(FLAG_FIVE, &flag5);

  _webServer.setup();
}

void Game::run(){
  Serial.println("Game is starting...");


  if(gameFinished()){
    Serial.println("Game finished.");
    wait(3);
    return;
  }else{
    Serial.println("The game is not yet finished.");
  }

  _webServer.run();

  Flag* currentFlag;
  currentFlag = getCurrentFlag();
  Serial.println("Current flag retrieved...");


  if(currentFlag == nullptr){
    Serial.println("Unable to get current flag.");
    return;
  }

  Serial.println("setting up current flag");
  currentFlag->setup();  
  
  
  if(currentFlag->process()){
    // Success
    flagCompleted();
  }else{
    // Failed
    flagFailed();
  }

  
  
}

void Game::flagCompleted(){
  _currentFlagId++;
}

boolean Game::gameFinished(){
  return _currentFlagId >= FLAG_COUNT;
}

void Game::flagFailed(){
  // TODO:  Shut down for a period of time

  // Write to EEPROM
}


void Game::addFlag(int flagId, Flag* flag){
  if(flagId >= 0 && flagId < FLAG_COUNT){
    Serial.print("adding flag,  flagId = ");
    Serial.println(flagId);
    flag->setFlagId(flagId);
    printAddress("   addFlag flag address = ", flag);
     _flags[flagId] = flag;
  }
}


void Game::setCurrentFlag(int flagId){
  if(flagId >= 0 && flagId < FLAG_COUNT){
    _currentFlagId = flagId;
  }
}


Flag* Game::getCurrentFlag(){
  if(_currentFlagId >= 0 && _currentFlagId < FLAG_COUNT){
    Serial.print("Getting Current flag,  flagId = ");
    Serial.println(_currentFlagId);
    Flag* flag = _flags[_currentFlagId];
    
    printAddress("   getCurrentFlag flag address = ", flag);

    return flag;
  }
}

void Game::setCurrentStage(int stageId){
  if(stageId >= 0 && stageId < MAX_STAGE_COUNT){
    Flag* flag = getCurrentFlag();
    flag->setCurrentStageId(stageId);
  }
}

void Game::setCurrentErrors(int errorCount){
  getCurrentFlag()->setFailedAttempts(errorCount);
}


