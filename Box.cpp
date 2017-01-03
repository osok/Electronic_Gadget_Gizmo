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
#include "Global.h"



Box::Box(){
  Serial.println("Box interface object created");
  setup();
}

void Box::setup(){
  Serial.println("Box interface object setup");

  initBuffer(_SEIRAL_BOUNDRY, '=');
  initBuffer(_EMPTY, ' ');
  
  
  pinMode(BUTTON_0, INPUT);
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(BUTTON_3, INPUT);
  pinMode(BUTTON_4, INPUT);
  pinMode(BUTTON_5, INPUT);
}

char* Box::initBuffer(char* buffer, char c){
//  Serial.println("initBuffer");
  int i = 0;
  for(; i < MAX_OUTPUT_LINE_LENGTH; i++){
    buffer[i] = c;
  }
  buffer[i] = '\0';
  return buffer;
}

char* Box::initAndCopyString(char* buffer, char* string, int max){
//  Serial.println("initAndCopyString");
  // This will ensure the null terminator exists at the end
  if(max > MAX_OUTPUT_LINE_LENGTH){
    max = MAX_OUTPUT_LINE_LENGTH;
  }
  
  if(max > strlen(string)){
    max = strlen(string);
  }
  
  buffer = initBuffer(buffer, '\0');
  strncpy(buffer, string, max);
  return buffer;
}

char* Box::getBlankLine(){
  return _EMPTY;
}


void Box::setTitle(char* line){
//  Serial.println("setTitle");

  initAndCopyString(_title, line, MAX_OUTPUT_LINE_LENGTH);
}

void Box::setCurrentFlag(int currentFlag, int currentStage){
//  Serial.println("setCurrentFlag");
  char flag[3];
  char stage[3];

  char num[10];
  int addr;

  initAndCopyString(_currentFlag, "Flag / Stage : ", MAX_OUTPUT_LINE_LENGTH - 5);
 
  if(currentFlag < 10){
    strcat(_currentFlag, itoa(currentFlag+1, flag, 10));
  }else{  
    strcat(_currentFlag, "?");
  }  
  
  strcat(_currentFlag, " / ");
  
  if(currentStage < 10){
    strcat(_currentFlag, itoa(currentStage+1, stage, 10));
  }else{  
    strcat(_currentFlag, "?");
  }

}

void Box::setAttempts(int attempts, int maxAttempts){
//  Serial.println("setAttempts");
  char num[4];

  initAndCopyString(_attempts, "Attempts : ", MAX_OUTPUT_LINE_LENGTH - 6);

  if(attempts < 100){
    strcat(_attempts, itoa(attempts, num, 10));
  }else{  
    strcat(_attempts, "??");
  }  
  strcat(_attempts, " of ");
  
  if(maxAttempts < 100){
    strcat(_attempts, itoa(maxAttempts, num, 10));
  }else{  
    strcat(_attempts, "??");
  }  
   
 
}

void Box::setCommand(char* line){
//  Serial.println("setCommand");
  initAndCopyString(_commands, line, MAX_OUTPUT_LINE_LENGTH);

}

void Box::clearOutput(){
//  Serial.println("clearOutput");
  _currentOutPutLine = 0;
  initAndCopyString(_output_1, "", MAX_OUTPUT_LINE_LENGTH);
  initAndCopyString(_output_2, "", MAX_OUTPUT_LINE_LENGTH);
}

void Box::writeOutput(char* line1, char* line2){
//  Serial.println("writeOutput");
  initAndCopyString(_output_1, line1, MAX_OUTPUT_LINE_LENGTH);
  initAndCopyString(_output_2, line2, MAX_OUTPUT_LINE_LENGTH);
}

void Box::updateStatus(char* line){
//  Serial.println("updateStatus");
  initAndCopyString(_status, line, MAX_OUTPUT_LINE_LENGTH);
}

void Box::updateUserInput(char* line){
  initAndCopyString(_userInput, line, MAX_OUTPUT_LINE_LENGTH);
}

void Box::clearUserInput(){
  updateUserInput("");
}

void Box::paintScreen(boolean titleScreen){
  
  Serial.println("");
  
  if(titleScreen){
    Serial.println("Painting Title Screen");
    Serial.println(_SEIRAL_BOUNDRY);
    Serial.println(_title);
    Serial.println(_currentFlag);
    Serial.println(_attempts);
    Serial.println(_commands);
    Serial.println(_SEIRAL_BOUNDRY);
  }else{
    Serial.println("Painting User Screen");
    Serial.println(_SEIRAL_BOUNDRY);
    Serial.println(_output_1);
    Serial.println(_output_2);
    Serial.println(_status);
    Serial.println(_userInput);
    Serial.println(_SEIRAL_BOUNDRY);
  }
  
  Serial.println("");
  
}
int Box::getButton(){
  boolean useButtons[] = {true,true,true,true,true,false};
  char* labels[] = {"A","B","C","D","E","Key"};
  return getButton(useButtons, labels);
}
  

