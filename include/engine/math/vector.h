#pragma once

typedef struct
{
	int x;
	int y;
} CE_vector2i_t;

typedef struct
{
	float x;
	float y;
} CE_vector2f_t;

typedef struct
{
	float x;
	float y;
	float z;
} CE_vector3f_t;

typedef struct
{
	float x;
	float y;
	float z;
	float w;
} CE_vector4f_t;

CE_vector2f_t CE_vector2f_normalize(CE_vector2f_t* vec);
CE_vector2f_t CE_vector2f_scalar_mul(CE_vector2f_t vec, float scalar);
CE_vector2f_t CE_vector2f_scalar_add(CE_vector2f_t vec, float scalar);
CE_vector2f_t CE_vector2f_add(CE_vector2f_t vec1, CE_vector2f_t vec2);
float CE_vector2f_dot(CE_vector2f_t vec1, CE_vector2f_t vec2);
