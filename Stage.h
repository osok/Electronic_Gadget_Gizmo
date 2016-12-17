/**
 * Stage.h - This is a base class for the Stages included in the Flags.
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#ifndef Stage_h
#define Stage_h

#include <Arduino.h>

// This just seemed a good maximum, I"ll change it if I need more
#define MAX_OUTPUT_LINES 6

// This values are set to the legnths os the LCD screen I'm using
#define MAX_OUTPUT_LINE_LENGTH 12

class Stage{
  private:
    int _id;
    char _EMPTY[MAX_OUTPUT_LINE_LENGTH];
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
    
  public:
    Stage(int id);  
    char* getOutput(int line);
    char* getError(int line);
    boolean doesOutputExist();
    boolean doesErrorExist();
    int getOutputLineCount();
    int getErrorLineCount();
    void setInput(char* input);

    // Must be implemented by implementation class
    boolean virtual process();
    

};



#endif

