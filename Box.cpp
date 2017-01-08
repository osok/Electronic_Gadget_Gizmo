#include <LiquidCrystal_I2C.h>

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
//#include <Wire.h>         //I2C library
//#include <RtcDS3231.h>    //RTC library


LiquidCrystal_I2C lcd(0x27,20,4);
//RtcDS3231<TwoWire> realTimeClock(Wire);
GameWifi _gameWifi;

Box::Box(){}

void Box::setup(){
  Serial.println("Box interface object setup");

  lcd.init();
  lcd.begin(20,4,LCD_5x8DOTS);
  lcd.backlight();
  lcd.noCursor();
  lcd.noBlink();

  initBuffer(_SEIRAL_BOUNDRY, '=');
  initBuffer(_EMPTY, ' ');
  
  
  pinMode(BUTTON_0, INPUT);
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(BUTTON_3, INPUT);
  pinMode(BUTTON_4, INPUT);
  pinMode(BUTTON_5, INPUT);

  _gameWifi.setup();

  

}

boolean  Box::isWifiConnected(){
  return _gameWifi.isWifiConnected();
}

char* Box::initBuffer(char* buffer, char c){
  return initBuffer(buffer, c, MAX_OUTPUT_LINE_LENGTH);
}
char* Box::initBuffer(char* buffer, char c, int len){
//  Serial.println("initBuffer");
  int i = 0;
  for(; i < len; i++){
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

void Box::updateInformation(char* line1){
  updateInformation(line1, "", "", "");
}
void Box::updateInformation(char* line1, char* line2){
  updateInformation(line1, line2, "", "");
}
void Box::updateInformation(char* line1, char* line2, char* line3){
  updateInformation(line1, line2, line3, "");
}
void Box::updateInformation(char* line1, char* line2, char* line3, char* line4){
  if(strlen(line1) > 0 ){
    Serial.println(line1);
  }
  if(strlen(line2) > 0 ){
    Serial.println(line2);
  }
  if(strlen(line3) > 0 ){
    Serial.println(line3);
  }
  if(strlen(line4) > 0 ){
    Serial.println(line4);
  }
  initAndCopyString(_information1, line1, MAX_OUTPUT_LINE_LENGTH);
  initAndCopyString(_information2, line2, MAX_OUTPUT_LINE_LENGTH);
  initAndCopyString(_information3, line3, MAX_OUTPUT_LINE_LENGTH);
  initAndCopyString(_information4, line4, MAX_OUTPUT_LINE_LENGTH);
  paintScreen(DISPLAY_INFORMATION);
}

void paintLCD(char* line1, char* line2, char* line3, char* line4, boolean clearFirst){
  lcd.backlight();
  if(clearFirst){
    lcd.clear();
  }
  lcd.home();
  lcd.noCursor();
  lcd.noBlink();
  
  if(strlen(line1) > 0 ){
    lcd.setCursor(0,0);
    lcd.print(line1);
  }
  if(strlen(line2) > 0 ){
    lcd.setCursor(0,1);
    lcd.print(line2);
  }
  if(strlen(line3) > 0 ){
    lcd.setCursor(0,2);
    lcd.print(line3);
  }
  if(strlen(line4) > 0 ){
    lcd.setCursor(0,3);
    lcd.print(line4);
  }

}



void Box::paintScreen(int screenType){
  paintScreen(screenType, true);
}
void Box::paintScreen(int screenType, boolean clearFirst){
  
//  Serial.println("");

  switch(screenType){
     case DISPLAY_INFORMATION :
      paintLCD(_information1,_information2,_information3,_information4, clearFirst);
      break;
  
    case DISPLAY_TITLE_SCREEN :
//      Serial.println("Painting Title Screen");
//      Serial.println(_SEIRAL_BOUNDRY);
//      Serial.println(_title);
//      Serial.println(_currentFlag);
//      Serial.println(_attempts);
//      Serial.println(_commands);
//      Serial.println(_SEIRAL_BOUNDRY);
      paintLCD(_title,_currentFlag, _attempts, _commands, clearFirst);
      break;
  
    case DISPLAY_USER_SCREEN :
//      Serial.println("Painting User Screen");
//      Serial.println(_SEIRAL_BOUNDRY);
//      Serial.println(_output_1);
//      Serial.println(_output_2);
//      Serial.println(_status);
//      Serial.println(_userInput);
//      Serial.println(_SEIRAL_BOUNDRY);
      paintLCD(_output_1,_output_2, _status, _userInput, clearFirst);
      break;
  
    case DISPLAY_FLAG :
      paintLCD("Congratulations you","Found a new flag","[Flag Goes here]","", clearFirst);
      break;
  
  }
  
//  Serial.println("");
  
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
//  Serial.println("getButtons called");

  if(seconds > 999){
    seconds = 999;
  }
  if(seconds < 0){
    seconds = 0;
  }
  
//  Serial.print("seconds = ");
//  Serial.println(seconds);

  byte val = 0;
  unsigned long  endTime = millis() + (seconds * 1000);
//  Serial.print("End Time = ");
//  Serial.println(endTime);
//  Serial.print("Current Time = ");
//  Serial.println( millis());
  
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

  paintScreen(DISPLAY_USER_SCREEN);
 
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

//    Serial.print("Current Val = ");
//    Serial.println(val);
//
//    Serial.print("Pressed Array = ");
//    for(int i=0; i<6;i++){
//      if(pressed[i]){
//        Serial.print("Y");
//      }else{
//        Serial.print("N");
//      }
//    }
//    Serial.println("");



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
//    Serial.print("Current UserInput = ");
//    Serial.println(userInputBuffer);
//    
     
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
    paintScreen(DISPLAY_USER_SCREEN, false);
    delay(250);
  }

  return val;

}


char* Box::getDateTimeStr(){
  char str[18];   //declare a string as an array of chars  
//  RtcDateTime currentTime = realTimeClock.GetDateTime();
//  
//  initBuffer(str, '\0', 18);
//  
//  sprintf(str, "%d/%d/%d %d:%d:%d",    
//                  currentTime.Year(),                    
//                  currentTime.Month(),                
//                  currentTime.Day(),                  
//                  currentTime.Hour(),                 
//                  currentTime.Minute(),             
//                  currentTime.Second());
//  
  return str; 
}

