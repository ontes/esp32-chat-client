#include "header.h"

void Terminal::addString(String msg) {
    Serial.print('\r');
    Serial.print(msg);
    Serial.print("\n\r");
    Serial.print(cmdLine);
}

void Terminal::addLine(String name, String msg) {

    Serial.print('\r');
    Serial.print('[');
    Serial.print(name);
    Serial.print("] ");
    Serial.print(msg);
    Serial.print("\n\r");

    Serial.print(cmdLine);
}

void Terminal::cmdAddChar(char ch) {
    if (!cmdCanWrite) return;

    Serial.print(ch);
    cmdLine += ch;
}

void Terminal::cmdRemoveChar() {
    if (!cmdCanWrite) return;

    if (cmdLine.length() > 0) {
        Serial.print("\b \b");
        cmdLine = cmdLine.substring(0, cmdLine.length()-1);
    }
}

String Terminal::cmdClear() {
    Serial.print('\r');
    for (int i = cmdLine.length(); i > 0; i--) {
        Serial.print(' ');
    }
    for (int i = cmdLine.length(); i > 0; i--) {
        Serial.print('\b');
    }
    String ret = cmdLine;
    cmdLine = "";
    return ret;
}

void Terminal::processSet(String name) {
    cmdCanWrite = false;
    cmdClear();
    String pr = " * " + name;
    Serial.print(pr);
    cmdLine = pr;
}

void Terminal::processClear() {
    cmdClear();
    cmdCanWrite = true;
}
