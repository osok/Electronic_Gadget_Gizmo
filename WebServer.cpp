/**
 * WebServer.cpp - This class manages the webserver interface.
 * 
 * Much ofthis class is based on the ESP example called FSBowser,
 * by Hristo Gochkov, which is license as LGPL.
 * 
 * Created by osok
 * github https://github.com/osok/Electronic_Gadget_Gizmo
 */

#include "WebServer.h"


ESP8266WebServer _server(80);
File _fsUploadFile;  //holds the current upload


WebServer::WebServer(){}

//format bytes
String formatBytes(size_t bytes){
  if (bytes < 1024){
    return String(bytes)+"B";
  } else if(bytes < (1024 * 1024)){
    return String(bytes/1024.0)+"KB";
  } else if(bytes < (1024 * 1024 * 1024)){
    return String(bytes/1024.0/1024.0)+"MB";
  } else {
    return String(bytes/1024.0/1024.0/1024.0)+"GB";
  }
}

String getContentType(String filename){
  if(_server.hasArg("download")) return "application/octet-stream";
  else if(filename.endsWith(".htm")) return "text/html";
  else if(filename.endsWith(".html")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".js")) return "application/javascript";
  else if(filename.endsWith(".png")) return "image/png";
  else if(filename.endsWith(".gif")) return "image/gif";
  else if(filename.endsWith(".jpg")) return "image/jpeg";
  else if(filename.endsWith(".ico")) return "image/x-icon";
  else if(filename.endsWith(".xml")) return "text/xml";
  else if(filename.endsWith(".pdf")) return "application/x-pdf";
  else if(filename.endsWith(".zip")) return "application/x-zip";
  else if(filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

bool handleFileRead(String path){
  DBG_OUTPUT_PORT.println("handleFileRead: " + path);
  if(path.endsWith("/")) path += "index.htm";
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  if(SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)){
    if(SPIFFS.exists(pathWithGz))
      path += ".gz";
    File file = SPIFFS.open(path, "r");
    size_t sent = _server.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}

void handleFileUpload(){
  if(_server.uri() != "/edit") return;
  HTTPUpload& upload = _server.upload();
  if(upload.status == UPLOAD_FILE_START){
    String filename = upload.filename;
    if(!filename.startsWith("/")) filename = "/"+filename;
    DBG_OUTPUT_PORT.print("handleFileUpload Name: "); DBG_OUTPUT_PORT.println(filename);
    _fsUploadFile = SPIFFS.open(filename, "w");
    filename = String();
  } else if(upload.status == UPLOAD_FILE_WRITE){
    //DBG_OUTPUT_PORT.print("handleFileUpload Data: "); DBG_OUTPUT_PORT.println(upload.currentSize);
    if(_fsUploadFile)
      _fsUploadFile.write(upload.buf, upload.currentSize);
  } else if(upload.status == UPLOAD_FILE_END){
    if(_fsUploadFile)
      _fsUploadFile.close();
    DBG_OUTPUT_PORT.print("handleFileUpload Size: "); DBG_OUTPUT_PORT.println(upload.totalSize);
  }
}

void handleFileDelete(){
  if(_server.args() == 0) return _server.send(500, "text/plain", "BAD ARGS");
  String path = _server.arg(0);
  DBG_OUTPUT_PORT.println("handleFileDelete: " + path);
  if(path == "/")
    return _server.send(500, "text/plain", "BAD PATH");
  if(!SPIFFS.exists(path))
    return _server.send(404, "text/plain", "FileNotFound");
  SPIFFS.remove(path);
  _server.send(200, "text/plain", "");
  path = String();
}

void handleFileCreate(){
  if(_server.args() == 0)
    return _server.send(500, "text/plain", "BAD ARGS");
  String path = _server.arg(0);
  DBG_OUTPUT_PORT.println("handleFileCreate: " + path);
  if(path == "/")
    return _server.send(500, "text/plain", "BAD PATH");
  if(SPIFFS.exists(path))
    return _server.send(500, "text/plain", "FILE EXISTS");
  File file = SPIFFS.open(path, "w");
  if(file)
    file.close();
  else
    return _server.send(500, "text/plain", "CREATE FAILED");
  _server.send(200, "text/plain", "");
  path = String();
}

void handleFileList() {
  if(!_server.hasArg("dir")) {_server.send(500, "text/plain", "BAD ARGS"); return;}
  
  String path = _server.arg("dir");
  DBG_OUTPUT_PORT.println("handleFileList: " + path);
  Dir dir = SPIFFS.openDir(path);
  path = String();

  String output = "[";
  while(dir.next()){
    File entry = dir.openFile("r");
    if (output != "[") output += ',';
    bool isDir = false;
    output += "{\"type\":\"";
    output += (isDir)?"dir":"file";
    output += "\",\"name\":\"";
    output += String(entry.name()).substring(1);
    output += "\"}";
    entry.close();
  }
  
  output += "]";
  _server.send(200, "text/json", output);
}

void WebServer::debugOutputFilesOnServer(){
  DBG_OUTPUT_PORT.print("\n");
  DBG_OUTPUT_PORT.setDebugOutput(true);
  SPIFFS.begin();
  {
    Dir dir = SPIFFS.openDir("/");
    while (dir.next()) {    
      String fileName = dir.fileName();
      size_t fileSize = dir.fileSize();
      DBG_OUTPUT_PORT.printf("FS File: %s, size: %s\n", fileName.c_str(), formatBytes(fileSize).c_str());
    }
    DBG_OUTPUT_PORT.printf("\n");
  }
  
}

void WebServer::configureHandlers(){
  //SERVER INIT
  //list directory
  _server.on("/list", HTTP_GET, handleFileList);
  //load editor
  _server.on("/edit", HTTP_GET, [](){
    if(!handleFileRead("/edit.htm")) _server.send(404, "text/plain", "FileNotFound");
  });
  //create file
  _server.on("/edit", HTTP_PUT, handleFileCreate);
  //delete file
  _server.on("/edit", HTTP_DELETE, handleFileDelete);
  //first callback is called after the request has ended with all parsed arguments
  //second callback handles file uploads at that location
  _server.on("/edit", HTTP_POST, [](){ _server.send(200, "text/plain", ""); }, handleFileUpload);

  //called when the url is not defined here
  //use it to load content from SPIFFS
  _server.onNotFound([](){
    if(!handleFileRead(_server.uri()))
      _server.send(404, "text/plain", "FileNotFound");
  });

  //get heap status, analog input value and all GPIO statuses in one json call
  _server.on("/all", HTTP_GET, [](){
    String json = "{";
    json += "\"heap\":"+String(ESP.getFreeHeap());
    json += ", \"analog\":"+String(analogRead(A0));
    json += ", \"gpio\":"+String((uint32_t)(((GPI | GPO) & 0xFFFF) | ((GP16I & 0x01) << 16)));
    json += "}";
    _server.send(200, "text/json", json);
    json = String();
  });
  _server.begin();
  DBG_OUTPUT_PORT.println("HTTP server started");
  
}

void WebServer::setup(){
  Serial.println("WebServer is setting up...");
  debugOutputFilesOnServer();
  configureHandlers();
  _serverRunning = true;
  
}

void WebServer::stopServer(){
  _serverRunning = false;
}

void WebServer::restartServer(){
  _serverRunning = true;
}

void WebServer::run(){
  Serial.println("WebServer is running");
  while(1){
    while(_serverRunning){
      _server.handleClient();
      yield();
    }
    yield();
  }
}


