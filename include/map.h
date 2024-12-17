#pragma once

#include "engine/game.h"

typedef struct
{
	short* m_tiles;
	int m_height;
	int m_width;
	int m_tile_size;
} map_t;

extern map_t map_g;

void map_init(map_t*, short*);
void map_cleanup(map_t*);
void map_render(map_t* map, float interpolation, CE_app_t* app);
