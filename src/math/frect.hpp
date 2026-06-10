#ifndef NUCLEAR_THRONE_CPP_FRECT_HPP
#define NUCLEAR_THRONE_CPP_FRECT_HPP

#include "SDL3/SDL_rect.h"
#include "vec2.hpp"

inline SDL_FRect addiction(SDL_FRect a, SDL_FRect b) {
    return {a.x + b.x, a.y + b.y, a.w + b.w, a.h + b.h};
}

inline SDL_FRect vec2_addiction(SDL_FRect a, ntcpp::vec2 b) {
    return {a.x + b.x, a.y + b.y, a.w, a.h};
}

#endif
