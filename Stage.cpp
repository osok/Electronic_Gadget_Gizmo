/**
 * Stage.cpp - This is a base class for the Stages included in the Flags.
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */
#include "Stage.h"


Stage::Stage(){
  Serial.print("Stage created,");
}

int Stage::getFlagId(){
  return _flagId;
}

void Stage::setFlagId(int flagId){
  Serial.print("Stage setFlagId = ");
  Serial.println(flagId);
  _flagId = flagId;  
}

int Stage::getStageId(){
  return _stageId;
}

void Stage::setStageId(int stageId){
  Serial.print("Stage setStageId = ");
  Serial.println(stageId);
   _stageId = stageId;
}




