#include "map.h"
#include <SDL_rect.h>
#include <SDL_render.h>
#include <stdlib.h>
#include <string.h>

map_t map_g = {
    0,
    8,
    8,
    75
};

void map_init(map_t* map, short* tiles) {
    int size = map->m_width * map->m_height;
    map->m_tiles = (short*)calloc(size, sizeof(short));
    memcpy(map->m_tiles, tiles, size * sizeof(short));
}

void map_cleanup(map_t* map) {
    free(map->m_tiles);
    free(map);
}

void map_render(map_t* map, float interpolation, CE_app_t* app) {
    for (int x = 0; x < map->m_height; x++) {
        for (int y = 0; y < map->m_width; y++) {
            if (map->m_tiles[y * map->m_height + x]) {
                SDL_Rect rect = { x * map->m_tile_size, y * map->m_tile_size, map->m_tile_size, map->m_tile_size };
                SDL_SetRenderDrawColor(app->m_renderer, 0, 255, 0, 255);
                SDL_RenderFillRect(app->m_renderer, &rect);
            }
        }
    }
}
