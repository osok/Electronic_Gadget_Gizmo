/**
 * Stage.h - This is a base class for the Stages included in the Flags.
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#ifndef Stage_h
#define Stage_h

#include <Arduino.h>
#include "Box.h"
#include "Global.h"


class Stage{
  private:
    int _flagId;
    int _stageId;
 
  protected:
    int getFlagId();
    
  public:
    Stage();  
    int getStageId();
    void setFlagId(int flagId);
    void setStageId(int stageId);

    // Must be implemented by implementation class
    virtual void  setup(){};
    virtual boolean  process(){};
    virtual char*  getTitle(){};
    

};



#endif

