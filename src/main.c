// Engine headers
#include "engine/game.h"
#include "player.h"
#include "util.h"
#include "map.h"

// Stl headers
#include <SDL_render.h>
#include <memory.h>
#include <stdint.h>

static short map_tiles[8][8] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
};

void update() {
    player_update(&player_g);
}

void render(float interpolation, CE_app_t* app) {
    player_render((player_t*)player_g.m_future, interpolation, app);
    player_render(&player_g, interpolation, app);
    map_render(&map_g, interpolation, app);
}

int main() {
    CE_settings_t app_settings = {
        CE_TRUE,
        CE_NO_FLAGS,
        "Hello SDL!",
        {1280, 720},
        SDL_RENDERER_ACCELERATED,
        {0, 0, 0, 255}
    };
    CE_app_t* app = CE_app_init(app_settings);

    player_init(&player_g);
    map_init(&map_g, (short*)&map_tiles[0]);

    register_keybindings(app);
    CE_app_run(app, render, update);

    CE_app_cleanup(app);
    player_cleanup(&player_g);
    map_cleanup(&map_g);
    return 0;
}
