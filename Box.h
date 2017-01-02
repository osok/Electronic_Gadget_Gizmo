/**
 * Box.h - This represents the inputs and outputs of the Game Box.
 *          It will be mad available to each Stage in order for the 
 *          Stage to interact with the User.
 *          
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#ifndef Box_h
#define Box_h

#include <Arduino.h>

// The defines here cannot go into global because there would be a circular reference

//GPIO Pins, this might need to change to actual pin number
#define BUTTON_0 0  
#define BUTTON_1 2   
#define BUTTON_2 14  
#define BUTTON_3 12  
#define BUTTON_4 13   
#define BUTTON_5 15   

#define ROW_COUNT 4
#define COL_COUNT 20

#define OUPUT_ROW_START 0
#define OUPUT_ROW_STOP 1
#define STATUS_ROW 2
#define INPUT_ROW 3

#define TITLE_ROW 0
#define FLAG_NUMBER_ROW 1
#define FAILED_ATTEMPT_ROW 2
#define COMMAND_ROW 3


#define MAX_OUTPUT_LINES 2

#define MAX_OUTPUT_LINE_LENGTH 20

#define STATUS_TIME_LEFT "Seconds Left: "
#define CURRENT_FLAG     "Current Flag: "
#define ATTEMPTS         "Attempts    : "


class Box{
  private:

    int _currentOutPutLine = 0;
    

    char _title[MAX_OUTPUT_LINE_LENGTH+1];
    char _currentFlag[MAX_OUTPUT_LINE_LENGTH+1];
    char _attempts[MAX_OUTPUT_LINE_LENGTH+1];
    char _commands[MAX_OUTPUT_LINE_LENGTH+1];
    
    char _output_1[MAX_OUTPUT_LINE_LENGTH+1];
    char _output_2[MAX_OUTPUT_LINE_LENGTH+1];
    char _status[MAX_OUTPUT_LINE_LENGTH+1];
    char _userInput[MAX_OUTPUT_LINE_LENGTH+1];

    char _EMPTY[MAX_OUTPUT_LINE_LENGTH+1];
    char _SEIRAL_BOUNDRY[MAX_OUTPUT_LINE_LENGTH+1];

    char xxx[1000];
    void printAddresses();

  protected:
    void updateUserInput(char* line);

  public:
    Box();

    void setup();
    char* initBuffer(char* buffer, char c);
    char* initAndCopyString(char* buffer, char* string, int max);
    char* getBlankLine();
    
    void setTitle(char* line);
    void setCurrentFlag(int currentFlag, int currentStage);
    void setAttempts(int attempts);
    void setCommand(char* line);

    void clearOutput();
    void writeOutput(char* line1, char* line2);
    void updateStatus(char* line);

    byte getButtons(int seconds);
    int getButton();

    void paintScreen(boolean titleScreen);
    
};

#endif

