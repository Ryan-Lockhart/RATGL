#ifndef READER_H

#define READER_H

#include "error.h"

err_t reader_string(cstr path, str* content);

err_t reader_binary(cstr path, byte** buffer);

#endif
