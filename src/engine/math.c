#include "engine/game.h"
#include "engine/math/vector.h"
#include "engine/math/shape.h"
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

CE_vector2f_t CE_vector2f_scalar_mul(CE_vector2f_t vec, float scalar) {
    return (CE_vector2f_t){ vec.x * scalar, vec.y * scalar };
}
CE_vector2f_t CE_vector2f_scalar_add(CE_vector2f_t vec, float scalar) {
    return (CE_vector2f_t){ vec.x + scalar, vec.y + scalar }; }
CE_vector2f_t CE_vector2f_add(CE_vector2f_t vec1, CE_vector2f_t vec2) {
    return (CE_vector2f_t) {vec1.x + vec2.x, vec1.y + vec2.y };
}
float CE_vector2f_dot(CE_vector2f_t vec1, CE_vector2f_t vec2) {
    return vec1.x * vec2.x + vec1.y + vec2.y;
}
CE_boolean_t CE_rectangle2f_collide(CE_rectangle2f_t first, CE_rectangle2f_t second) {
    CE_boolean_t x_overlap = ( second.m_origin.x > first.m_origin.x && first.m_origin.x < second.m_origin.x + second.m_width ) ||
                             ( first.m_origin.x > second.m_origin.x && second.m_origin.x < first.m_origin.x + first.m_width );
    CE_boolean_t y_overlap = ( second.m_origin.y > first.m_origin.y && first.m_origin.y < second.m_origin.y + second.m_height ) ||
                             ( first.m_origin.y > second.m_origin.y && second.m_origin.y < first.m_origin.y + first.m_height );
    return x_overlap && y_overlap;
}
