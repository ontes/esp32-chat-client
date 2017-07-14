#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <map>

class Terminal {
    String cmdLine;
public:
    bool cmdCanWrite = true;
    void addString(String msg);
    void addLine(String name, String msg);
    void cmdAddChar(char ch);
    void cmdRemoveChar();
    String cmdClear();
    void processSet(String name);
    void processClear();
};

class Comunicator {
    int length = 0;
    char cmd;
    IPAddress ip;
    String msg = "";
public:
    int serverType = 0;
    void recieveChar(char ch);
    void sendMsg(String ms);
    void clearBuffer();
};

class Users {
    std::map <IPAddress, bool> banned;
    std::map <IPAddress, String> nicks;
public:
    void ban (IPAddress ip);
    void unban (IPAddress ip);
    bool isBanned (IPAddress ip);
    void setNick (IPAddress ip, String nick);
    void setDefaultNick (IPAddress ip);
    String getNick (IPAddress ip);
};

// Command
void wifiConnect(String ssid, String password);
void wifiDisconnect();
void serverConnect(IPAddress ip, int port);
void serverDisconnect();
void raw(String msg);
void serverType (int type);

// Parser
bool parseCmd (String cmd, String args);
void parseMsg(char cmd, IPAddress ip, String msg);

// StringTools
String stringBefore (String str, char ch);
String stringAfter (String str, char ch);
int stringCharCount (String str, char ch);
String stringSplit (String str, char ch, int num);

// Instance
extern WiFiClient client;
extern Terminal terminal;
extern Comunicator comunicator;
