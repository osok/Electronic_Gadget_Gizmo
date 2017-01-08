/**
 * GameWifi.h - This class take care of the Wifi connectivity
 * 
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#ifndef GameWifi_h
#define GameWifi_h

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>


class GameWifi{
  private:
    const char* ssid = "Test-Net";
    const char* password = "PleaseStayOffMyWiFi";
    boolean wifiConnected = false;
    
  public:
    GameWifi();
    void setup();
    boolean isWifiConnected();
};



#endif

