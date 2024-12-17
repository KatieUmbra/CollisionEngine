#include "engine/game.h"
#include <SDL_events.h>
#include <SDL_timer.h>
#include <stdlib.h>

CE_app_t* CE_app_init(CE_settings_t settings)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
	CE_app_t* app = (CE_app_t*)malloc(sizeof(CE_app_t));
	app->m_window = SDL_CreateWindow(settings.m_window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
									 settings.m_window_size.x, settings.m_window_size.y, settings.m_window_flags);
    app->m_settings = settings;
    app->m_keybindings_down = (CE_keybinding_t*)calloc(256, sizeof(CE_keybinding_t));
    app->m_keybindings_up = (CE_keybinding_t*)calloc(256, sizeof(CE_keybinding_t));
	if (!app->m_window)
	{
		printf("Failed to open %d x %d window: %s\n", settings.m_window_size.x, settings.m_window_size.y,
			   SDL_GetError());
		exit(1);
	}
	if (settings.m_vsync)
	{
		app->m_renderer = SDL_CreateRenderer(app->m_window, -1, settings.m_renderer_flags | SDL_RENDERER_PRESENTVSYNC);
	}
	else
	{
		app->m_renderer = SDL_CreateRenderer(app->m_window, -1, settings.m_renderer_flags);
	}
	if (!app->m_renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	return app;
}

void CE_app_cleanup(CE_app_t *app) {
    free(app->m_keybindings_down);
    free(app->m_keybindings_up);
    free(app);
    app = NULL;
}

void CE_app_register_keydown(CE_app_t* app, SDL_Scancode key, CE_keybinding_t action) {
    app->m_keybindings_down[key] = action;
}
void CE_app_register_keyup(CE_app_t* app, SDL_Scancode key, CE_keybinding_t action) {
    app->m_keybindings_up[key] = action;
}

static void CE_app_keydown(CE_app_t* app, SDL_Event event) {
    CE_keybinding_t action = app->m_keybindings_down[event.key.keysym.scancode];
    if (action == NULL) return;
    action(event);
}
static void CE_app_keyup(CE_app_t* app, SDL_Event event) {
    CE_keybinding_t action = app->m_keybindings_up[event.key.keysym.scancode];
    if (action == NULL) return;
    action(event);
}

// https://dewitters.com/dewitters-gameloop/
void CE_app_run(CE_app_t* app, void (*render)(float interpolation, CE_app_t* app), void (*update)()) {
    CE_miliseconds_t next_game_tick = 0.0;
    int loops;
    float interpolation;
    while(CE_TRUE) {
        loops = 0;
        while (SDL_GetTicks64() > next_game_tick && loops < CE_MAX_FRAMESKIPS) {
            SDL_Event event;
            while(SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_QUIT:
                        exit(1);
                        break;
                    case SDL_KEYDOWN:
                        if (event.key.repeat == SDL_FALSE) {
                            CE_app_keydown(app, event);
                        }
                        break;
                    case SDL_KEYUP:
                        CE_app_keyup(app, event);
                        break;
                    default:
                        break;
                }
            }
            update();
            next_game_tick += CE_SKIP_TICKS;
            loops++;
        }
        interpolation = (CE_SKIP_TICKS + SDL_GetTicks64() - next_game_tick) / CE_SKIP_TICKS;
        SDL_SetRenderDrawColor(
                app->m_renderer,
                app->m_settings.m_clear_color.r,
                app->m_settings.m_clear_color.g, 
                app->m_settings.m_clear_color.b,
                app->m_settings.m_clear_color.a
                );
        SDL_RenderClear(app->m_renderer);
        render(interpolation, app);
        SDL_RenderPresent(app->m_renderer);
    }
}
