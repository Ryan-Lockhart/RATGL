#include "color.h"

#include "vec3.h"
#include "vec4.h"

#include "stdlib.h"
#include "stdio.h"

err_t color_init(color_t* color, byte r, byte g, byte b, byte a)
{
	if (color == NULL) return error_param_null("color", __FILE__, __LINE__);

	color->red = r;
	color->green = g;
	color->blue = b;
	color->alpha = a;

	return ERROR_NONE;
}

err_t color_init_rgb(color_t* color, byte r, byte g, byte b)
{
	if (color == NULL) error_param_null("color", __FILE__, __LINE__);

	color->red = r;
	color->green = g;
	color->blue = b;
	color->alpha = COLOR_DEFAULT;

	return ERROR_NONE;
}

err_t color_init_f32(color_t* color, f32 r, f32 g, f32 b, f32 a)
{
	if (color == NULL) error_param_null("color", __FILE__, __LINE__);

	if (r > 1.0f) error_color_unnorm("r", __FILE__, __LINE__);
	if (g > 1.0f) error_color_unnorm("g", __FILE__, __LINE__);
	if (b > 1.0f) error_color_unnorm("b", __FILE__, __LINE__);
	if (a > 1.0f) error_color_unnorm("a", __FILE__, __LINE__);

	color->red = (byte)(r * 255);
	color->green = (byte)(g * 255);
	color->blue = (byte)(b * 255);
	color->alpha = (byte)(a * 255);

	return ERROR_NONE;
}

err_t color_init_rgb_f32(color_t* color, f32 r, f32 g, f32 b)
{
	if (color == NULL) error_param_null("color", __FILE__, __LINE__);

	if (r > 1.0f) error_color_unnorm("r", __FILE__, __LINE__);
	if (g > 1.0f) error_color_unnorm("g", __FILE__, __LINE__);
	if (b > 1.0f) error_color_unnorm("b", __FILE__, __LINE__);

	color->red = (byte)(r * COLOR_FLOAT_MULTIPLIER);
	color->green = (byte)(g * COLOR_FLOAT_MULTIPLIER);
	color->blue = (byte)(b * COLOR_FLOAT_MULTIPLIER);
	color->alpha = COLOR_DEFAULT;

	return ERROR_NONE;
}

err_t color_create(color_t** color, byte r, byte g, byte b, byte a)
{
	if (color == NULL) return error_param_null("color", __FILE__, __LINE__);

	(*color)->red = r;
	(*color)->green = g;
	(*color)->blue = b;
	(*color)->alpha = a;

	return ERROR_NONE;
}

err_t color_create_rgb(color_t** color, byte r, byte g, byte b)
{
	if (color == NULL) return error_param_null("color", __FILE__, __LINE__);

	*color = (color_t*)malloc(sizeof(color_t));

	if (*color == NULL) return error_alloc_fail("color_t", sizeof(color_t), __FILE__, __LINE__);

	(*color)->red = r;
	(*color)->green = g;
	(*color)->blue = b;
	(*color)->alpha = COLOR_DEFAULT;

	return ERROR_NONE;
}

err_t color_create_f32(color_t** color, f32 r, f32 g, f32 b, f32 a)
{
	if (color == NULL) error_param_null("color", __FILE__, __LINE__);

	if (r > 1.0f) error_color_unnorm("r", __FILE__, __LINE__);
	if (g > 1.0f) error_color_unnorm("g", __FILE__, __LINE__);
	if (b > 1.0f) error_color_unnorm("b", __FILE__, __LINE__);
	if (a > 1.0f) error_color_unnorm("a", __FILE__, __LINE__);

	(*color)->red = (byte)(r * 255);
	(*color)->green = (byte)(g * 255);
	(*color)->blue = (byte)(b * 255);
	(*color)->alpha = (byte)(a * 255);

	return ERROR_NONE;
}

err_t color_create_rgb_f32(color_t** color, f32 r, f32 g, f32 b)
{
	if (color == NULL) error_param_null("color", __FILE__, __LINE__);

	if (r > 1.0f) error_color_unnorm("r", __FILE__, __LINE__);
	if (g > 1.0f) error_color_unnorm("g", __FILE__, __LINE__);
	if (b > 1.0f) error_color_unnorm("b", __FILE__, __LINE__);

	(*color)->red = (byte)(r * COLOR_FLOAT_MULTIPLIER);
	(*color)->green = (byte)(g * COLOR_FLOAT_MULTIPLIER);
	(*color)->blue = (byte)(b * COLOR_FLOAT_MULTIPLIER);
	(*color)->alpha = COLOR_DEFAULT;

	return ERROR_NONE;
}

err_t color_to_vec3(const color_t* color, vec3_t* vec)
{
	if (color == NULL) error_param_null("color", __FILE__, __LINE__);
	if (vec == NULL) error_param_null("vec", __FILE__, __LINE__);

	vec->x = color->red / COLOR_FLOAT_MULTIPLIER;
	vec->y = color->blue / COLOR_FLOAT_MULTIPLIER;
	vec->z = color->green / COLOR_FLOAT_MULTIPLIER;

	return ERROR_NONE;
}

err_t color_to_vec4(const color_t* color, vec4_t* vec)
{
	if (color == NULL) error_param_null("color", __FILE__, __LINE__);
	if (vec == NULL) error_param_null("vec", __FILE__, __LINE__);

	vec->x = color->red / COLOR_FLOAT_MULTIPLIER;
	vec->y = color->blue / COLOR_FLOAT_MULTIPLIER;
	vec->z = color->green / COLOR_FLOAT_MULTIPLIER;
	vec->w = color->alpha / COLOR_FLOAT_MULTIPLIER;

	return ERROR_NONE;
}

err_t color_mix(const color_t* color_a, const color_t* color_b, color_t* result)
{
	if (color_a == NULL) error_param_null("color_a", __FILE__, __LINE__);
	if (color_b == NULL) error_param_null("color_b", __FILE__, __LINE__);
	if (result == NULL) error_param_null("result", __FILE__, __LINE__);

	// mixing is achieved by adding component wise and shifting the results once right to effectively divide them by two

	result->red = (byte)((color_a->red + color_b->red) >> 1);
	result->green = (byte)((color_a->green + color_b->green) >> 1);
	result->blue = (byte)((color_a->blue + color_b->blue) >> 1);
	result->alpha = (byte)((color_a->alpha + color_b->alpha) >> 1);

	return ERROR_NONE;
}
