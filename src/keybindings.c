#include "engine/game.h"
#include "util.h"

#define SPEED 100.0f
#define SPEED_PER_TICK SPEED / (float)CE_TPS

void press_move_up(SDL_Event _) { acceleration.y -= SPEED_PER_TICK; }
void press_move_down(SDL_Event _) { acceleration.y += SPEED_PER_TICK; }
void press_move_right(SDL_Event _) { acceleration.x += SPEED_PER_TICK; }
void press_move_left(SDL_Event _) { acceleration.x -= SPEED_PER_TICK; }

void release_move_up(SDL_Event _) { acceleration.y += SPEED_PER_TICK; }
void release_move_down(SDL_Event _) { acceleration.y -= SPEED_PER_TICK; }
void release_move_right(SDL_Event _) { acceleration.x -= SPEED_PER_TICK; }
void release_move_left(SDL_Event _) { acceleration.x += SPEED_PER_TICK; }

void register_keybindings(CE_app_t* app) {
    CE_app_register_keydown(app, SDL_SCANCODE_W, press_move_up);
    CE_app_register_keydown(app, SDL_SCANCODE_A, press_move_left);
    CE_app_register_keydown(app, SDL_SCANCODE_S, press_move_down);
    CE_app_register_keydown(app, SDL_SCANCODE_D, press_move_right);

    CE_app_register_keydown(app, SDL_SCANCODE_UP, press_move_up);
    CE_app_register_keydown(app, SDL_SCANCODE_DOWN, press_move_down);
    CE_app_register_keydown(app, SDL_SCANCODE_LEFT, press_move_left);
    CE_app_register_keydown(app, SDL_SCANCODE_RIGHT, press_move_right);

    CE_app_register_keyup(app, SDL_SCANCODE_W, release_move_up);
    CE_app_register_keyup(app, SDL_SCANCODE_A, release_move_left);
    CE_app_register_keyup(app, SDL_SCANCODE_S, release_move_down);
    CE_app_register_keyup(app, SDL_SCANCODE_D, release_move_right);

    CE_app_register_keyup(app, SDL_SCANCODE_UP, release_move_up);
    CE_app_register_keyup(app, SDL_SCANCODE_LEFT, release_move_left);
    CE_app_register_keyup(app, SDL_SCANCODE_DOWN, release_move_down);
    CE_app_register_keyup(app, SDL_SCANCODE_RIGHT, release_move_right);
}
