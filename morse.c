#include "morse.h"

char* morse_encode_char(char ch) { 
    switch (ch) { 
        // letters
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
        // digits
        case '0':
            return "1110111011101110111"; // -----
        case '1':
            return "10111011101110111"; // .----
        case '2':
            return "101011101110111"; // ..---
        case '3':
            return "1010101110111"; // ...--
        case '4':
            return "10101010111"; // ....-
        case '5':
            return "101010101"; // .....
        case '6':
            return "11101010101"; // -....
        case '7':
            return "1110111010101"; // --...
        case '8':
            return "111011101110101"; // ---..
        case '9':
            return "11101110111011101"; // ----.
        // symbols /* NOT READY */
        case '.':
            return "10111010111010111"; // • − • − • −
        case ',':
            return "1110111010101110111"; // − − • • − −
        case ':':
            return "11101110111010101"; // − − − • • •	
        case '?':
            return "101011101110101"; // • • − − • •
        case '\'':
            return "1011101110111011101"; // • − − − − •
        case '-':
            return "111010101010111"; // − • • • • −	
        case '+':
            return "1011101011101"; // • − • − •
        case '=':
            return "1110101010111"; // − • • • −
    } 
    return "00000"; // space 
} 

char* str_to_morse(char* str){
    char* output = (char*) malloc(2000); 
    char code[20];
    for (int i = 0; str[i]; i++){
        strcpy(code, morse_encode_char(str[i]));
        if(str[i] !=  ' ' && str[i + 1] && str[i + 1] != ' ' )
            strcat(code, "000");
        strcat(output, code);
    }
    return output;
}