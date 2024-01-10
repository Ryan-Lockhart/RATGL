#ifndef READER_H

#define READER_H

#include "typedef.h"

int reader_string(const char* path, char** content);

int reader_binary(const char* path, byte** buffer);

#endif
