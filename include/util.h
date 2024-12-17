#pragma once

#include "engine/game.h"
#include "engine/math/vector.h"

extern CE_vector2i_t WASD_vec;
extern CE_vector2i_t ARR_vec;

void register_keybindings(CE_app_t* app);
