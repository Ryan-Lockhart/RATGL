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

	color->red = (byte)((f32)r * COLOR_FLOAT_MULTIPLIER);
	color->green = (byte)((f32)g * COLOR_FLOAT_MULTIPLIER);
	color->blue = (byte)((f32)b * COLOR_FLOAT_MULTIPLIER);
	color->alpha = (byte)((f32)a * COLOR_FLOAT_MULTIPLIER);

	return ERROR_NONE;
}

err_t color_init_rgb_f32(color_t* color, f32 r, f32 g, f32 b)
{
	if (color == NULL) error_param_null("color", __FILE__, __LINE__);

	if (r > 1.0f) error_color_unnorm("r", __FILE__, __LINE__);
	if (g > 1.0f) error_color_unnorm("g", __FILE__, __LINE__);
	if (b > 1.0f) error_color_unnorm("b", __FILE__, __LINE__);

	color->red = (byte)((f32)r * COLOR_FLOAT_MULTIPLIER);
	color->green = (byte)((f32)g * COLOR_FLOAT_MULTIPLIER);
	color->blue = (byte)((f32)b * COLOR_FLOAT_MULTIPLIER);
	color->alpha = COLOR_DEFAULT;

	return ERROR_NONE;
}

err_t color_init_vec3(color_t* color, const vec3_t* vec3)
{
	if (color == NULL) error_param_null("color", __FILE__, __LINE__);
	if (vec3 == NULL) error_param_null("vec3", __FILE__, __LINE__);

	if (vec3->x > 1.0f) error_color_unnorm("vec3->x", __FILE__, __LINE__);
	if (vec3->y > 1.0f) error_color_unnorm("vec3->y", __FILE__, __LINE__);
	if (vec3->z > 1.0f) error_color_unnorm("vec3->z", __FILE__, __LINE__);

	color->red = (byte)((f32)vec3->x * COLOR_FLOAT_MULTIPLIER);
	color->green = (byte)((f32)vec3->y * COLOR_FLOAT_MULTIPLIER);
	color->blue = (byte)((f32)vec3->z * COLOR_FLOAT_MULTIPLIER);
	color->alpha = COLOR_DEFAULT;

	return ERROR_NONE;
}

err_t color_init_vec4(color_t* color, const vec4_t* vec4)
{
	if (color == NULL) error_param_null("color", __FILE__, __LINE__);
	if (vec4 == NULL) error_param_null("vec4", __FILE__, __LINE__);

	if (vec4->x > 1.0f) error_color_unnorm("vec4->x", __FILE__, __LINE__);
	if (vec4->y > 1.0f) error_color_unnorm("vec4->y", __FILE__, __LINE__);
	if (vec4->z > 1.0f) error_color_unnorm("vec4->z", __FILE__, __LINE__);
	if (vec4->w > 1.0f) error_color_unnorm("vec4->w", __FILE__, __LINE__);

	color->red = (byte)((f32)vec4->x * COLOR_FLOAT_MULTIPLIER);
	color->green = (byte)((f32)vec4->y * COLOR_FLOAT_MULTIPLIER);
	color->blue = (byte)((f32)vec4->z * COLOR_FLOAT_MULTIPLIER);
	color->alpha = (byte)((f32)vec4->w * COLOR_FLOAT_MULTIPLIER);

	return ERROR_NONE;
}

err_t color_destroy(color_t** color)
{
	if (color == NULL) error_param_null("color", __FILE__, __LINE__);
	if (*color != NULL) error_param_notnull("*color", __FILE__, __LINE__);

	free(*color);
	*color = NULL;

	return ERROR_NONE;
}

err_t color_create(color_t** color, byte r, byte g, byte b, byte a)
{
	if (color == NULL) return error_param_null("color", __FILE__, __LINE__);

	*color = (color_t*)malloc(sizeof(color_t));

	if (*color == NULL) return error_alloc_fail("color_t", sizeof(color_t), __FILE__, __LINE__);

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

	*color = (color_t*)malloc(sizeof(color_t));

	if (*color == NULL) return error_alloc_fail("color_t", sizeof(color_t), __FILE__, __LINE__);

	(*color)->red = (byte)((f32)r * COLOR_FLOAT_MULTIPLIER);
	(*color)->green = (byte)((f32)g * COLOR_FLOAT_MULTIPLIER);
	(*color)->blue = (byte)((f32)b * COLOR_FLOAT_MULTIPLIER);
	(*color)->alpha = (byte)((f32)a * COLOR_FLOAT_MULTIPLIER);

	return ERROR_NONE;
}

