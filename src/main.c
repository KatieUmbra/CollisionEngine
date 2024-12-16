// Engine headers
#include "engine/game.h"
#include "engine/math/vector.h"
#include "util.h"

// Stl headers
#include <memory.h>
#include <stdint.h>

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

#define BOX_SIZE 50

#define SPEED 100.0f
#define SPEED_PER_TICK SPEED / (float)CE_TPS

static CE_vector2f_t position = {0.0f, 0.0f};
CE_vector2f_t acceleration = {0.0f, 0.0f};
static CE_vector2f_t normalized = {0.0f, 0.0f};
static CE_rgba_t color = {255, 255, 255, 255};

void update() {
        normalized = CE_vector2f_normalize(&acceleration);
        position.x += normalized.x * SPEED_PER_TICK;
        position.y += normalized.y * SPEED_PER_TICK;
}

void render(float interpolation, CE_app_t* app) {
        SDL_Rect rect = {position.x + (normalized.x * interpolation), position.y + (normalized.y * interpolation), BOX_SIZE, BOX_SIZE};
        color.g *= -1;
        SDL_SetRenderDrawColor(app->m_renderer, 255, color.g, 255, 255);
        SDL_RenderFillRect(app->m_renderer, &rect);
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
    register_keybindings(app);
    CE_app_run(app, render, update);
    CE_app_cleanup(app);
    return 0;
}
