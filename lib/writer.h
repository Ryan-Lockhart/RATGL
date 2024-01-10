#ifndef WRITER_H

#define WRITER_H

#include "typedef.h"

int writer_string(const char* path, const char* content);

int writer_binary(const char* path, const byte* buffer);

#endif
