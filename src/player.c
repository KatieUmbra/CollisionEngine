#include "player.h"
#include "engine/game.h"
#include "engine/math/shape.h"
#include "engine/math/vector.h"
#include "map.h"
#include "util.h"

// SDL headers
#include <SDL_rect.h>
#include <SDL_render.h>

// Std headers
#include <stdlib.h>

player_t player_g = {
    {100.0f, 100.0f},
    {0.0f, 0.0f},
    {0.0f, 0.0f},
    {255, 255, 255, 255},
    0.6,
    100.0f,
    50
};

void player_init(player_t* plr) {
    plr->m_future = (player_t*)malloc(sizeof(player_t));
}

void player_cleanup(player_t* plr) {
    free(plr->m_future);
    free(plr);
}

static void player_update_acc_vec(player_t* plr) {
    if (WASD_vec.x * WASD_vec.x >= ARR_vec.x * ARR_vec.x) {
        plr->m_acceleration_vec.x = WASD_vec.x * plr->m_acceleration;
    } else {
        plr->m_acceleration_vec.x = ARR_vec.x * plr->m_acceleration;
    } 
    if (WASD_vec.y * WASD_vec.y >= ARR_vec.y * ARR_vec.y) {
        plr->m_acceleration_vec.y = WASD_vec.y * plr->m_acceleration;
    } else {
        plr->m_acceleration_vec.y = ARR_vec.y * plr->m_acceleration;
    } 
}

void player_update(player_t* plr) {
    plr->m_position = CE_vector2f_add(plr->m_position, plr->m_velocity);
    player_update_acc_vec(plr);
    CE_vector2f_t normalized = CE_vector2f_normalize(&plr->m_acceleration_vec);
    plr->m_velocity = CE_vector2f_add(
            plr->m_velocity, 
            CE_vector2f_scalar_mul(normalized, plr->m_acceleration / CE_TPS)
            );
    collision_res_tup_t collision_data = {CE_FALSE, {0.0f, 0.0f}};
    if (plr->m_future != 0) {
        *(player_t*)plr->m_future = player_update_peek(plr);
        collision_data = player_collides_map((player_t*)plr->m_future, &map_g);
    }
    if (collision_data.m_success) {
        /*
        plr->m_velocity = (CE_vector2f_t) {
            CE_clamp_2b(0, plr->m_velocity.x, collision_data.m_distance.x),
            CE_clamp_2b(0, plr->m_velocity.y, collision_data.m_distance.y),
        };
        */
        plr->m_velocity = (CE_vector2f_t) {0.0f, 0.0f};
    }
    plr->m_velocity = CE_vector2f_scalar_mul(plr->m_velocity, plr->m_drag);
}

player_t player_update_peek(player_t* plr) {
    player_t new_player = *plr;
    new_player.m_future = 0;
    new_player.m_color.g = 0;
    player_update(&new_player);
    return new_player;
}

void player_render(player_t* plr, float interpolation, CE_app_t* app) {
    CE_vector2f_t interpolated_vel = CE_vector2f_scalar_mul(plr->m_velocity, interpolation);
    CE_vector2f_t interpolated_pos = CE_vector2f_add(plr->m_position, interpolated_vel);
    SDL_Rect rect = { interpolated_pos.x, interpolated_pos.y, plr->m_box_size, plr->m_box_size};
    SDL_SetRenderDrawColor(app->m_renderer, plr->m_color.r, plr->m_color.g, plr->m_color.b, plr->m_color.a);
    SDL_RenderFillRect(app->m_renderer, &rect);
}

CE_vector2f_t player_collision_origin(player_t* plr) {
    float half_box = plr->m_box_size / 2.0f;
    return (CE_vector2f_t) { plr->m_position.x + half_box, plr->m_position.y + half_box };
}

collision_res_tup_t player_collides_map(player_t* plr, map_t* map) {
    collision_res_tup_t result = {CE_FALSE, {0.0f, 0.0f}};
    CE_rectangle2f_t plr_rect = {plr->m_position, plr->m_box_size, plr->m_box_size};
    for (int x = 0; x < map->m_height; x++) {
        for (int y = 0; y < map->m_width; y++) {
            int index = y * map->m_height + x;
            if (map->m_tiles[index] == 1) {
                CE_rectangle2f_t map_rect = {
                    {x * map->m_tile_size, y * map->m_tile_size}, 
                    map->m_tile_size, 
                    map->m_tile_size 
                };
                CE_boolean_t rect_collide = CE_rectangle2f_collide(plr_rect, map_rect);
                if (rect_collide) {
                    if (WASD_vec.x > 0) {
                        result.m_distance.x = map_rect.m_origin.x - plr->m_position.x;
                    } else if (WASD_vec.x < 0) {
                        result.m_distance.x = map_rect.m_origin.x + map_rect.m_width - plr->m_position.x;
                        result.m_distance.x *= -1;
                    }
                    if (WASD_vec.y > 0) {
                        result.m_distance.y = map_rect.m_origin.y - plr->m_position.y;
                    } else if (WASD_vec.y < 0) {
                        result.m_distance.y = map_rect.m_origin.y + map_rect.m_height - plr->m_position.y;
                        result.m_distance.y *= -1;
                    }
                }
                result.m_success = result.m_success || rect_collide;
            }
        }
    }
    return result;
}
