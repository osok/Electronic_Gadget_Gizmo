/**
 * Stage.h - This is a base class for the Stages included in the Flags.
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#ifndef Stage_h
#define Stage_h

#include <Arduino.h>
#include "Box.h"


class Stage{
  private:
    int _id;
    Box* _box;
    char _output[MAX_OUTPUT_LINES][MAX_OUTPUT_LINE_LENGTH];
    char _error[MAX_OUTPUT_LINES][MAX_OUTPUT_LINE_LENGTH];
    char _input[MAX_OUTPUT_LINE_LENGTH];
    int _outputCount = 0;
    int _errorCount = 0;

    void resetOutput();
    void resetError();

  protected:
    void addOutput(char output[MAX_OUTPUT_LINE_LENGTH]);
    void addError(char output[MAX_OUTPUT_LINE_LENGTH]);
    Box* getBox();
    
  public:
    Stage(int id, Box* box);  
    char* getOutput(int line);
    char* getError(int line);
    boolean doesOutputExist();
    boolean doesErrorExist();
    int getOutputLineCount();
    int getErrorLineCount();
    void setInput(char* input);

    // Must be implemented by implementation class
    void virtual setup();
    boolean virtual process();
    

};



#endif

