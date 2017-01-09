/**
 * Config.h - This is where all the config file stuff happens
 * 
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#include "Config.h"

Config::Config(){
  Serial.println("Configuration interface object created");
  
}

void Config::setup(){
  Serial.println("Configuration interface object setting up...");
  readData();
  
}


void Config::readData(){
  if(SPIFFS.exists(CONFIG_FILE_NAME)){
    String line;
    File f = SPIFFS.open(CONFIG_FILE_NAME, "r");
    line = f.readStringUntil('\n');
    strncpy(_configData.ssid, line.c_str(), 255);
    line = f.readStringUntil('\n');
    strncpy(_configData.password, line.c_str(), 255);
    line = f.readStringUntil('\n');
    strncpy(_configData.username, line.c_str(), 255);
    line = f.readStringUntil('\n');
    strncpy(_configData.email, line.c_str(), 255);
    line = f.readStringUntil('\n');
    strncpy(_configData.flag1, line.c_str(), 255);
    line = f.readStringUntil('\n');
    strncpy(_configData.flag2, line.c_str(), 255);
    line = f.readStringUntil('\n');
    strncpy(_configData.flag3, line.c_str(), 255);
    line = f.readStringUntil('\n');
    strncpy(_configData.flag4, line.c_str(), 255);
    line = f.readStringUntil('\n');
    strncpy(_configData.clientPrivateKey, line.c_str(), 2048);
    line = f.readStringUntil('\n');
    strncpy(_configData.clientPublicKey, line.c_str(), 2048);
    line = f.readStringUntil('\n');
    strncpy(_configData.serverPrivateKey, line.c_str(), 2048);
    line = f.readStringUntil('\n');
    strncpy(_configData.serverPublicKey, line.c_str(), 2048);
    line = f.readStringUntil('\n');
    _configData.currentFlag = atoi(line.c_str());
    line = f.readStringUntil('\n');
    _configData.currentState = atoi(line.c_str());
    
    f.close();
  }else{
      writeData();
  }
}


void Config::writeData(){
  File configFile = SPIFFS.open(CONFIG_FILE_NAME, "w+");
  char num[5];
 
  configFile.println(_configData.ssid);
  configFile.println(_configData.password);
  configFile.println(_configData.username);
  configFile.println(_configData.email);
  configFile.println(_configData.flag1);
  configFile.println(_configData.flag2);
  configFile.println(_configData.flag3);
  configFile.println(_configData.flag4);
  configFile.println(_configData.clientPrivateKey);
  configFile.println(_configData.clientPublicKey);
  configFile.println(_configData.serverPrivateKey);
  configFile.println(_configData.serverPublicKey);
  configFile.println(itoa(_configData.currentFlag, num, 10));
  configFile.println(itoa(_configData.currentState, num, 10));
 
  configFile.close(); 
}

char* Config::getSSID(){
  return _configData.ssid;
}
void Config::setSSID(char* val){
  strncpy(_configData.ssid, val, 255);
}
char* Config::getPassword(){
  return _configData.password;
}
void Config::getPassword(char* val){
  strncpy(_configData.password, val, 255);
}
char* Config::getUsername(){
  return _configData.username;
}
void Config::getUsername(char* val){
  strncpy(_configData.username, val, 255); 
}
char* Config::getEMail(){
  return _configData.email;
}
void Config::getEMail(char* val){
  strncpy(_configData.email, val, 255); 
}
char* Config::getFlag1(){
  return _configData.flag1; 
}
void Config::getFlag1(char* val){
  strncpy(_configData.flag1, val, 255); 
}
char* Config::getFlag2(){
  return _configData.flag2;  
}
void Config::getFlag2(char* val){
  strncpy(_configData.flag2, val, 255); 
}
char* Config::getFlag3(){
  return _configData.flag3; 
}
void Config::getFlag3(char* val){
  strncpy(_configData.flag3, val, 255); 
}
char* Config::getFlag4(){
  return _configData.flag4;  
}
void Config::getFlag4(char* val){
  strncpy(_configData.flag4, val, 255); 
}
char* Config::getClientPrivateKey(){
  return _configData.clientPrivateKey;  
}
void Config::getClientPrivateKey(char* val){
  strncpy(_configData.clientPrivateKey, val, 2048); 
}
char* Config::getClientPublicKey(){
  return _configData.clientPublicKey;  
}
void Config::getClientPublicKey(char* val){
  strncpy(_configData.clientPublicKey, val, 2048); 
}
char* Config::getServerPrivateKey(){
  return _configData.serverPrivateKey;  
}
void Config::getServerPrivateKey(char* val){
  strncpy(_configData.serverPrivateKey, val, 2048); 
}
char* Config::getServerPublicKey(){
  return _configData.serverPublicKey;  
}
void Config::getServerPublicKey(char* val){
  strncpy(_configData.serverPublicKey, val, 2048); 
}
int Config::getCurrentFlag(){
  return _configData.currentFlag;
}
void Config::getCurrentFlag(int val){
  _configData.currentFlag = val;
}
int Config::getCurrentState(){
  return _configData.currentState;
}
void Config::getCurrentState(int val){
  _configData.currentState = val;
}


