#ifndef NUCLEAR_THRONE_CPP_ANIMATION_MANAGER_HPP
#define NUCLEAR_THRONE_CPP_ANIMATION_MANAGER_HPP

#include <vector>

#include "../animation.hpp"

namespace ntcpp {
    class animation_manager : obj_interface {
    public:
        std::optional<status> init(std::initializer_list<animation*> animations, size_t current_animation);

        void update() override;
        void draw(SDL_Renderer* renderer) override;

        void change_anim(size_t new_anim_index);

        size_t get_current_anim_index() { return m_current_animation; }

        void set_h_flip(bool flip) { m_h_flip = flip; m_animations[m_current_animation].set_h_flip(m_h_flip); }
        bool get_h_flip() { return m_h_flip; }

    private:
        size_t m_current_animation = 0;
        std::vector<animation> m_animations;

        bool m_h_flip = false;
    };
}

#endif
