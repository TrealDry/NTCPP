#ifndef NUCLEAR_THRONE_CPP_INPUT_MANAGER_HPP
#define NUCLEAR_THRONE_CPP_INPUT_MANAGER_HPP

#include <unordered_map>

#include "SDL3/SDL_keyboard.h"

namespace ntcpp {
    enum class en_keys {
        UP, DOWN, RIGHT, LEFT, FIRE,
        SPEC, PICK, SWAP, PAUSE, YV_AIRHORN,
        DEBUG
    };

    class input_manager {
    public:
        static input_manager& get_instance() {
            static input_manager instance;
            return instance;
        }

        input_manager(input_manager const&)  = delete;
        void operator=(input_manager const&) = delete;

        void update();

        unsigned char get_key_status(en_keys key) {
            if (m_keys.find(key) == m_keys.end()) return 0;

            return m_keys[key];
        }

    private:
        // 0 - nothing; 1 - pressed; 2 - hold; 3 - release;
        std::unordered_map<en_keys, unsigned char> m_keys = {
            {en_keys::UP, 0}, {en_keys::DOWN, 0},
            {en_keys::RIGHT, 0}, {en_keys::LEFT, 0},
            {en_keys::FIRE, 0}, {en_keys::SPEC, 0},
            {en_keys::PICK, 0}, {en_keys::SWAP, 0},
            {en_keys::PAUSE, 0}, {en_keys::YV_AIRHORN, 0},
            {en_keys::DEBUG, 0}
        };

        // F24 - left click, F23 - right click, F22 - mouse wheel up, F21 - mouse wheel down, F20 - middle click
        std::unordered_map<en_keys, std::vector<SDL_Scancode>> m_scan_codes = {
            {en_keys::UP, {SDL_SCANCODE_W, SDL_SCANCODE_UP}},
            {en_keys::DOWN, {SDL_SCANCODE_S, SDL_SCANCODE_DOWN}},
            {en_keys::RIGHT, {SDL_SCANCODE_D, SDL_SCANCODE_RIGHT}},
            {en_keys::LEFT, {SDL_SCANCODE_A, SDL_SCANCODE_LEFT}},
            {en_keys::FIRE, {SDL_SCANCODE_F24, SDL_SCANCODE_F}},
            {en_keys::SPEC, {SDL_SCANCODE_F23, SDL_SCANCODE_G}},
            {en_keys::PICK, {SDL_SCANCODE_E}},
            {en_keys::SWAP, {SDL_SCANCODE_SPACE, SDL_SCANCODE_F22, SDL_SCANCODE_F21, SDL_SCANCODE_F20}},
            {en_keys::PAUSE, {SDL_SCANCODE_ESCAPE}},
            {en_keys::YV_AIRHORN, {SDL_SCANCODE_B}},
            {en_keys::DEBUG, {SDL_SCANCODE_F1}}
        };

    private:
        input_manager() {}
    };
};

#endif
