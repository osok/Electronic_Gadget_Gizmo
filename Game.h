/**
 * Game.h - This is the main class for the game, the INO will create this class
 *          then interact with it to manage the lifecycle of the game.
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#ifndef Game_h
#define Game_h

#include <Arduino.h>
#include "Global.h"
#include "Box.h"
#include "WebServer.h"
#include "FlagOne.h"

 
class Game{
  private:
    Flag* _flags[FLAG_COUNT];
    FlagOne flag1;
    FlagOne flag2;
    FlagOne flag3;
    FlagOne flag4;
    FlagOne flag5;
    WebServer _webServer;

    int _currentFlagId = 0;
    boolean gameFinished();
    void addFlag(int flagId, Flag* flag);
    void flagCompleted();
    void flagFailed();
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

