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

#include "GameWifi.h"


#define DISPLAY_INFORMATION 0
#define DISPLAY_TITLE_SCREEN 1
#define DISPLAY_USER_SCREEN 2
#define DISPLAY_FLAG 3

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

    char _information1[MAX_OUTPUT_LINE_LENGTH+1];
    char _information2[MAX_OUTPUT_LINE_LENGTH+1];
    char _information3[MAX_OUTPUT_LINE_LENGTH+1];
    char _information4[MAX_OUTPUT_LINE_LENGTH+1];

    char _EMPTY[MAX_OUTPUT_LINE_LENGTH+1];
    char _SEIRAL_BOUNDRY[MAX_OUTPUT_LINE_LENGTH+1];

    void printAddresses();

  protected:
    void updateUserInput(char* line);

  public:
    Box();

    void setup();
    char* initBuffer(char* buffer, char c);
    char* initBuffer(char* buffer, char c, int len);
    char* initAndCopyString(char* buffer, char* string, int max);
    char* getBlankLine();
    
    void setTitle(char* line);
    void setCurrentFlag(int currentFlag, int currentStage);
    void setAttempts(int attempts, int maxAttempts);
    void setCommand(char* line);

    void clearUserInput();
    void clearOutput();
    void writeOutput(char* line1, char* line2);
    void updateStatus(char* line);

    void updateInformation(char* line1);
    void updateInformation(char* line1, char* line2);
    void updateInformation(char* line1, char* line2, char* line3);
    void updateInformation(char* line1, char* line2, char* line3, char* line4);

    byte getButtons(int seconds, int maxButtonsPressed);
    byte getButtons(int seconds, int maxButtonsPressed, boolean useButtons[6], char* labels[6]);
    int getButton();
    int getButton(boolean useButtons[6], char* labels[6]);

    void paintScreen(int screenType);
    void paintScreen(int screenType, boolean clearFirst);
    
    char* getDateTimeStr();

    boolean isWifiConnected();
    
};

#endif