int Box::getButton(boolean useButtons[6], char* labels[6]){
  char userInputBuffer[MAX_OUTPUT_LINE_LENGTH+1]; 
  initAndCopyString(userInputBuffer, "", MAX_OUTPUT_LINE_LENGTH);
  updateUserInput(userInputBuffer);
  
  int retVal = -1;
  boolean done = false;
  
  while(!done){
    //
    // Check each input
    //
    if( useButtons[0] && (digitalRead(BUTTON_0)==LOW)){
      strcat(userInputBuffer, labels[0]);
      retVal = 0;
      done = true;
    }else if( useButtons[1] && (digitalRead(BUTTON_1)==LOW)){
      strcat(userInputBuffer, labels[1]);
      retVal =  1;
      done = true;
    }else if( useButtons[2] && (digitalRead(BUTTON_2)==LOW)){
      strcat(userInputBuffer, labels[2]);
      retVal =  2;
      done = true;
    }else if( useButtons[3] && (digitalRead(BUTTON_3)==LOW)){
      strcat(userInputBuffer, labels[3]);
      retVal =  3;
      done = true;
    }else if( useButtons[4] && (digitalRead(BUTTON_4)==LOW)){
      strcat(userInputBuffer, labels[4]);
      retVal =  4;
      done = true;
    }else if( useButtons[5] && (digitalRead(BUTTON_5)==LOW)){
      strcat(userInputBuffer, labels[5]);
      retVal =  5;
      done = true;
    } 
    delay(250);
  }
  updateUserInput(userInputBuffer);
  return retVal;
}

byte Box::getButtons(int seconds, int maxButtonsPressed){
  boolean useButtons[] = {true,true,true,true,true,false};
  char* labels[] = {"A","B","C","D","E","Key"};
  return getButtons(seconds, maxButtonsPressed, useButtons, labels);
  
}

byte Box::getButtons(int seconds, int maxButtonsPressed, boolean useButtons[6], char* labels[6]){
  Serial.println("getButtons called");

  if(seconds > 999){
    seconds = 999;
  }
  if(seconds < 0){
    seconds = 0;
  }
  
  Serial.print("seconds = ");
  Serial.println(seconds);

  byte val = 0;
  unsigned long  endTime = millis() + (seconds * 1000);
  Serial.print("End Time = ");
  Serial.println(endTime);
  Serial.print("Current Time = ");
  Serial.println( millis());
  
  char secondsStringBuf[5];
  
  int secondsLeft = seconds;
  char statusBuffer[MAX_OUTPUT_LINE_LENGTH+1];
  char userInputBuffer[MAX_OUTPUT_LINE_LENGTH+1]; //used to build up buffer
  
  initAndCopyString(userInputBuffer, "", MAX_OUTPUT_LINE_LENGTH);
  initAndCopyString(statusBuffer, "", MAX_OUTPUT_LINE_LENGTH);

  updateUserInput(userInputBuffer);
  
  itoa(secondsLeft, secondsStringBuf , 10);
  initAndCopyString(statusBuffer, secondsStringBuf, MAX_OUTPUT_LINE_LENGTH);
  strcat(statusBuffer, "s left to select");
  updateStatus(statusBuffer);

  paintScreen(false);
 
  int bit = 0;
  boolean pressed[] = {false,false,false,false,false,false};
  char pressedStr[7] = "      ";
  
  while(endTime >  millis()){

    if( !pressed[0] && useButtons[0] && (digitalRead(BUTTON_0)==LOW)){
      bit = 0;
      strcat(userInputBuffer, labels[bit]);
      pressed[bit] = true;
      val += 1;
    }else if( !pressed[1] && useButtons[1] && (digitalRead(BUTTON_1)==LOW)){
      bit = 1;
      strcat(userInputBuffer, labels[bit]);
      pressed[bit] = true;
      val += 2;
    }else if( !pressed[2] && useButtons[2] && (digitalRead(BUTTON_2)==LOW)){
      bit = 2;
      strcat(userInputBuffer, labels[bit]);
      pressed[bit] = true;
      val += 4;
    }else if( !pressed[3] && useButtons[3] && (digitalRead(BUTTON_3)==LOW)){
      bit = 3;
      strcat(userInputBuffer, labels[bit]);
      pressed[bit] = true;
      val += 8;
    }else if( !pressed[4] && useButtons[4] && (digitalRead(BUTTON_4)==LOW)){
      bit = 4;
      strcat(userInputBuffer, labels[bit]);
      pressed[bit] = true;
      val += 16;
    }else if( !pressed[5] && useButtons[5] && (digitalRead(BUTTON_5)==LOW)){
      // This is for the key lock so not often used
      bit = 5;
      strcat(userInputBuffer, labels[bit]);
      pressed[bit] = true;
      val += 32;
    }

    Serial.print("Current Val = ");
    Serial.println(val);

    Serial.print("Pressed Array = ");
    for(int i=0; i<6;i++){
      if(pressed[i]){
        Serial.print("Y");
      }else{
        Serial.print("N");
      }
    }
    Serial.println("");



    //
    // End time if user input Max input reached
    //
    if(strlen(userInputBuffer) >= maxButtonsPressed){
      endTime =  millis();
    }


    //
    // Sort the user Input and set it for display
    //
    sortString(userInputBuffer);
    updateUserInput(userInputBuffer);
    Serial.print("Current UserInput = ");
    Serial.println(userInputBuffer);
    
     
     //
    // Caculate seconds left
    //
    secondsLeft = (endTime -  millis())/1000;

    //
    //Update Status
    //
    itoa(secondsLeft, secondsStringBuf , 10);
    initAndCopyString(statusBuffer, secondsStringBuf, MAX_OUTPUT_LINE_LENGTH);
    strcat(statusBuffer, "s left to select");
    updateStatus(statusBuffer);
    paintScreen(false);
    delay(500);
  }

  return val;

}

