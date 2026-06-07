#ifndef NUCLEAR_THRONE_CPP_ANIMATION_MANAGER_HPP
#define NUCLEAR_THRONE_CPP_ANIMATION_MANAGER_HPP

#include <vector>

#include "animation.hpp"

namespace ntcpp {
    class animation_manager : obj_interface {
    public:
        std::optional<status> init(std::initializer_list<animation*> animations, size_t current_animation) {
            for (auto& anim : animations) {
                anim->play();
                m_animations.push_back(*anim);
            }

            m_current_animation = current_animation;
            if (m_current_animation >= m_animations.size()) {
                return status{
                    en_status::NOT_OK,
                    "wrong anim index: " + std::to_string(m_current_animation)
                };
            }

            return std::nullopt;
        }

        void update() override {
            m_animations[m_current_animation].update();
        }

        void draw(SDL_Renderer* renderer) override {
            m_animations[m_current_animation].draw(renderer);
        }

        void change_anim(size_t new_anim_index) {
            m_current_animation = new_anim_index;
            m_animations[m_current_animation].set_h_flip(m_h_flip);
        }

        size_t get_current_anim_index() { return m_current_animation; }

        void set_h_flip(bool flip) {
            m_h_flip = flip;
            m_animations[m_current_animation].set_h_flip(m_h_flip);
        }
        bool get_h_flip() { return m_h_flip; }

    private:
        size_t m_current_animation = 0;
        std::vector<animation> m_animations;

        bool m_h_flip = false;
    };
}

#endif