err_t color_create_rgb_f32(color_t** color, f32 r, f32 g, f32 b)
{
	if (color == NULL) error_param_null("color", __FILE__, __LINE__);

	if (r > 1.0f) error_color_unnorm("r", __FILE__, __LINE__);
	if (g > 1.0f) error_color_unnorm("g", __FILE__, __LINE__);
	if (b > 1.0f) error_color_unnorm("b", __FILE__, __LINE__);

	*color = (color_t*)malloc(sizeof(color_t));

	if (*color == NULL) return error_alloc_fail("color_t", sizeof(color_t), __FILE__, __LINE__);

	(*color)->red = (byte)((f32)r * COLOR_FLOAT_MULTIPLIER);
	(*color)->green = (byte)((f32)g * COLOR_FLOAT_MULTIPLIER);
	(*color)->blue = (byte)((f32)b * COLOR_FLOAT_MULTIPLIER);
	(*color)->alpha = COLOR_DEFAULT;

	return ERROR_NONE;
}

err_t color_create_vec3(color_t** color, const vec3_t* vec3)
{
	if (color == NULL) error_param_null("color", __FILE__, __LINE__);
	if (vec3 == NULL) error_param_null("vec3", __FILE__, __LINE__);

	if (vec3->x > 1.0f) error_color_unnorm("vec3->x", __FILE__, __LINE__);
	if (vec3->y > 1.0f) error_color_unnorm("vec3->y", __FILE__, __LINE__);
	if (vec3->z > 1.0f) error_color_unnorm("vec3->z", __FILE__, __LINE__);

	*color = (color_t*)malloc(sizeof(color_t));

	if (*color == NULL) return error_alloc_fail("color_t", sizeof(color_t), __FILE__, __LINE__);

	(*color)->red = (byte)((f32)vec3->x * COLOR_FLOAT_MULTIPLIER);
	(*color)->green = (byte)((f32)vec3->y * COLOR_FLOAT_MULTIPLIER);
	(*color)->blue = (byte)((f32)vec3->z * COLOR_FLOAT_MULTIPLIER);
	(*color)->alpha = COLOR_DEFAULT;

	return ERROR_NONE;
}

err_t color_create_vec4(color_t** color, const vec4_t* vec4)
{
	if (color == NULL) error_param_null("color", __FILE__, __LINE__);
	if (vec4 == NULL) error_param_null("vec4", __FILE__, __LINE__);

	if (vec4->x > 1.0f) error_color_unnorm("vec4->x", __FILE__, __LINE__);
	if (vec4->y > 1.0f) error_color_unnorm("vec4->y", __FILE__, __LINE__);
	if (vec4->z > 1.0f) error_color_unnorm("vec4->z", __FILE__, __LINE__);
	if (vec4->w > 1.0f) error_color_unnorm("vec4->w", __FILE__, __LINE__);

	*color = (color_t*)malloc(sizeof(color_t));

	if (*color == NULL) return error_alloc_fail("color_t", sizeof(color_t), __FILE__, __LINE__);

	(*color)->red = (byte)((f32)vec4->x * COLOR_FLOAT_MULTIPLIER);
	(*color)->green = (byte)((f32)vec4->y * COLOR_FLOAT_MULTIPLIER);
	(*color)->blue = (byte)((f32)vec4->z * COLOR_FLOAT_MULTIPLIER);
	(*color)->alpha = (byte)((f32)vec4->w * COLOR_FLOAT_MULTIPLIER);

	return ERROR_NONE;
}

err_t color_to_vec3(const color_t* color, vec3_t* vec)
{
	if (color == NULL) error_param_null("color", __FILE__, __LINE__);
	if (vec == NULL) error_param_null("vec", __FILE__, __LINE__);

	vec->x = (f32)color->red / COLOR_FLOAT_MULTIPLIER;
	vec->y = (f32)color->blue / COLOR_FLOAT_MULTIPLIER;
	vec->z = (f32)color->green / COLOR_FLOAT_MULTIPLIER;

	return ERROR_NONE;
}

err_t color_to_vec4(const color_t* color, vec4_t* vec)
{
	if (color == NULL) error_param_null("color", __FILE__, __LINE__);
	if (vec == NULL) error_param_null("vec", __FILE__, __LINE__);

	vec->x = (f32)color->red / COLOR_FLOAT_MULTIPLIER;
	vec->y = (f32)color->blue / COLOR_FLOAT_MULTIPLIER;
	vec->z = (f32)color->green / COLOR_FLOAT_MULTIPLIER;
	vec->w = (f32)color->alpha / COLOR_FLOAT_MULTIPLIER;

	return ERROR_NONE;
}

