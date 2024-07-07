#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set1.h"

static unsigned test_base64_str(const char *file, int line,
                                const char *input, const char *expected)
{
    char *actual = hex_to_base64(input);
    if (!actual) {
        fprintf(stderr, "%s:%d: to_base64(\"%s\") returned null; expected \"%s\"\n",
                file, line, input, expected);
        return 1;
    }

    if (!strcmp(actual, expected)) {
        free(actual);
        return 0;
    }
    fprintf(stderr, "%s:%d: to_base64(\"%s\") returned \"%s\"; expected \"%s\"\n",
            file, line, input, actual, expected);
    free(actual);
    return 1;
}

static unsigned test_fixed_XOR(const char *file, int line,
                               const char *input1, const char *input2, char *expected)
{
    char *actual = fixed_XOR(input1, input2);
    
   if (!actual) {
        fprintf(stderr, "%s:%d: returned null; expected \"%s\"\n",
                file, line, expected);
        return 1;
    }

    if (!strcmp(actual, expected)) {
        free(actual);
        return 0;
    }

    fprintf(stderr, "%s:%d: returned returned \"%s\"; expected \"%s\"\n",
                file, line, actual, expected);
    free(actual);
    return 1;
}

#define TEST_BASE64_STR(n, expected) \
    failures += test_base64_str(__FILE__, __LINE__, n, expected)

#define TEST_FIXED_XOR(n1, n2, expected) \
    failures += test_fixed_XOR(__FILE__, __LINE__, n1, n2, expected)

int main(void)
{
    unsigned failures = 0;

    TEST_BASE64_STR("1d", "HQ=");
    TEST_BASE64_STR("1d0", "HQ");
    TEST_BASE64_STR("deadbeef", "3q2+7w=");
    TEST_BASE64_STR("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d",
                    "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t");

    TEST_FIXED_XOR("1c0111001f010100061a024b53535009181c", "686974207468652062756c6c277320657965", "746865206b696420646f6e277420706c6179");

    printf("Tests completed with %u failures.\n", failures);

    // const char *hex_str = "4A3";
    // int len = 3;
    // int result = test(hex_str);
    // printf("Hexadecimal %s to integer is %d\n", hex_str, result);

    test(10);
    

    return failures > 0;
}