/**
 * Game.cpp - This is the main class for the game, the INO will create this class
 *          then interact with it to manage the lifecycle of the game.
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#include "Game.h"
#include "FlagOne.h"

char xxx[1000];   // This is here because something in box is overwriting the above values TODO: Fix this problem
Box  _box;
char zzz[1000];   // This is here because something in box is overwriting the above values TODO: Fix this problem

void printAddress(char* description, void *ptr){
  Serial.print(description);
  Serial.print(" = ");
  Serial.println(uint32_t(ptr), DEC);
}

Box* getBox(){
  printAddress("In getBox() Method",&_box); 
  return &_box;
}


Game::Game(){}

void Game::setup(){
  Serial.println("Game is setting up...");
  FlagOne flag1(FLAG_ONE);
  FlagOne flag2(FLAG_TWO);
  FlagOne flag3(FLAG_THREE);
  FlagOne flag4(FLAG_FOUR);
  FlagOne flag5(FLAG_FIVE);

  addFlag(FLAG_ONE, &flag1);
  addFlag(FLAG_TWO, &flag2);
  addFlag(FLAG_THREE, &flag3);
  addFlag(FLAG_FOUR, &flag4);
  addFlag(FLAG_FIVE, &flag5);
  
}

void Game::run(){
  Serial.println("Game is starting...");
   printAddress("In Game.run() Method",getBox()); 
 
  Flag* currentFlag;

  currentFlag = getCurrentFlag();
  Serial.println("Current flag retrieved...");

  if(currentFlag == nullptr){
    Serial.println("Unable to get current flag.");
    return;
  }
  currentFlag->setup();  
  
  if(gameFinished()){
    Serial.println("Game finished.");
    return;
  }else{
    Serial.println("The game is not yet finished.");
  }
  
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
  return _currentFlagId == FLAG_COUNT;
}

void Game::flagFailed(){
  // TODO:  Shut down for a period of time

  // Write to EEPROM
}


void Game::addFlag(int flagId, Flag* flag){
  if(flagId >= 0 && flagId < FLAG_COUNT){
    Serial.print("adding flag,  flagId = ");
    Serial.println(flagId);
    
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
    return _flags[_currentFlagId];
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


