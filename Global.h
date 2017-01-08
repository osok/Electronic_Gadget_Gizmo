/**
 * Global.h - This is where anything global goes, try NOT to put too much here
 * 
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#ifndef Global_h
#define Global_h

#include "Box.h"
#include "Config.h"

#define FLAG_ONE 0
#define FLAG_TWO 1
#define FLAG_THREE 2
#define FLAG_FOUR 3
#define FLAG_FIVE 4

#define FLAG_COUNT 5

#define STAGE_ID_ONE 0
#define STAGE_ID_TWO 1
#define STAGE_ID_THREE 2
#define MAX_STAGE_COUNT 3

#define TITLE_SCREEN_SHOW_SECONDS 5

#define NEW(x,y) *(x=(y*)malloc(sizeof(y)))=y

Box* getBox();
Config* getConfig();

void printAddress(char* description, void* ptr);

char* getRandomString(int length);
int getRandomNumber(int lower, int upper);
void wait(int seconds);
void sortString(char *s);


#endif

