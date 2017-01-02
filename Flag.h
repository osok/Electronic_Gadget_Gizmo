/**
 * Flag.h - This is a base class for the Flags.
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#ifndef Flag_h
#define Flag_h

#include <Arduino.h>
#include "Stage.h"
#include "Box.h"
#include "Global.h"

#define FLAG_NOT_COMPLETE "Keep Trying"


class Flag{
  private:
    Stage* _stage[MAX_STAGE_COUNT];
    int _flagId = 0;
    int _failedAttempts = 0;
    int _failedAttemptMax = 10;
    int _currentStage = 0;

  protected:
    void changeMaxFailedAttempts(int max);
    void addStage(int stageId, Stage* stage);
    int getFlagId();
    void stageCompleted();
    void addFailedAttempt();

  public:
    Flag();
    void setFlagId(int flagId);
    boolean tooManyFailedAttempts();
    Stage* getCurrentStage();
    void setCurrentStageId(int stageId);
    boolean allStagesComplete();
    char* getFlagString();
    boolean  process();
    void setFailedAttempts(int attempts);

     //Must be defined in implementing class  True is completed, False is Failed
    void virtual setup(); 
};



#endif

