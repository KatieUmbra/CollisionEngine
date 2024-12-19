#include "engine/game.h"
#include "player.h"
#include "util.h"

CE_vector2i_t WASD_vec = {0, 0};
CE_vector2i_t ARR_vec = {0, 0};

static void press_move_w(SDL_Event _) { WASD_vec.y -= 1; }
static void press_move_a(SDL_Event _) { WASD_vec.x -= 1; }
static void press_move_s(SDL_Event _) { WASD_vec.y += 1; }
static void press_move_d(SDL_Event _) { WASD_vec.x += 1; }

static void press_move_up(SDL_Event _)     { ARR_vec.y -= 1; }
static void press_move_left(SDL_Event _)   { ARR_vec.x -= 1; }
static void press_move_down(SDL_Event _)   { ARR_vec.y += 1; }
static void press_move_right(SDL_Event _)  { ARR_vec.x += 1; }

static void release_move_w(SDL_Event _) { WASD_vec.y += 1; }
static void release_move_a(SDL_Event _) { WASD_vec.x += 1; }
static void release_move_s(SDL_Event _) { WASD_vec.y -= 1; }
static void release_move_d(SDL_Event _) { WASD_vec.x -= 1; }

static void release_move_up(SDL_Event _)   { ARR_vec.y += 1; }
static void release_move_left(SDL_Event _) { ARR_vec.x += 1; }
static void release_move_down(SDL_Event _) { ARR_vec.y -= 1; }
static void release_move_right(SDL_Event _){ ARR_vec.x -= 1; }

static void reset_position(SDL_Event _) { player_g.m_position.x = 100.0f, player_g.m_position.y = 100.0f; }

void register_keybindings(CE_app_t* app) {
    CE_app_register_keydown(app, SDL_SCANCODE_R, reset_position);

    CE_app_register_keydown(app, SDL_SCANCODE_W, press_move_w);
    CE_app_register_keydown(app, SDL_SCANCODE_A, press_move_a);
    CE_app_register_keydown(app, SDL_SCANCODE_S, press_move_s);
    CE_app_register_keydown(app, SDL_SCANCODE_D, press_move_d);

    CE_app_register_keydown(app, SDL_SCANCODE_UP, press_move_up);
    CE_app_register_keydown(app, SDL_SCANCODE_LEFT, press_move_left);
    CE_app_register_keydown(app, SDL_SCANCODE_DOWN, press_move_down);
    CE_app_register_keydown(app, SDL_SCANCODE_RIGHT, press_move_right);

    CE_app_register_keyup(app, SDL_SCANCODE_W, release_move_w);
    CE_app_register_keyup(app, SDL_SCANCODE_A, release_move_a);
    CE_app_register_keyup(app, SDL_SCANCODE_S, release_move_s);
    CE_app_register_keyup(app, SDL_SCANCODE_D, release_move_d);

    CE_app_register_keyup(app, SDL_SCANCODE_UP, release_move_up);
    CE_app_register_keyup(app, SDL_SCANCODE_LEFT, release_move_left);
    CE_app_register_keyup(app, SDL_SCANCODE_DOWN, release_move_down);
    CE_app_register_keyup(app, SDL_SCANCODE_RIGHT, release_move_right);
}
