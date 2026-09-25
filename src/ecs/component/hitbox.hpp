#ifndef NUCLEAR_THRONE_CPP_HITBOX_HPP
#define NUCLEAR_THRONE_CPP_HITBOX_HPP

#include "SDL3/SDL_rect.h"

#include "../../math/circle.hpp"

struct RectHitbox {
    SDL_FRect rect;
};

struct CircleHitbox {
    ntcpp::circle circle;
};

#endif
