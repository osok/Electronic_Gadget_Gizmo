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



Box::Box(){
  Serial.println("Box interface object created");
  setup();
}

void Box::printAddresses(){
//  Serial.println("-----------------------------------------");
//  Serial.print("Address of _title = ");
//  Serial.println(uint32_t( _title), DEC);
//
//  Serial.print("Address of _currentFlag = ");
//  Serial.println(uint32_t(_currentFlag), DEC);
//
//  Serial.print("Address of _attempts = ");
//  Serial.println(uint32_t(_attempts), DEC);
//
//  Serial.print("Address of _commands = ");
//  Serial.println(uint32_t(_commands), DEC);
//
//  Serial.print("Address of _title = ");
//  Serial.println(uint32_t(_title), DEC);
//
//  Serial.print("Address of _output_1 = ");
//  Serial.println(uint32_t(_output_1), DEC);
//
//  Serial.print("Address of _title = ");
//  Serial.println(uint32_t(_title), DEC);
//
//  Serial.print("Address of _output_2 = ");
//  Serial.println(uint32_t(_output_2), DEC);
//
//  Serial.print("Address of _status = ");
//  Serial.println(uint32_t(_status), DEC);
//
//  Serial.print("Address of _userInput = ");
//  Serial.println(uint32_t(_userInput), DEC);
//
//  Serial.print("Address of _EMPTY = ");
//  Serial.println(uint32_t(_EMPTY), DEC);
//
//  Serial.print("Address of _SEIRAL_BOUNDRY = ");
//  Serial.println(uint32_t(_SEIRAL_BOUNDRY), DEC); 
//  
//  Serial.println("-----------------------------------------");
//

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
  printAddresses();
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
    if( useButtons[0] && digitalRead(BUTTON_0)==LOW){
      strcat(userInputBuffer, labels[0]);
      retVal = 0;
      done = true;
    }else if( useButtons[1] && digitalRead(BUTTON_1)==LOW){
      strcat(userInputBuffer, labels[1]);
      retVal =  1;
      done = true;
    }else if( useButtons[2] && digitalRead(BUTTON_2)==LOW){
      strcat(userInputBuffer, labels[2]);
      retVal =  2;
      done = true;
    }else if( useButtons[3] && digitalRead(BUTTON_3)==LOW){
      strcat(userInputBuffer, labels[3]);
      retVal =  3;
      done = true;
    }else if( useButtons[4] && digitalRead(BUTTON_4)==LOW){
      strcat(userInputBuffer, labels[4]);
      retVal =  4;
      done = true;
    }else if( useButtons[5] && digitalRead(BUTTON_5)==LOW){
      strcat(userInputBuffer, labels[5]);
      retVal =  5;
      done = true;
    } 
    delay(250);
  }
  updateUserInput(userInputBuffer);
  return retVal;
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
  char statusBuffer[MAX_OUTPUT_LINE_LENGTH+1];
  char userInputBuffer[MAX_OUTPUT_LINE_LENGTH+1]; //used to build up buffer
  char userInput[MAX_OUTPUT_LINE_LENGTH+1];       //Used to write
  
  initAndCopyString(userInput, "", MAX_OUTPUT_LINE_LENGTH);
  initAndCopyString(userInputBuffer, "", MAX_OUTPUT_LINE_LENGTH);
  initAndCopyString(statusBuffer, "", MAX_OUTPUT_LINE_LENGTH);

  
  userInputBuffer[0] = '>';
  
  int bit = 0;
   
  while(endTime <  millis()){

    //
    // Check each input
    //
    if( digitalRead(BUTTON_0)==HIGH){
      bit = 0;
      if((val >> 0) & bit){ //First time 
        strcat(userInputBuffer, "A");
      }
      val |= 1 << bit;   // 0000000X
    }
    if( digitalRead(BUTTON_1)==HIGH){
      bit = 1;
      if((val >> 0) & bit){ //First time 
        strcat(userInputBuffer, "B");
      }
      val |= 1 << bit;   // 000000X0
    }
    if( digitalRead(BUTTON_2)==HIGH){
      bit = 2;
      if((val >> 0) & bit){ //First time 
        strcat(userInputBuffer, "C");
      }
      val |= 1 << bit;   // 00000X00
    }
    if( digitalRead(BUTTON_3)==HIGH){
      bit = 3;
      if((val >> 0) & bit){ //First time 
        strcat(userInputBuffer, "D");
      }
      val |= 1 << bit;   // 0000X000
    }
    if( digitalRead(BUTTON_4)==HIGH){
      bit = 4;
      if((val >> 0) & bit){ //First time 
        strcat(userInputBuffer, "E");
      }
      val |= 1 << bit;   // 000X0000
    }
    if( digitalRead(BUTTON_5)==HIGH){
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
    initAndCopyString(userInput, "", MAX_OUTPUT_LINE_LENGTH);

    //
    // Caculate seconds left
    //
    secondsLeft = seconds - ((endTime -  millis())/1000);

    //
    //Update Status
    //
    initAndCopyString(statusBuffer, STATUS_TIME_LEFT, strlen(STATUS_TIME_LEFT));

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

