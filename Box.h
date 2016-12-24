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

#define MAX_OUTPUT_LINES 3

#define MAX_OUTPUT_LINE_LENGTH 12


class Box{
  private:
    char _EMPTY[MAX_OUTPUT_LINE_LENGTH];
    
    int _currentOutPutLine = 0;
    char _title[MAX_OUTPUT_LINE_LENGTH];
    char _output[MAX_OUTPUT_LINES][MAX_OUTPUT_LINE_LENGTH];
    char _userInput[MAX_OUTPUT_LINE_LENGTH];
    char _status[MAX_OUTPUT_LINE_LENGTH];
    
    void setup();
    void updateUserInput(char* line);

  public:
    Box();

    char* createEmptyBuffer();
    char* createBufferFromString(char* string);
    char* getBlankLine();
    
    void setTitle(char* line);
    void clearOutput();
    void writeOutput(char* line);
    void updateStatus(char* line);

    byte getButtons(int seconds);

    void paintScreen();
    
};

#endif

