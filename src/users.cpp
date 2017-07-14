#include "header.h"
#include <map>



void Users::ban (IPAddress ip) {
    banned[ip] = true;
}

void Users::unban (IPAddress ip) {
    banned[ip] = false;
}

bool Users::isBanned (IPAddress ip) {
    if (banned.find(ip) == banned.end()) {
        banned[ip] = false;
    }
    return banned[ip];
}

void Users::setNick (IPAddress ip, String nick) {
    nicks[ip] = nick;
}

void Users::setDefaultNick (IPAddress ip) {
    nicks[ip] = ip.toString();
}

String Users::getNick (IPAddress ip) {
    if (nicks.find(ip) == nicks.end()) {
        setDefaultNick(ip);
    }
    return nicks[ip];
}
