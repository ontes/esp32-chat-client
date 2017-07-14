#include "header.h"


void wifiConnect(String ssid, String password) {
    int timer = 3;
    terminal.processSet("Pripojuji se na wifi...");
    WiFi.begin(ssid.c_str(), password.c_str());

    while(WiFi.status() != WL_CONNECTED) {

        if(WiFi.status() != WL_DISCONNECTED) {
            if (timer <= 0) {
                terminal.addLine("Err", "Nepodarilo se pripojit.");
                terminal.processClear();
                return;
            }
            else {
                terminal.addLine("Err", "Nepodarilo se pripojit, opakuji " + (String)timer + "x!");
                WiFi.begin(ssid.c_str(), password.c_str());
            }
            timer --;
        }
        delay(1000);

    }
    terminal.processClear();
    terminal.addLine("Inf", "Pripojeno k WiFi " + ssid + " s ip " + WiFi.localIP().toString() + "!");
}

void wifiDisconnect() {
    WiFi.disconnect();
    terminal.addLine("Inf", "Odpojeno z WiFi.");
}

void serverConnect(IPAddress ip, int port) {
    terminal.processSet("Pripojuju se na server...");

    if (client.connect(ip, port)) {
        terminal.addLine("Inf", "Pripojeno na server " + ip.toString() + ":" + (String)port + "!");
    }
    else {
        terminal.addLine("Err", "Nepodarilo se pripojit na server!");
    }

    terminal.processClear();
}

void serverDisconnect() {
    if (!client.connected()) {
        terminal.addLine("Err", "Nejsi pripojeny!");
    }
    else {
        client.stop();
        terminal.addLine("Inf", "Odpojeno ze serveru!");
    }
}

void raw(String msg) {
    for (int i = 0; i < stringCharCount(msg, ' ') + 1; i++ ) {
        client.write(stringSplit(msg, ' ', i).toInt());
    }
}

void serverType (int type) {
    if (type == -1) {
        terminal.addLine("Inf", "Typ serveru je " + (String)comunicator.serverType);
    }
    else if (type > 1 || type < 0) {
        terminal.addLine("Err", "Neznam tento typ.");
    }
    else {
        comunicator.serverType = type;
        terminal.addLine("Inf", "Typ serveru byl nastaven na " + (String)type);
    }
}
