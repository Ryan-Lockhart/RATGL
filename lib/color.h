#ifndef COLOR_H

#define COLOR_H

#include "typedef.h"
#include "error.h"

typedef struct color_t {
	byte red;
	byte green;
	byte blue;
	byte alpha;
} color_t;

#define COLOR_DEFAULT 255
#define COLOR_FLOAT_MULTIPLIER 255.0f

struct vec3_t;
struct vec4_t;

// initialize a color on the stack with r, g, b, and a components
err_t color_init(color_t* color, byte r, byte g, byte b, byte a);

// initialize a color on the stack with normalized floating point r, g, b, and a components
err_t color_init_rgb(color_t* color, byte r, byte g, byte b);

// initialize a color on the stack with r, g, and b components
err_t color_init_f32(color_t* color, f32 r, f32 g, f32 b, f32 a);

// initialize a color on the stack with normalized floating point r, g, and b components
err_t color_init_rgb_f32(color_t* color, f32 r, f32 g, f32 b);

// allocate and initialize a color on the heap with r, g, b, and a components
err_t color_create(color_t** color_ptr, byte r, byte g, byte b, byte a);

// allocate and initialize a color on the heap with r, g, and b components
err_t color_create_rgb(color_t** color_ptr, byte r, byte g, byte b);

// allocate and initialize a color on the heap with normalized floating point r, g, b, and a components
err_t color_create_f32(color_t** color_ptr, f32 r, f32 g, f32, f32 b);

// allocate and initialize a color on the heap with normalized floating point r, g, and b components
err_t color_create_rgb_f32(color_t** color_ptr, f32 r, f32 g, f32 b);

// convert a color to a normalized vec3
err_t color_to_vec3(const color_t* color, struct vec3_t* vec3);

// convert a color to a normalized vec4
err_t color_to_vec4(const color_t* color, struct vec4_t* vec4);

// mix two colors together
err_t color_mix(const color_t* color_a, const color_t* color_b, color_t* result);

#endif
