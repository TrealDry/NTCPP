#ifndef NUCLEAR_THRONE_CPP_VEC2_HPP
#define NUCLEAR_THRONE_CPP_VEC2_HPP

#include <cmath>

constexpr float c_PI = 3.1415927f;

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

        static float get_angle(vec2 from, vec2 to) {
            float dx = to.x - from.x;
            float dy = to.y - from.y;
            return std::atan2f(dy, dx);
        }

        static vec2 normalize_angle(float angle) {
            return {std::cos(angle), std::sin(angle)};
        }

        static float rad_to_deg(float angle) {
            return angle * (180.f / c_PI);
        }

        static float deg_to_rad(float angle) {
            return angle * (c_PI / 180.f);
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
