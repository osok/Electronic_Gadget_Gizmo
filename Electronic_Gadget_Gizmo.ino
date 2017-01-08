
#include "Global.h"
#include "Game.h"




Game _game;



void setup() {
  
  Serial.begin(115200);
  Serial.println(""); 
  Serial.println("Booting");

  randomSeed(analogRead(0));
  
  getConfig()->setup();
  getBox()->setup();
  
  _game.setup();
  
}

void loop() {
  _game.run();

}
