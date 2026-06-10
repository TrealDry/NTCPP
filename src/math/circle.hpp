#ifndef NUCLEAR_THRONE_CPP_CIRCLE_HPP
#define NUCLEAR_THRONE_CPP_CIRCLE_HPP

namespace ntcpp {
    // miss
    struct Circle {
        float x;
        float y;
        float r;

        static bool overlap(Circle a, Circle b) {
            float dx = a.x - b.x;
            float dy = a.y - b.y;
            float dist2 = dx*dx + dy*dy;
            float rsum = a.r + b.r;
            return dist2 < rsum * rsum;
        }
    };
}

#endif
