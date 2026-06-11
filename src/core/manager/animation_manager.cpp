#include "animation_manager.hpp"

namespace ntcpp {
    std::optional<status> animation_manager::init(std::initializer_list<animation*> animations, size_t current_animation) {
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

    void animation_manager::update() {
        m_animations[m_current_animation].update();
    }

    void animation_manager::draw(SDL_Renderer* renderer, vec2 pos) {
        m_animations[m_current_animation].draw(renderer, pos);
    }

    void animation_manager::change_anim(size_t new_anim_index) {
        m_current_animation = new_anim_index;
        m_animations[m_current_animation].set_h_flip(m_h_flip);
    }
}