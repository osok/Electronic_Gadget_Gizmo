/**
 * Stage.h - This is a base class for the Stages included in the Flags.
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */
#include "Stage.h"


Stage::Stage(int id){
  _id = id;  

  for(int c = 0; c < MAX_OUTPUT_LINE_LENGTH; c++){
    _EMPTY[c] = ' ';
  }
}

void Stage::resetOutput(){
  _outputCount = 0;
  for(int r = 0; r < MAX_OUTPUT_LINE_LENGTH; r++){
    strncpy(_output[r], _EMPTY, MAX_OUTPUT_LINE_LENGTH);
  } 
}

void Stage::resetError(){
  _errorCount = 0;
  for(int r = 0; r < MAX_OUTPUT_LINE_LENGTH; r++){
    strncpy(_error[r], _EMPTY, MAX_OUTPUT_LINE_LENGTH);
  }
}

char* Stage::getOutput(int line){
  if(line < 0 or line>=MAX_OUTPUT_LINES){
    return _EMPTY;
  }
  return _output[line];
}

char* Stage::getError(int line){
  if(line < 0 or line >=MAX_OUTPUT_LINES){
    return _EMPTY;
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



