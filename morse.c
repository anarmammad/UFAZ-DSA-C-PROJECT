#include "morse.h"

char* morse_encode_char(char ch) { 
    switch (ch) { 
        case 'a': 
            return "10111"; // .-  
        case 'b': 
            return "111010101"; // -...
        case 'c': 
            return "11101011101"; // -.-.
        case 'd': 
            return "1110101"; // -..
        case 'e': 
            return "1"; // .
        case 'f': 
            return "101011101"; // ..-. 
        case 'g': 
            return "111011101"; // --. 
        case 'h': 
            return "1010101"; // .... 
        case 'i': 
            return "101"; // ..
        case 'j': 
            return "1011101110111"; // .--- 
        case 'k': 
            return "111010111"; // -.-
        case 'l': 
            return "101110101"; // .-..
        case 'm': 
            return "1110111"; // -- 
        case 'n': 
            return "11101"; // -. 
        case 'o': 
            return "11101110111"; // --- 
        case 'p': 
            return "10111011101"; // .--. 
        case 'q': 
            return "1110111010111"; // --.- 
        case 'r': 
            return "1011101"; // .-. 
        case 's': 
            return "10101"; // ...  
        case 't': 
            return "111"; // - 
        case 'u': 
            return "1010111"; // ..- 
        case 'v': 
            return "101010111"; // ...- 
        case 'w': 
            return "101110111"; // .-- 
        case 'x': 
            return "11101010111"; // -..- 
        case 'y': 
            return "1110101110111"; // -.-- 
        case 'z': 
            return "11101110101"; // --.. 
    } 
    return "00000"; //  
} 

char* str_to_morse(char* str){
    char* output = (char*) malloc(2000); 
    char code[20];
    for (int i = 0; str[i]; i++){
        strcpy(code, morse_encode_char(str[i]));
        if(str[i]!= ' ' && str[i+1] && str[i+1] != ' ' )
            strcat(code, "000");
        strcat(output, code);
    }
    return output;
}