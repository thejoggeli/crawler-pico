#pragma once

#include <Arduino.h>

namespace StringUtils {

String padLeft(const String& str, char c, unsigned int n){

    int delta = n -str.length();

    if(delta <= 0){
        return str;
    }

    char pad[delta];
    for(int i = 0; i < delta; i++){
        pad[i] = c;
    }

    return String(pad) + str;
    
}

}