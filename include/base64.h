#ifndef H_BASE64
#define H_BASE64

#define INPUT_BUFFER_SIZE 1024

size_t base64_encoded_size(size_t input_size);

char* base64_encode(char* data);

size_t base64_decoded_size(size_t input_size);

char* base64_decode(char* data);

#endif