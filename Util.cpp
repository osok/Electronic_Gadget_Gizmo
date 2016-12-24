
#import "Util.h"

Util::Util(){
  randomSeed(millis());
}

char* Util::getRandomString(int length){
  char buffer[length+1];
  int upper = strlen(characterSet);
  int i = 0;
  
  for( ;i < length;i++){
    buffer[i] = characterSet[getRandomNumber(0,upper)];
  }
  buffer[i] = 0;
}

int Util::getRandomNumber(int lower, int upper){
  int num = random((upper - lower));
  return (num + lower);
}

