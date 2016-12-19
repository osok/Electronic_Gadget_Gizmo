/**
 * Stage.cpp - This is a base class for the Stages included in the Flags.
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */
#include "Stage.h"


//These need to be here, but should not be populated
// the concrete classes will implement them.
// Not having them cause a linking error
// "undefined reference to `vtable for"
// Define any virtual functions with empty bodies
void Stage::setup(){}
boolean Stage::process(){}



Stage::Stage(int id, Box* box){
  _id = id;  
  _box = box;

}

Box* Stage::getBox(){
  return _box;
}

void Stage::resetOutput(){
  _outputCount = 0;
  for(int r = 0; r < MAX_OUTPUT_LINE_LENGTH; r++){
    strncpy(_output[r], getBox()->getBlankLine(), MAX_OUTPUT_LINE_LENGTH);
  } 
}

void Stage::resetError(){
  _errorCount = 0;
  for(int r = 0; r < MAX_OUTPUT_LINE_LENGTH; r++){
    strncpy(_error[r], getBox()->getBlankLine(), MAX_OUTPUT_LINE_LENGTH);
  }
}

char* Stage::getOutput(int line){
  if(line < 0 or line>=MAX_OUTPUT_LINES){
    return getBox()->getBlankLine();
  }
  return _output[line];
}

char* Stage::getError(int line){
  if(line < 0 or line >=MAX_OUTPUT_LINES){
    return getBox()->getBlankLine();
  }
  return _error[line];
}

int  Stage::getOutputLineCount(){
  return _outputCount;
}

int  Stage::getErrorLineCount(){
  return _errorCount;
}

boolean Stage::doesOutputExist(){
  return _outputCount>0;
}

boolean Stage::doesErrorExist(){
  return _errorCount>0;
}

void Stage::setInput(char* input){
  strncpy(_input, input, MAX_OUTPUT_LINE_LENGTH);
  resetOutput();
  resetError();
}

void Stage::addOutput(char output[MAX_OUTPUT_LINE_LENGTH]){
  // Extra lines will just not be added.  
  // TODO: Maybe thing of something to manage this if so desired
  if(_outputCount<MAX_OUTPUT_LINES){
    strncpy(_output[_outputCount++], output, MAX_OUTPUT_LINE_LENGTH);
  }
}
void Stage::addError(char error[MAX_OUTPUT_LINE_LENGTH]){
  // Extra lines will just not be added.  
  // TODO: Maybe thing of something to manage this if so desired
  if(_outputCount<MAX_OUTPUT_LINES){
    strncpy(_error[_errorCount++], error, MAX_OUTPUT_LINE_LENGTH);
  }
  
}




