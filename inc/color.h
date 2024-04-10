#ifndef COLOR_H

#define COLOR_H

#include "typedef.h"
#include "error.h"

/// <summary>a 32-bit structure representing the red, green, blue, and alpha channels of a color</summary>
typedef struct color_t {
	byte red;
	byte green;
	byte blue;
	byte alpha;
} color_t;

#define COLOR_DEFAULT 0
#define COLOR_FLOAT_MULTIPLIER 255.0f

struct vec3_t;
struct vec4_t;

/// <summary>
/// initialize a color on the stack with r, g, b, and a components
/// </summary>
/// <param name="color">- address of the uninitialized color</param>
/// <param name="r">- 8-bit red component of the color</param>
/// <param name="g">- 8-bit green component of the color</param>
/// <param name="b">- 8-bit blue component of the color</param>
/// <param name="a">- 8-bit alpha component of the color</param>
/// <returns>
/// ERROR_NONE on success, ERROR_PARAM_NULL on failure
/// </returns>
err_t color_init(color_t* color, byte r, byte g, byte b, byte a);

/// <summary>
/// initialize a color on the stack with normalized floating point r, g, b, and a components
/// </summary>
/// <param name="color">- address of the uninitialized color</param>
/// <param name="r">- 8-bit red component of the color</param>
/// <param name="g">- 8-bit green component of the color</param>
/// <param name="b">- 8-bit blue component of the color</param>
/// <returns>
/// ERROR_NONE on success, ERROR_PARAM_NULL on failure
/// </returns>
err_t color_init_rgb(color_t* color, byte r, byte g, byte b);

/// <summary>
/// initialize a color on the stack with normalized floating point r, g, b, and a components
/// </summary>
/// <param name="color">- address of the uninitialized color</param>
/// <param name="r">- normalized 32-bit floating point red component of the color</param>
/// <param name="g">- normalized 32-bit floating point green component of the color</param>
/// <param name="b">- normalized 32-bit floating point blue component of the color</param>
/// <param name="a">- normalized 32-bit floating point alpha component of the color</param>
/// <returns>
/// ERROR_NONE on success, ERROR_PARAM_NULL or ERROR_UNNORM_COLOR on failure
/// </returns>
err_t color_init_f32(color_t* color, f32 r, f32 g, f32 b, f32 a);

/// <summary>
/// initialize a color on the stack with normalized floating point r, g, and b components
/// </summary>
/// <param name="color">- address of the uninitialized color</param>
/// <param name="r">- normalized 32-bit floating point red component of the color</param>
/// <param name="g">- normalized 32-bit floating point green component of the color</param>
/// <param name="b">- normalized 32-bit floating point blue component of the color</param>
/// <returns>
/// ERROR_NONE on success, ERROR_PARAM_NULL or ERROR_UNNORM_COLOR on failure
/// </returns>
err_t color_init_rgb_f32(color_t* color, f32 r, f32 g, f32 b);

/// <summary>
/// initialize a color on the stack with a normalized vec3
/// </summary>
/// <param name="color">- address of the uninitialized color</param>
/// <param name="vec3">- normalized x, y, and z components of vec3 for r, g, and, b components of color</param>
/// <returns>
/// ERROR_NONE on success, ERROR_PARAM_NULL or ERROR_UNNORM_COLOR on failure
/// </returns>
err_t color_init_vec3(color_t* color, const struct vec3_t* vec3);

/// <summary>
/// initialize a color on the stack with a normalized vec4
/// </summary>
/// <param name="color">- address of the uninitialized color</param>
/// <param name="vec4">- normalized x, y, z, and w components of vec4 for r, g, b, and a components of color</param>
/// <returns>
/// ERROR_NONE on success, ERROR_PARAM_NULL or ERROR_UNNORM_COLOR on failure
/// </returns>
err_t color_init_vec4(color_t* color, const struct vec4_t* vec3);

/// <summary>
/// deallocate a color on the heap
/// </summary>
/// <param name="color">- address of the allocated color pointer</param>
/// <returns>
/// ERROR_NONE on success, ERROR_PARAM_NULL or ERROR_PARAM_NOTNULL on failure
/// </returns>
err_t color_destroy(color_t** color);

/// <summary>
/// allocate and initialize a color on the heap with r, g, b, and a components
/// </summary>
/// <param name="color">- address of the uninitialized color pointer</param>
/// <param name="r">- 8-bit red component of the color</param>
/// <param name="g">- 8-bit green component of the color</param>
/// <param name="b">- 8-bit blue component of the color</param>
/// <param name="a">- 8-bit alpha component of the color</param>
/// <returns>
/// ERROR_NONE on success, ERROR_PARAM_NULL or ERROR_PARAM_NOTNULL on failure
/// </returns>
err_t color_create(color_t** color_ptr, byte r, byte g, byte b, byte a);

/// <summary>
/// allocate and initialize a color on the heap with r, g, and b components
/// </summary>
/// <param name="color">- address of the uninitialized color pointer</param>
/// <param name="r">- 8-bit red component of the color</param>
/// <param name="g">- 8-bit green component of the color</param>
/// <param name="b">- 8-bit blue component of the color</param>
/// <returns>
/// ERROR_NONE on success, ERROR_PARAM_NULL or ERROR_PARAM_NOTNULL on failure
/// </returns>
err_t color_create_rgb(color_t** color_ptr, byte r, byte g, byte b);

