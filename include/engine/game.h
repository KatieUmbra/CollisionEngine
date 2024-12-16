#pragma once

#include "engine/color.h"
#include "engine/math/vector.h"
#include <SDL.h>
#include <SDL_scancode.h>

#define CE_TRUE 1
#define CE_FALSE 0
#define CE_NO_FLAGS 0

// https://dewitters.com/dewitters-gameloop/
#define CE_TPS 25
#define CE_MAX_FRAMESKIPS 5
#define CE_SKIP_TICKS 1000.0 / CE_TPS

typedef unsigned long CE_miliseconds_t;
typedef const char* CE_string_t;
typedef int CE_boolean_t;
typedef void (*CE_keybinding_t)(SDL_Event);

typedef struct CE_settings_s
{
	CE_boolean_t m_vsync;
	int m_window_flags;
	CE_string_t m_window_title;
	CE_vector2i_t m_window_size;
	int m_renderer_flags;
	CE_rgba_t m_clear_color;
} CE_settings_t;

typedef struct CE_app_s
{
	SDL_Renderer* m_renderer;
	SDL_Window* m_window;
	CE_settings_t m_settings;
	CE_keybinding_t* m_keybindings_down;
	CE_keybinding_t* m_keybindings_up;
} CE_app_t;

CE_app_t* CE_app_init(CE_settings_t settings);
void CE_app_cleanup(CE_app_t* app);
void CE_app_run(CE_app_t* app, void (*render)(float interpolation, CE_app_t* app), void (*update)());
void CE_app_register_keydown(CE_app_t* app, SDL_Scancode key, CE_keybinding_t action);
void CE_app_register_keyup(CE_app_t* app, SDL_Scancode key, CE_keybinding_t action);
