#include "set1.h"
#include <stdlib.h>
#include <string.h>

/* a in "0123456789abcdef" */
static int from_hex(char c)
{
    switch (c) {
    default: return c - '0';    /* digits are guaranteed consecutive */
    case 'a': case 'A': return 10;
    case 'b': case 'B': return 11;
    case 'c': case 'C': return 12;
    case 'd': case 'D': return 13;
    case 'e': case 'E': return 14;
    case 'f': case 'F': return 15;
    }
}

char *hex_to_base64(const char *hex_string) {
    //Calculate the lenght of the string
    int input_len = strlen(hex_string);
    int output_len = (input_len * 2 + 2) / 3        //Convert to base64
                        + 2 - (input_len - 1) % 3   //padding '=' or '=='
                        + 1;                        //null terminator ('\0')

    //Allocate memory for the output
    char* const out_buf = malloc(output_len);
    if(!out_buf){
        return NULL;
    }
    
    //Start 

    
    return;
}

int main() {
    printf("Hello world");
    return 0;
}