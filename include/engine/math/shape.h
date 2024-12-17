#pragma once

#include "engine/game.h"
#include "engine/math/vector.h"
typedef struct
{
	CE_vector2f_t m_origin;
	float m_width;
	float m_height;
} CE_rectangle2f_t;

CE_boolean_t CE_rectangle2f_collide(CE_rectangle2f_t first, CE_rectangle2f_t second);
