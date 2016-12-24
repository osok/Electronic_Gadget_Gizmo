/**
 * Game.h - This is the main class for the game, the INO will create this class
 *          then interact with it to manage the lifecycle of the game.
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#ifndef Game_h
#define Game_h

#include <Arduino.h>
#include "Box.h"
#include "Flag.h"

#define FLAG_ONE 1
#define FLAG_TWO 2
#define FLAG_THREE 3
#define FLAG_FOUR 4
#define FLAG_FIVE 5
#define FLAG_COUNT 5

class Game{
  private:
    Box _box;   
    Flag* _flags[FLAG_COUNT];
    int _currentFlagId = 0;

  protected:
    void addFlag(int flagId, Flag* flag);
    Box* getBox();
    Flag* getCurrentFlag();
   
  public:
    Game();
    void setup();
    void run();
    void setCurrentFlag(int flagId);
    void setCurrentStage(int stageId);
    void setCurrentErrors(int errorCount);

};



#endif