/// <summary>
/// allocate and initialize a color on the heap with normalized floating point r, g, b, and a components
/// </summary>
/// <param name="color">- address of the uninitialized color pointer</param>
/// <param name="r">- normalized 32-bit floating point red component of the color</param>
/// <param name="g">- normalized 32-bit floating point green component of the color</param>
/// <param name="b">- normalized 32-bit floating point blue component of the color</param>
/// <param name="a">- normalized 32-bit floating point alpha component of the color</param>
/// <returns>
/// ERROR_NONE on success, ERROR_PARAM_NULL, ERRPR_PARAM_NOTNULL or ERROR_UNNORM_COLOR on failure
/// </returns>
err_t color_create_f32(color_t** color_ptr, f32 r, f32 g, f32, f32 b);

/// <summary>
/// allocate and initialize a color on the heap with normalized floating point r, g, and b components
/// </summary>
/// <param name="color">- address of the uninitialized color pointer</param>
/// <param name="r">- normalized 32-bit floating point red component of the color</param>
/// <param name="g">- normalized 32-bit floating point green component of the color</param>
/// <param name="b">- normalized 32-bit floating point blue component of the color</param>
/// <returns>
/// ERROR_NONE on success, ERROR_PARAM_NULL, ERRPR_PARAM_NOTNULL or ERROR_UNNORM_COLOR on failure
/// </returns>
err_t color_create_rgb_f32(color_t** color_ptr, f32 r, f32 g, f32 b);

/// <summary>
/// initialize a color on the stack with a normalized vec3
/// </summary>
/// <param name="color">- address of the uninitialized color</param>
/// <param name="vec3">- normalized x, y, and z components of vec3 for r, g, and, b components of color</param>
/// <returns>
/// ERROR_NONE on success, ERROR_PARAM_NULL, ERROR_PARAM_NOTNULL or ERROR_UNNORM_COLOR on failure
/// </returns>
err_t color_create_vec3(color_t** color, const struct vec3_t* vec3);

/// <summary>
/// initialize a color on the stack with a normalized vec4
/// </summary>
/// <param name="color">- address of the uninitialized color</param>
/// <param name="vec4">- normalized x, y, z, and w components of vec4 for r, g, b, and a components of color</param>
/// <returns>
/// ERROR_NONE on success, ERROR_PARAM_NULL, ERROR_PARAM_NOTNULL or ERROR_UNNORM_COLOR on failure
/// </returns>
err_t color_create_vec4(color_t** color, const struct vec4_t* vec3);

/// <summary>
/// convert a color's components to normalized floating points to initialize a vec3
/// </summary>
/// <param name="color>- the color to be converted</param>
/// <param name="vec3">- the vec3 to be initialized</param>
/// <returns>
/// ERROR_NONE on success, ERROR_PARAM_NULL on failure
/// </returns>
err_t color_to_vec3(const color_t* color, struct vec3_t* vec3);

/// <summary>
/// convert a color's components to normalized floating points to initialize a vec4
/// </summary>
/// <param name="color>- the color to be converted</param>
/// <param name="vec4">- the vec4 to be initialized</param>
/// <returns>
/// ERROR_NONE on success, ERROR_PARAM_NULL on failure
/// </returns>
err_t color_to_vec4(const color_t* color, struct vec4_t* vec4);

/// <summary>
/// mix two colors together and initialize a third with their results
/// </summary>
/// <param name="color_a">- the first color to be mixed</param>
/// <param name="color_b">- the second color to be mixed</param>
/// <param name="result">- the result of the two colors mixed</param>
/// <returns>
/// ERROR_NONE on success, ERROR_PARAM_NULL on failure
/// </returns>
err_t color_mix(const color_t* color_a, const color_t* color_b, color_t* result);

/// <summary>
/// resets a color's r, g, b, and a components to their defaults
/// </summary>
/// <param name="color">- address of the color</param>
/// <returns>
/// ERROR_NONE on success, ERROR_PARAM_NULL on failure
/// </returns>
err_t color_reset(color_t* color);

extern color_t color_transperant; extern color_t color_white; extern color_t color_black;

extern color_t color_grey; extern color_t color_light_grey; extern color_t color_dark_grey;

extern color_t color_marble; extern color_t color_intrite; extern color_t color_charcoal;

extern color_t color_red; extern color_t color_bright_red; extern color_t color_light_red; extern color_t color_dark_red;

extern color_t color_green; extern color_t color_bright_green; extern color_t color_light_green; extern color_t color_dark_green;

extern color_t color_blue; extern color_t color_bright_blue; extern color_t color_light_blue; extern color_t color_dark_blue;

extern color_t color_cyan; extern color_t color_bright_cyan; extern color_t color_light_cyan; extern color_t color_dark_cyan;

extern color_t color_magenta; extern color_t color_bright_magenta; extern color_t color_light_magenta; extern color_t color_dark_magenta;

extern color_t color_yellow; extern color_t color_bright_yellow; extern color_t color_light_yellow; extern color_t color_dark_yellow;

extern color_t color_orange; extern color_t color_bright_orange; extern color_t color_light_orange; extern color_t color_dark_orange;

extern color_t color_blood;

extern color_t color_ebony; extern color_t color_ivory;

extern color_t color_oak; extern color_t color_willow; extern color_t color_birch;

extern color_t color_iron; extern color_t color_steel;

extern color_t color_gold; extern color_t color_silver; extern color_t color_copper;

extern color_t color_tin; extern color_t color_bronze;

extern color_t color_zinc; extern color_t color_brass;

#endif
