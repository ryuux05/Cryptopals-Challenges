#include "set1.h"
#include <string.h>
#include <math.h>
#include<stdio.h>

/* a in "0123456789abcdef" */
static int from_hex_char(char c)
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

static int from_hex_string(char *hex) {
    int val = 0;
    int len = sizeof(hex);
    for (int i = 0; i < len; i++)
    {
        val += from_hex_char(hex[i]) * pow(16, len - i - 1);
        printf("%d\n", val);
    }
    return val;
}

static int* from_decimal_to_binary(int dec, int *size) {
    if (dec == 0) {
        int* binary = malloc(1 * sizeof(int));
        binary[0] = 0;
        *size = 1;
        return binary;
    }

    *size = (int)log2(dec) + 1; // Calculate the number of bits required
    int* binary = malloc(*size * sizeof(int));
    
    for (int i = 0; i < size; i++) {
        binary[i] = 0; // Initialize the array
    }

    int i = size - 1;
    while (dec > 0) {
        binary[i] = dec % 2;
        dec = dec / 2;
        i--;
    }

    for (int i = 0; i < size; i++)
    {
        printf("%d", binary[i]);
    }
    
}

// Function to convert an ASCII character to its hexadecimal representation
// Hex is 4 bits representation and ASCII is 8 bits representation (7 to be more precise)
static void char_to_hex(unsigned char c, char* hex) {
    const char hex_chars[] = "0123456789abcdef";
    hex[0] = hex_chars[(c >> 4) & 0xF]; // High nibble
    hex[1] = hex_chars[c & 0xF];        // Low nibble
}

static void hex_to_char(unsigned char hex1, unsigned char hex2, char* c) {
    int high = (hex1 << 4) & 0xF0;
    int low = hex2 & 0xF;
    c[0] = high | low;
}

// Function to decode a hex string to a byte array
char* string_to_hex(const char* string, int* out_len) {
    const input_len = strlen(string);
    const output_len = (input_len * 2) + 1; // Each char to 2 hex digits + 1 for null terminator
    char* const out_buf = malloc(output_len);
    if(!out_buf){
        return NULL;
    }

    char *out = out_buf;
    for (int i = 0; i < input_len; i++)
    {
        char_to_hex(string[i], (char*)out + i * 2);
    }

    out[output_len - 1] = '\0'; // Null-terminate the string
    *out_len = output_len - 1;     // Set the output length (excluding the null terminator)

    return out;
}

char* hex_to_string(const char* hex, int* out_len){
    const input_len = strlen(hex);
    const output_len = (input_len - 1) / 2; // Each char to 2 hex digits + 1 for null terminator
    char* const out_buf = malloc(output_len);
    if(!out_buf){
        return NULL;
    }

    char *out = out_buf;
    for (int i = 0; i < input_len / 2; i++)
    {
        hex_to_char(hex[i * 2], hex[i * 2 + 1], (char*)out + i);
    }

    out[output_len - 1] = '\0';
    out_len = output_len - 1;
    
    return out;
}


char *hex_to_base64(const char *hex_string) {
    static const char base64[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

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

    char *out = out_buf;
    //Start checking every three hex digits, it makes 12 bytes, to make two base64 digits which consist of 12 bytes as well
    while(hex_string[0] && hex_string[1] && hex_string[2]){
        /* convert three hex digits to two base-64 chars */
        int digits[3] = {
            from_hex_char(hex_string[0]),
            from_hex_char(hex_string[1]),
            from_hex_char(hex_string[2]),
        };

        *out++ = base64[(digits[0] << 2) + (digits[1] >> 2)];
        *out++ = base64[((digits[1] & 3) << 4) + (digits[2])];

        hex_string += 3;
    }

    //Now check if there is any leftover char
    if (hex_string[0] && hex_string[1]){
        int digits[2] = {
            from_hex_char(hex_string[0]),
            from_hex_char(hex_string[1]),
        };

        *out++ = base64[(digits[0] << 2) + (digits[1] >> 2)];
        *out++ = base64[(digits[1] & 3) << 4];
        *out++ = '=';
    } else if (hex_string[0]) {
        int digits = from_hex_char(hex_string[0]);

        *out++ = base64[(digits << 2)];
        *out++ = '=';
        *out++ = '=';
    }

    *out++ = '\0'; //return null terminator

    return out_buf;
}

char *fixed_XOR(const char *string1, const char *string2) {
    int len1, len2, out_len;
    unsigned char *hex1 = string_to_hex(string1, &len1);
    unsigned char *hex2 = string_to_hex(string2, &len2);

    printf("%s\n", hex1);
    printf("%s\n", hex2);

    if (hex1 == NULL || hex2 == NULL) {
        printf("Error in hex decoding\n");
        return 0;
    }

    if (len1 != len2) {
        printf("Length mismatch\n");
        free(hex1);
        free(hex2);
        return 0;
    }
    char* const out_buf = malloc(len1 / 2);
    if(!out_buf){
        return NULL;
    }

    char *out = out_buf;
    for (int i = 0; i < len1; i++)
    {
        out[i] = hex1[i] ^ hex2[i];
        printf("%c\n", out[i]);
    }

    printf("%s\n", out);
    unsigned char *string = hex_to_string(out, out_len);
    
  for (int i = 0; i < len1 / 2; ++i) {
        out_buf[i] = hex1[i * 2] ^ hex2[i * 2];
    }

    return string;
}

void test(int dec){
    //from_decimal_to_binary(dec);   
}