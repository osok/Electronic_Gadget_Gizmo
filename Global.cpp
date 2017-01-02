#include "Global.h"

const char* characterSet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";



//
// GLOBAL VARIABLES ARE BAD JU-JU
// But so are pointer references that keep moving (don't ask)
//
Box  _box;


void printAddress(char* description, void *ptr){
  Serial.print("*****  ");
  Serial.print(description);
  Serial.print(" = [");
  Serial.print(uint32_t(ptr), DEC);
  Serial.println("]  *****");
}

Box* getBox(){
  printAddress("In getBox() Method",&_box); 
  return &_box;
}


char* getRandomString(int length){
  char buffer[length+1];
  int upper = strlen(characterSet);
  int i = 0;
  
  for( ;i < length;i++){
    buffer[i] = characterSet[getRandomNumber(0,upper)];
  }
  buffer[i] = 0;
}

int getRandomNumber(int lower, int upper){
  int num = random((upper - lower));
  return (num + lower);
}

void wait(int seconds){
  Serial.println("");
  Serial.print("Waiting (");
  Serial.print(seconds);
  Serial.print(" seconds) ");
  for(int i=0; i<seconds; i++){
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  
}
