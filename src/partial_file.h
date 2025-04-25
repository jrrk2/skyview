// partial_file.h

#ifndef PARTIAL_FILE_H
#define PARTIAL_FILE_H

#ifdef __EMSCRIPTEN__
#include <emscripten.h>

#include <stdint.h>
#include <stdlib.h>

#define FILE_ERROR_NONE 0
#define FILE_ERROR_NOT_FOUND 1
#define FILE_ERROR_NETWORK 2
#define FILE_ERROR_TIMEOUT 3
#define FILE_ERROR_INVALID 4

#define FILE_MAX_FILES 256
#define FILE_TIMEOUT_MS 5000
#define FILE_BUFFER_SIZE 8192

typedef struct {
    char* filename;
    int32_t position;     // Current file position
    int32_t size;         // Total file size if known, -1 if unknown
    int exists;           // Whether file exists
    int error_state;      // Current error state
    unsigned char* buffer;  // Read buffer
    size_t buffer_size;    // Size of buffered data
    size_t buffer_pos;     // Current position in buffer
    int buffer_valid;      // Whether buffer contains valid data
    void* user_data;      // For future extensibility
} FILE;

// Core API functions
FILE* fopen(const char* filename, const char* mode);
size_t fread(void* ptr, size_t size, size_t count, FILE* file);
int fseek(FILE* file, int32_t offset, int origin);
int32_t ftell(FILE* file);
int ferror(FILE* file);
int feof(FILE* file);
int fclose(FILE* file);

// Utility functions
const char* myfile_strerror(int error_code);
int32_t myfile_size(FILE* file);
void myfile_set_timeout(int milliseconds);
void js_fetch_partial_file(const char* url, int32_t start, int32_t end, void* buffer_ptr, int* status_ptr);

#endif

#endif // PARTIAL_FILE_H
