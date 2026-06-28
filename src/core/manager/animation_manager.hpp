#ifndef NUCLEAR_THRONE_CPP_ANIMATION_MANAGER_HPP
#define NUCLEAR_THRONE_CPP_ANIMATION_MANAGER_HPP

#include <vector>

#include "../animation.hpp"

namespace ntcpp {
    class animation_manager {
    public:
        std::optional<status> init(std::initializer_list<animation*> animations, size_t current_animation);

        void update();
        void draw(SDL_Renderer* renderer, vec2 pos);

        void change_anim(size_t new_anim_index);

        size_t get_current_anim_index() { return m_current_animation; }

        void set_flip(SDL_FlipMode flip) { m_flip = flip; m_animations[m_current_animation].set_flip(m_flip); }
        SDL_FlipMode get_flip() { return m_flip; }

    private:
        size_t m_current_animation = 0;
        std::vector<animation> m_animations;

        SDL_FlipMode m_flip = SDL_FLIP_NONE;
    };
}

#endif
