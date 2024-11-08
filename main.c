#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "base64.h"

const char base64_encoding_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const int base64_decoding_table[] = { 62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58,
	59, 60, 61, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5,
	6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28,
	29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
	43, 44, 45, 46, 47, 48, 49, 50, 51 };

/**
 * Returns the exact size of a Base64 encoded string.
 */

size_t base64_encoded_size(size_t input_size) {
    size_t output_size = input_size;

    if (input_size % 3 != 0) {
        output_size += 3 - input_size % 3;
    }

    output_size = (output_size / 3) * 4;
    return output_size;
}

/**
 * Encodes an input string in Base64.
 */

char* base64_encode(char* data) {
    size_t i, j, holder;
    size_t mask = 0x3F;
    size_t input_size = strlen(data);
    size_t output_size = base64_encoded_size(input_size);
    
    // Add 1 to account for the NULL Terminator.
    char* output = malloc(output_size + 1);
    if (output == NULL) {
        return NULL;
    }

    output[output_size] = '\0';

    for (i = 0, j = 0; i < input_size; i += 3, j += 4) {
        holder = data[i];
        holder = i + 1 < input_size ? (holder << 8) | data[i + 1] : holder << 8;
        holder = i + 2 < input_size ? (holder << 8) | data[i + 2] : holder << 8;

        output[j] = base64_encoding_table[(holder >> 18) & mask];
        output[j + 1] = base64_encoding_table[(holder >> 12) & mask];
        output[j + 2] = i + 1 < input_size ? base64_encoding_table[(holder >> 6) & mask] : '=';
        output[j + 3] = i + 2 < input_size ? base64_encoding_table[holder & mask] : '=';
    }

    // /!\ DON'T FORGET TO FREE!
    return output;
}

/**
 * Returns the maximum decoding size, meaning there might be an offset by 1-2 bytes.
 */

size_t base64_decoded_size(size_t input_size) {
    return input_size / 4 * 3;
}

/**
 * Decodes a Base64 input string.
 */

char* base64_decode(char* data) {
    size_t i, j, holder;
    size_t k = 0;
    size_t mask = 0xFF;
    size_t input_size = strlen(data);
    size_t output_size = base64_decoded_size(input_size);

    char* output = malloc(output_size);
    if (output == NULL) {
        return NULL;
    }

    for (i = 0, j = 0; i < input_size; i += 4, j += 3) {
        holder = base64_decoding_table[data[i] - '+'];
        holder = (holder << 6) | base64_decoding_table[data[i + 1] - '+'];
        holder = (holder << 6) | base64_decoding_table[data[i + 2] - '+'];
        holder = (holder << 6) | base64_decoding_table[data[i + 3] - '+'];

        output[j] = holder >> 16 & mask;
        k++;

        if (data[i + 2] != '=') {
            output[j + 1] = holder >> 8 & mask;
            k++;
        }
        if (data[i + 3] != '=') {
            output[j + 2] = holder & mask;
            k++;
        }
    }

    output[k] = '\0';
    // /!\ DON'T FORGET TO FREE!
    return output;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("[ERROR] Invalid amount of arguments.");
        return 1;
    }

    char buffer[INPUT_BUFFER_SIZE];

    if (strcmp(argv[1], "encode") == 0) {
        printf("Enter a string: ");
        fgets(buffer, INPUT_BUFFER_SIZE, stdin);
        char* encoded_data = base64_encode(buffer);
        printf("Base64 Encoding: %s", encoded_data);

        free(encoded_data);
    }
    else if (strcmp(argv[1], "decode") == 0) {
        printf("Enter a string: ");
        fgets(buffer, INPUT_BUFFER_SIZE, stdin);
        char* decoded_data = base64_decode(buffer);
        printf("Base64 Decoding: %s", decoded_data);

        free(decoded_data);
    }
    else {
        printf("[ERROR] Second argument is invalid, use [decode/encode].");
        return 1;
    }

    return 0;
}

