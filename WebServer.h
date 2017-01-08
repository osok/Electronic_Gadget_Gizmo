/**
 * WebServer.h - This class manages the webserver interface.
 * 
 * Much ofthis class is based on the ESP example called FSBowser,
 * by Hristo Gochkov, which is license as LGPL.
 * 
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#ifndef WebServer_h
#define WebServer_h

#include <Arduino.h>
#include "Global.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>

#define DBG_OUTPUT_PORT Serial


class WebServer{
  private:
    boolean _serverRunning;
    void debugOutputFilesOnServer();
    void configureHandlers();
    
  public:
    WebServer();
    void setup();
    void run();
    void stopServer();
    void restartServer();
};

#endif

