#include "Global.h"

const char* characterSet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";



//
// GLOBAL VARIABLES ARE BAD JU-JU
// But so are pointer references that keep moving (don't ask)
//
Box  _box;


void printAddress(char* description, void *ptr){
//  Serial.print("*****  ");
//  Serial.print(description);
//  Serial.print(" = [");
//  Serial.print(uint32_t(ptr), DEC);
//  Serial.println("]  *****");
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



/**
 * Copied from: http://www.programmingsimplified.com/c/source-code/c-program-sort-string
 * 
 */
void sortString(char *s){
   int c, d = 0, length;
   char *pointer, *result, ch;
 
   length = strlen(s);
 
   result = (char*)malloc(length+1);
 
   pointer = s;
 
   for ( ch = 'A' ; ch <= 'Z' ; ch++ )
   {
      for ( c = 0 ; c < length ; c++ )
      {
         if ( *pointer == ch )
         {
            *(result+d) = *pointer;
            d++;
         }
         pointer++;
      }
      pointer = s;
   }
   *(result+d) = '\0';
 
   strcpy(s, result);
   free(result);
}
