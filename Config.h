/**
 * Config.h - This is where all the config file stuff happens
 * 
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#ifndef Config_h
#define Config_h

#include <Arduino.h>
#include <FS.h>

#define CONFIG_FILE_NAME  "/conf/config.txt"


typedef struct {
    char ssid[256];
    char password[256];
    char username[256];
    char email[256];
    char flag1[256];
    char flag2[256];
    char flag3[256];
    char flag4[256];
    char clientPrivateKey[2050];
    char clientPublicKey[2050];
    char serverPrivateKey[2050];
    char serverPublicKey[2050];
    int currentFlag = 0;
    int currentState = 0; 
}config_t;


class Config{
  private:
    config_t _configData;
    
    void readData();

  public:
    Config();
    void setup();
    void writeData();
    char* getSSID();
    void setSSID(char* val);
    char* getPassword();
    void getPassword(char* val);
    char* getUsername();
    void getUsername(char* val);
    char* getEMail();
    void getEMail(char* val);
    char* getFlag1();
    void getFlag1(char* val);
    char* getFlag2();
    void getFlag2(char* val);
    char* getFlag3();
    void getFlag3(char* val);
    char* getFlag4();
    void getFlag4(char* val);
    char* getClientPrivateKey();
    void getClientPrivateKey(char* val);
    char* getClientPublicKey();
    void getClientPublicKey(char* val);
    char* getServerPrivateKey();
    void getServerPrivateKey(char* val);
    char* getServerPublicKey();
    void getServerPublicKey(char* val);
    int getCurrentFlag();
    void getCurrentFlag(int val);
    int getCurrentState();
    void getCurrentState(int val);
};

#endif