err_t color_mix(const color_t* color_a, const color_t* color_b, color_t* result)
{
	if (color_a == NULL) error_param_null("color_a", __FILE__, __LINE__);
	if (color_b == NULL) error_param_null("color_b", __FILE__, __LINE__);
	if (result == NULL) error_param_null("result", __FILE__, __LINE__);

	// mixing is achieved by adding component wise and shifting the results once right to effectively divide them by two

	result->red = (byte)(((u16)color_a->red + (u16)color_b->red) >> 1);
	result->green = (byte)(((u16)color_a->green + (u16)color_b->green) >> 1);
	result->blue = (byte)(((u16)color_a->blue + (u16)color_b->blue) >> 1);
	result->alpha = (byte)(((u16)color_a->alpha + (u16)color_b->alpha) >> 1);

	return ERROR_NONE;
}

err_t color_reset(color_t* color)
{
	if (color == NULL) return error_param_null("color", __FILE__, __LINE__);

	color->red = COLOR_DEFAULT;
	color->green = COLOR_DEFAULT;
	color->blue = COLOR_DEFAULT;
	color->alpha = COLOR_DEFAULT;

	return ERROR_NONE;
}

extern color_t color_transperant = { 0, 0, 0, 0 }; extern color_t color_white = { 255, 255, 255, 255 }; extern color_t color_black = { 0, 0, 0, 255 };

extern color_t color_light_grey = { 191, 191, 191, 255 }; extern color_t color_grey = { 127, 127, 127, 255 }; extern color_t color_dark_grey = { 63, 63, 63, 255 };

extern color_t color_marble = { 239, 231, 231, 255 }; extern color_t color_intrite = { 111, 103, 103, 255 }; extern color_t color_charcoal = { 39, 31, 31, 255 };

extern color_t color_red = { 255, 0, 0, 255 }; extern color_t color_bright_red = { 191, 0, 0, 255 }; extern color_t color_light_red = { 127, 0, 0, 255 }; extern color_t color_dark_red = { 63, 0, 0, 255 };

extern color_t color_green = { 0, 255, 0, 255 }; extern color_t color_bright_green = { 0, 191, 0, 255 }; extern color_t color_light_green = { 0, 127, 0, 255 }; extern color_t color_dark_green = { 0, 63, 0, 255 };

extern color_t color_blue = { 0, 0, 255, 255 }; extern color_t color_bright_blue = { 0, 0, 191, 255 }; extern color_t color_light_blue = { 0, 0, 127, 255 }; extern color_t color_dark_blue = { 0, 0, 63, 255 };

extern color_t color_cyan = { 0, 255, 255, 255 }; extern color_t color_bright_cyan = { 0, 255, 255, 255 }; extern color_t color_light_cyan = { 0, 127, 127, 255 }; extern color_t color_dark_cyan = { 0, 63, 63, 255 };

extern color_t color_magenta = { 255, 0, 255, 255 }; extern color_t color_bright_magenta = { 255, 0, 255, 255 }; extern color_t color_light_magenta = { 127, 0, 127, 255 }; extern color_t color_dark_magenta = { 63, 0, 63, 255 };

extern color_t color_yellow = { 255, 255, 0, 255 }; extern color_t color_bright_yellow = { 191, 191, 0, 255 }; extern color_t color_light_yellow = { 127, 127, 0, 255 }; extern color_t color_dark_yellow = { 63, 63, 0, 255 };

extern color_t color_orange = { 255, 127, 0, 255 }; extern color_t color_bright_orange = { 191, 96, 0, 255 }; extern color_t color_light_orange = { 127, 63, 0, 255 }; extern color_t color_dark_orange = { 63, 32, 0, 255 };

extern color_t color_blood = { 157, 33, 53, 255 };

extern color_t color_ebony = { 39, 43, 51, 255 }; extern color_t color_ivory = { 255, 255, 239, 255 };

extern color_t color_oak = { 119, 81, 45, 255 }; extern color_t color_willow = { 169, 171, 155, 255 }; extern color_t color_birch = { 233, 225, 215, 255 };

extern color_t color_iron = { 67, 69, 75, 255 }; extern color_t color_steel = { 161, 157, 149, 255 };

extern color_t color_gold = { 255, 215, 0, 255 };

extern color_t color_silver = { 191, 191, 191, 255 };

extern color_t color_copper = { 185, 115, 51, 255 };

extern color_t color_tin = { 145, 145, 145, 255 }; extern color_t color_bronze = { 205, 127, 49, 255 };

extern color_t color_zinc = { 187, 197, 199, 255 }; extern color_t color_brass = { 181, 167, 67, 255 };
