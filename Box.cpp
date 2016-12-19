/**
 * Box.h - This represents the inputs and outputs of the Game Box.
 *          It will be mad available to each Stage in order for the 
 *          Stage to interact with the User.
 *          
 *          There should ONLY be one Box in a Game.  It will be created
 *          in the Game 
 *          
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#include "Box.h"

//GPIO Pins, this might need to change to actual pin number
#define BUTTON_0 15   
#define BUTTON_1 2   
#define BUTTON_2 0  
#define BUTTON_3 4  
#define BUTTON_4 5   
#define BUTTON_5 16   


#define TITLE_ROW 0
#define OUPUT_ROW_START 1
#define OUPUT_ROW_STOP 3
#define INPUT_ROW 4
#define STATUS_ROW 5

#define STATUS_TIME_LEFT "Sec Left:"
Box::Box(){
  setup();
}

void Box::setup(){
  
  for(int c = 0; c < MAX_OUTPUT_LINE_LENGTH; c++){
    _EMPTY[c] = ' ';
  }

  pinMode(BUTTON_0, INPUT);
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(BUTTON_3, INPUT);
  pinMode(BUTTON_4, INPUT);
  pinMode(BUTTON_5, INPUT);
}

char* Box::createEmptyBuffer(){
  char buffer[MAX_OUTPUT_LINE_LENGTH];
  strncpy(buffer, _EMPTY, MAX_OUTPUT_LINE_LENGTH);
  return buffer;
}

char* Box::createBufferFromString(char* string){
  char buffer[MAX_OUTPUT_LINE_LENGTH];
  strncpy(buffer, string, MAX_OUTPUT_LINE_LENGTH);
  return buffer;
}

char* Box::getBlankLine(){
  return _EMPTY;
}


void Box::setTitle(char* line){
  //First clear the characters on the line, then write the line
  strncpy(_title, _EMPTY, MAX_OUTPUT_LINE_LENGTH);
  strncpy(_title, line, MAX_OUTPUT_LINE_LENGTH);
}

void Box::clearOutput(){
  _currentOutPutLine = 0;
  for(int i=0; i < MAX_OUTPUT_LINES; i++){
    strncpy(_output[i], _EMPTY, MAX_OUTPUT_LINE_LENGTH);
  }
}

void Box::writeOutput(char* line){
  if(_currentOutPutLine>=0 && _currentOutPutLine < MAX_OUTPUT_LINES){
    //First clear the characters on the line, then write the line
    strncpy(_output[_currentOutPutLine], _EMPTY, MAX_OUTPUT_LINE_LENGTH);
    strncpy(_output[_currentOutPutLine++], line, MAX_OUTPUT_LINE_LENGTH);
  }
}

void Box::updateStatus(char* line){
  //First clear the characters on the line, then write the line
  strncpy(_status, _EMPTY, MAX_OUTPUT_LINE_LENGTH);
  strncpy(_status, line, MAX_OUTPUT_LINE_LENGTH);
}

void Box::updateUserInput(char* line){
  //First clear the characters on the line, then write the line
  strncpy(_userInput, _EMPTY, MAX_OUTPUT_LINE_LENGTH);
  strncpy(_userInput, line, MAX_OUTPUT_LINE_LENGTH);
}

void Box::paintScreen(){
  
}

byte Box::getButtons(int seconds){
  // Button 0  - A
  // Button 1  - B
  // Button 2  - C
  // Button 3  - D
  // Button 4  - E
  // Button 5  - Key

  byte val = 0;
  unsigned long  startTime =   millis();
  unsigned long  endTime =   startTime + (seconds * 1000);
  
  char secondsStringBuf[5];
  
  int secondsLeft = seconds;
  char statusBuffer[MAX_OUTPUT_LINE_LENGTH];
  char userInputBuffer[MAX_OUTPUT_LINE_LENGTH]; //used to build up buffer
  char userInput[MAX_OUTPUT_LINE_LENGTH];       // Used to write
  
  strncpy(userInput, createEmptyBuffer(), MAX_OUTPUT_LINE_LENGTH);
  userInputBuffer[0] = '>';
  
  int bit = 0;
   
  while(endTime <  millis()){

    //
    // Check each input
    //
    if( digitalRead(BUTTON_0)){
      bit = 0;
      if((val >> 0) & bit){ //First time 
        strcat(userInputBuffer, "A");
      }
      val |= 1 << bit;   // 0000000X
    }
    if( digitalRead(BUTTON_1)){
      bit = 1;
      if((val >> 0) & bit){ //First time 
        strcat(userInputBuffer, "B");
      }
      val |= 1 << bit;   // 000000X0
    }
    if( digitalRead(BUTTON_2)){
      bit = 2;
      if((val >> 0) & bit){ //First time 
        strcat(userInputBuffer, "C");
      }
      val |= 1 << bit;   // 00000X00
    }
    if( digitalRead(BUTTON_3)){
      bit = 3;
      if((val >> 0) & bit){ //First time 
        strcat(userInputBuffer, "D");
      }
      val |= 1 << bit;   // 0000X000
    }
    if( digitalRead(BUTTON_4)){
      bit = 4;
      if((val >> 0) & bit){ //First time 
        strcat(userInputBuffer, "E");
      }
      val |= 1 << bit;   // 000X0000
    }
    if( digitalRead(BUTTON_5)){
      bit = 5;
      if((val >> 0) & bit){ //First time 
        strcat(userInputBuffer, "K");
      }
      val |= 1 << bit;   // 00X00000
    }

    //
    // End time if user input Max input reached
    //
    if(strlen(userInputBuffer) >= MAX_OUTPUT_LINE_LENGTH-2){
      endTime =  millis();
    }
    
    //
    // Update User Input Line
    //
    strncpy(userInput, userInputBuffer, MAX_OUTPUT_LINE_LENGTH);

    //
    // Caculate seconds left
    //
    secondsLeft = seconds - ((endTime -  millis())/1000);

    //
    //Update Status
    //
    strcpy(statusBuffer, STATUS_TIME_LEFT);
    if(secondsLeft <10){
      strcat(statusBuffer, "  ");
    }else{
      strcat(statusBuffer, " ");
    }
    itoa(secondsLeft, secondsStringBuf , 10);
    
    strcat(statusBuffer, secondsStringBuf);
    updateStatus(statusBuffer);

  }

  return val;

}

