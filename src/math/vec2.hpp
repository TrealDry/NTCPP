#ifndef NUCLEAR_THRONE_CPP_VEC2_HPP
#define NUCLEAR_THRONE_CPP_VEC2_HPP

#include <cmath>
#include <complex>

namespace ntcpp {
    struct vec2 {
        float x;
        float y;

        vec2(float x, float y) : x(x), y(y) {}
        vec2() : x(0.f), y(0.f) {}

        static vec2 normalize(const vec2& other) {
            vec2 result;
            float len = std::sqrt(other.x * other.x + other.y * other.y);

            if (len > 0.f) {
                result.x = other.x / len;
                result.y = other.y / len;
            }

            return result;
        }

        static float distance(vec2 from, vec2 to) {
            float dx = to.x - from.x;
            float dy = to.y - from.y;
            return std::sqrtf(dx*dx + dy*dy);
        }

        vec2 operator+(const vec2& other) const {
            return {x + other.x, y + other.y};
        }

        vec2 operator-(const vec2& other) const {
            return {x - other.x, y - other.y};
        }

        vec2 operator/(const vec2& other) const {
            return {x / other.x, y / other.y};
        }

        vec2 operator*(const vec2& other) const {
            return {x * other.x, y * other.y};
        }

        vec2 operator*(float num) const {
            return {x * num, y * num};
        }

        vec2& operator+=(const vec2& other) {
            x += other.x;
            y += other.y;
            return *this;
        }

        vec2& operator-=(const vec2& other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        vec2& operator/=(const vec2& other) {
            x /= other.x;
            y /= other.y;
            return *this;
        }

        vec2& operator*=(const vec2& other) {
            x *= other.x;
            y *= other.y;
            return *this;
        }

        vec2& operator/=(const float num) {
            x /= num;
            y /= num;
            return *this;
        }

        bool operator==(const vec2& other) const {
            return x == other.x && y == other.y;
        }
    };
}

#endif
