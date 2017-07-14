#include <Arduino.h>

String stringBefore (String str, char ch) {
    return str.substring(0, str.indexOf(ch));
}

String stringAfter (String str, char ch) {
    return str.substring(str.indexOf(ch) + 1);
}

int stringCharCount (String str, char ch) {
    int count = 0;
    while (str.indexOf(ch) != -1) {
        str = str.substring(str.indexOf(ch) + 1);
        count ++;
    }
    return count;
}

String stringSplit (String str, char ch, int num) {
    for (int i = 0; i < num; i++) {
        if (str.indexOf(ch) == -1)
            return str;
        str = stringAfter(str, ch);
    }
    return stringBefore(str, ch);
}
