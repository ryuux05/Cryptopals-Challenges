#ifndef HEX_TO_BASE64_H
#define HEX_TO_BASE64_H
#include <stdlib.h>
/*
  Function to convert a hexadecimal-encoded string to a base64-encoded string.
  params : hexadecimal-encoded string
  returns : string - or a null pointer if allocation failed

  The return value must be deallocated using free().
*/
char *hex_to_base64(const char *hex_string);
/*
  Function to convert a string base64-encoded to a hexadecimal-encoded string.
  params : hexadecimal-encoded string
  returns : string - or a null pointer if allocation failed

  The return value must be deallocated using free().
*/
char *string_to_hex(const char *hex_string, int* out_len);
/*
  Function to do fixed XOR on two hex string.
  params : hexadecimal-encoded string
  returns : string - or a null pointer if allocation failed

  The return value must be deallocated using free().
*/
char *fixed_XOR(const char *hex_string1, const char *hex_string2);

void test(int dec);

#endif