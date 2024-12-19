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

static CE_boolean_t CE_rectangle2f_collide_vec(CE_rectangle2f_t rec, CE_vector2f_t vec) {
    return rec.m_origin.x < vec.x && vec.x < ( rec.m_origin.x + rec.m_width ) &&
            rec.m_origin.y < vec.y && vec.y < ( rec.m_origin.y + rec.m_height );
}

CE_boolean_t CE_rectangle2f_collide(CE_rectangle2f_t first, CE_rectangle2f_t second) {
    CE_boolean_t a = CE_rectangle2f_collide_vec(second, first.m_origin);
    CE_boolean_t b = CE_rectangle2f_collide_vec(second, (CE_vector2f_t) {first.m_origin.x + first.m_width, first.m_origin.y});
    CE_vector2f_t test = (CE_vector2f_t) { first.m_origin.x + first.m_width, first.m_origin.y + first.m_height };    CE_boolean_t c = CE_rectangle2f_collide_vec(second, test);
    CE_boolean_t d = CE_rectangle2f_collide_vec(second, (CE_vector2f_t) {first.m_origin.x, first.m_origin.y +  first.m_height});
    return  a || b || c || d;
}
