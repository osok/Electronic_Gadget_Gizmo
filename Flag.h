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

#define FLAG_NOT_COMPLETE "Keep Trying"

#define STAGE_ID_ONE 0
#define STAGE_ID_TWO 1
#define STAGE_ID_THREE 2
#define MAX_STAGE_COUNT 3

class Flag{
  private:
    int _id = 0;
    Box* _box;
    int _failedAttempts = 0;
    int _failedAttemptMax = 10;
    Stage* _stage[MAX_STAGE_COUNT];
    int _currentStage = 0;

  protected:
    void changeMaxFailedAttempts(int max);
    void addStage(int stageId, Stage* stage);
    void stageCompleted();
    void addFailedAttempt();
    Box* getBox();

  public:
    Flag(int id, Box* box);
    boolean tooManyFailedAttempts();
    Stage* getCurrentStage();
    void setCurrentStageId(int stageId);
    boolean allStagesComplete();
    char* getFlagString();

     //Must be defined in implementing class  True is completed, False is Failed
    void virtual setup();
    boolean virtual process();

};



#endif

