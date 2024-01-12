#ifndef WRITER_H

#define WRITER_H

#include "error.h"

err_t writer_string(cstr path, cstr content);

err_t writer_binary(cstr path, const byte* buffer);

#endif
