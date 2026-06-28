#ifndef NUCLEAR_THRONE_CPP_CIRCLE_HPP
#define NUCLEAR_THRONE_CPP_CIRCLE_HPP

#include "SDL3/SDL_rect.h"
#include <algorithm>

namespace ntcpp {
    // miss
    struct circle {
        float x;
        float y;
        float r;

        static bool overlap(circle a, circle b) {
            float dx = a.x - b.x;
            float dy = a.y - b.y;
            float dist2 = dx*dx + dy*dy;
            float rsum = a.r + b.r;
            return dist2 < rsum * rsum;
        }

        static bool rect_overlap(circle a, SDL_FRect b) {
            float cx = std::clamp(a.x, b.x, b.x + b.w);
            float cy = std::clamp(a.y, b.y, b.y + b.h);

            float dx = a.x - cx;
            float dy = a.y - cy;

            float dist2 = dx*dx + dy*dy;

            return dist2 < a.r * a.r;
        }
    };
}

#endif
