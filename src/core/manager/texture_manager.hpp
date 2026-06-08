#ifndef NUCLEAR_THRONE_CPP_TEXTURE_MANAGER_HPP
#define NUCLEAR_THRONE_CPP_TEXTURE_MANAGER_HPP

#include <array>
#include <optional>
#include <filesystem>
#include <unordered_map>

#include "../status.hpp"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"

namespace fs = std::filesystem;

namespace ntcpp {
    using sprite_data = std::pair<SDL_FRect, unsigned char>;

    class texture_manager {
    public:
        static texture_manager& get_instance() {
            static texture_manager instance;
            return instance;
        }

        texture_manager(texture_manager const&) = delete;
        void operator=(texture_manager const&)  = delete;

        std::optional<status> init(SDL_Renderer* renderer);

        std::optional<sprite_data> get_sprite(const std::string& name);
        std::optional<SDL_Texture*> get_texture(unsigned char index);

    private:
        std::unordered_map<std::string, sprite_data> m_sprites = {};
        std::array<SDL_Texture*, 256> m_textures = {};

    private:
        texture_manager() {}

        bool json_parse(const fs::path& path_to_file, unsigned char texture_index);
    };
}

#endif
