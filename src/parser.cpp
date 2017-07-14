#include "header.h"
#include "credentials.h"

bool parseCmd (String cmd, String args) {
    if (cmd.equalsIgnoreCase("wc")) {

        if (stringCharCount(args, ' ') == 1) {
            String ssid = stringBefore(args, ' ');
            String password = stringAfter(args, ' ');
            wifiConnect(ssid, password);
            return true;
        }
        else if (args == "") {
            wifiConnect(defSsid, defPassword);
            return true;
        }
        else {
            return false;
        }
    }
    else if (cmd.equalsIgnoreCase("wd")) {
        if (args != "") return false;
        wifiDisconnect();
        return true;
    }
    else if (cmd.equalsIgnoreCase("sc")) {

        if (stringCharCount(args, ':') != 1) return false;

        if (stringCharCount(args, '.') == 3) {
            IPAddress ip;
            ip.fromString(stringBefore(args, ':'));
            int port = stringAfter(args, ':').toInt();
            serverConnect(ip, port);
            return true;
        }
        else if (stringCharCount(args, '.') == 0) {
            IPAddress ip;
            ip = WiFi.localIP();
            ip[3] = stringBefore(args, ':').toInt();
            int port = stringAfter(args, ':').toInt();
            serverConnect(ip, port);
            return true;
        }
        else {
            return false;
        }

    }
    else if (cmd.equalsIgnoreCase("sd")) {
        if (args != "") return false;

        serverDisconnect();
        return true;
    }
    else if (cmd.equalsIgnoreCase("raw")) {
        raw(args);
        return true;
    }
    else if (cmd.equalsIgnoreCase("st")) {
        if (stringCharCount(args, ' ') != 0) return false;
        if (args == "") {
            serverType(-1);
        }
        else {
            serverType(args.toInt());
        }
        return true;
    }
    else if (cmd.equalsIgnoreCase("nl")) {
        if (args != "") return false;
        terminal.addString("");
        return true;
    }
    else {
        cmd.toUpperCase();
        terminal.addLine("Err", "Prikaz " + cmd + " neznam!");
    }

}

void parseMsg(char cmd, IPAddress ip, String msg) {
    if (cmd == 'k') {

    }
    else if (cmd == 'm') {
        terminal.addLine((String)ip[3], msg);
    }
    else if (cmd == 'c') {
        terminal.addLine((String)ip[3], "Jsem online s prezdivkou " + msg);
    }
    else if (cmd == 'd') {
        terminal.addLine((String)ip[3], "Jsem offline!");
    }
    else if (cmd == 'a') {

    }
    else if (cmd == 't') {

    }
    else {
        terminal.addLine("Anti", "Prisel vadny packet.");
    }
}
