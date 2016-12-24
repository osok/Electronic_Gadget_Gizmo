/**
 * Game.cpp - This is the main class for the game, the INO will create this class
 *          then interact with it to manage the lifecycle of the game.
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#include "Game.h"
#include "FlagOne.h"

Game::Game(){
  
}


Box* Game::getBox(){
  return &_box;
}

void Game::setup(){
  FlagOne flag1(FLAG_ONE, getBox());
  FlagOne flag2(FLAG_TWO, getBox());
  FlagOne flag3(FLAG_THREE, getBox());
  FlagOne flag4(FLAG_FOUR, getBox());
  FlagOne flag5(FLAG_FIVE, getBox());

  addFlag(FLAG_ONE, &flag1);
  addFlag(FLAG_TWO, &flag2);
  addFlag(FLAG_THREE, &flag3);
  addFlag(FLAG_FOUR, &flag4);
  addFlag(FLAG_FIVE, &flag5);
}

void Game::run(){
  Flag* currentFlag;

  currentFlag = getCurrentFlag();
  currentFlag->setup();

  if(currentFlag->process()){
    // Flag Completed
    
  }else{
    // Flag Not compleeted
    
  }
  
}

void Game::addFlag(int flagId, Flag* flag){
  if(flagId >= 0 && flagId < FLAG_COUNT){
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
    return _flags[_currentFlagId];
  }
}

void Game::setCurrentStage(int stageId){
  if(stageId >= 0 && stageId < MAX_STAGE_COUNT){
    Flag* flag = getCurrentFlag();
    flag->setCurrentStageId(stageId);
  }
}

void setCurrentErrors(int errorCount){
  
}


