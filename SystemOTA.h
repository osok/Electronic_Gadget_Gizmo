/**
 * SystemOTA.h - This Class manages the OTA "Over The Air" option
 *              which enables the card to be programmed without UART 
 *              connectivity.
 * 
 * 
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#ifndef SystemOTA_h
#define SystemOTA_h

#include <Arduino.h>


class SystemOTA{

  public:
    SystemOTA();
    void setup();
    void run();
};

#endif

