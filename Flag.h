/**
 * Flag.h - This is a base class for the Flags.
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#ifndef Flag_h
#define Flag_h

#include <Arduino.h>
#include "Stage.h"

#define FLAG_NOT_COMPLETE "Keep Trying"

#define STAGE_ID_ONE 0
#define STAGE_ID_TWO 1
#define STAGE_ID_THREE 2
#define MAX_STAGE_COUNT 3

class Flag{
  private:
    int _id = 0;
    int _failedAttempts = 0;
    int _failedAttemptMax = 10;
    Stage* _stage[MAX_STAGE_COUNT];
    int _currentStage = 0;

  protected:
    void changeMaxFailedAttempts(int max);
    void addStage(int stageId, Stage* stage);

    //Must be defined in implementing class
    void virtual setupStages();

  public:
    Flag(int id);
    void addFailedAttempt();
    boolean tooManyFailedAttempts();
    Stage* getCurrentStage();
    void stageCompleted();
    boolean allStagesComplete();
    char* getFlag();

};



#endif

