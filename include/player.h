#pragma once

#include "engine/color.h"
#include "engine/game.h"
#include "engine/math/shape.h"
#include "engine/math/vector.h"
#include "map.h"

typedef struct player_s
{
	CE_vector2f_t m_position;
	CE_vector2f_t m_acceleration_vec;
	CE_vector2f_t m_velocity;
	CE_rgba_t m_color;
	float m_drag;
	float m_acceleration;
	unsigned int m_box_size;
	void* m_future;
} player_t;

typedef struct
{
	CE_boolean_t m_success;
	CE_vector2f_t m_distance;
} collision_res_tup_t;

extern player_t player_g;

void player_init(player_t*);
void player_cleanup(player_t*);
void player_update(player_t*);
player_t player_update_peek(player_t*);
void player_render(player_t*, float interpolation, CE_app_t* app);
CE_vector2f_t player_collision_origin(player_t* plr);
collision_res_tup_t player_collides_map(player_t*, map_t*);
