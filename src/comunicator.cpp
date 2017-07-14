#include "header.h"

#define MAX_LENGTH 64

void Comunicator::recieveChar(char ch) {
    if (serverType == 0) {
        if (ch == '\n') {
            terminal.addLine("Server", msg);
            msg = "";
            length = 0;
        }
        else if (ch >= 32 && ch <= 126) {
            msg += ch;
        }
        else {
            msg += "/" + (String)((byte)ch) + "/";
        }
    } else if (serverType == 1) {
        //terminal.addLine("Debug", (String)ch);
        if (length == 0) {
            cmd = ch;
        }
        else if (length <= 4) {
            ip[length-1] = (byte)ch;
        }
        else if (length < MAX_LENGTH) {
            if (ch == '\0') {
                parseMsg(cmd, ip, msg);
                clearBuffer();
                return;
            }
            else if (ch >= 32 && ch <= 126) {
                msg += ch;
            }
            else {
                msg += "[" + (String)((int)ch) + "]";
            }
        }
        else {
            terminal.addLine("Anti", "Prisla prilis dlouha zprava z " + (String)ip + ", zahazuji.");
            clearBuffer();
            Serial.readString();
            return;
        }
        length++;
    }
}

void Comunicator::sendMsg(String ms) {
    if (serverType == 0) {
        client.print(ms);
    }
    else if (serverType == 1) {
        client.write("m\0\0\0\0", 5);
        client.print(ms);
        client.write("\0", 1);
    }
}

void Comunicator::clearBuffer() {
    msg = "";
    length = 0;
}
