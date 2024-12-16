#include "engine/math/vector.h"
#include <SDL_timer.h>
#include <math.h>

CE_vector2f_t CE_vector2f_normalize(CE_vector2f_t* vec) {
    float length = sqrtf(vec->x * vec->x + vec->y * vec->y);
    if (length == 0.0f) {
        CE_vector2f_t returned = {0.0f, 0.0f};
        return returned;
    }
    CE_vector2f_t normalized = {vec->x / length, vec->y / length};
    return normalized;
}
