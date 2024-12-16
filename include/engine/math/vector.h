#pragma once

typedef struct CE_vector2i_s
{
	int x;
	int y;
} CE_vector2i_t;

typedef struct CE_vector2f_s
{
	float x;
	float y;
} CE_vector2f_t;

typedef struct CE_vector3f_s
{
	float x;
	float y;
	float z;
} CE_vector3f_t;

typedef struct CE_vector4f_s
{
	float x;
	float y;
	float z;
	float w;
} CE_vector4f_t;

CE_vector2f_t CE_vector2f_normalize(CE_vector2f_t* vec);
