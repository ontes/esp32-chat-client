#include "header.h"

WiFiClient client;
Terminal terminal;
Comunicator comunicator;

void setup() {
    Serial.begin(115200);
    terminal.addLine("Inf", "Startuju XTR v1.0");

    WiFi.mode(WIFI_STA);
    delay(1000);
}

void loop() {
    if(WiFi.status() != WL_CONNECTED || WiFi.status() != WL_DISCONNECTED) {
        Serial.println("Err", "Spojeni s WiFi ztraceno!");
    }
    
    if(Serial.available()) {
        byte b = Serial.read();

        if (b == '\n') {
            if (msg[0] == '.') {
                // Command mode

                String cmd = msg.substring(1);

                if (stringStarting(cmd, "tcp c")) {
                    String args = cmd.substring(6); // delka "tcp c "
                    tcpConnect(args);
                }
                else if (stringStarting(cmd, "tcp d")) {
                    tcpDisconnect();
                }
                else {
                    Serial.print("XTR: Neznam prikaz ");
                    Serial.print(cmd);
                    Serial.println("!");
                }
            }
            else {
                // Chat
                if (client.connected()) {
                    client.println(msg);
                } else {
                    Serial.println("XTR: Nejsi pripojeny!");
                }
            }
            msg = "";
        }
        else if(b == '\b') {
            terminal.removeChar();
        }
        else if(b == '\r') {

        }
        else {
            msg += (char)b;
        }
    }

    while(client.available()) {

    }

    delay(50);
}