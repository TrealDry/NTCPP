#include "texture_manager.hpp"
#include "nlohmann/json.hpp"

#define QOI_IMPLEMENTATION
#include "qoi.h"

#include <fstream>

namespace fs = std::filesystem;
using json = nlohmann::json;

namespace ntcpp {
    std::optional<status> texture_manager::init(SDL_Renderer* renderer) {
        fs::path dir = "assets\\textures";
        std::unordered_map<unsigned char, std::pair<fs::path, fs::path>> texture_pairs;

        if (!fs::exists(dir) || !fs::is_directory(dir)) {
            return status{
                en_status::NOT_OK, "directory doesn't exist"
            };
        }

        for (const auto& entry : fs::directory_iterator(dir)) {
            auto filename = entry.path().stem().string();
            auto ext = entry.path().extension().string();

            if (filename == ".gitkeep") continue;

            unsigned char index = std::atoi(filename.c_str());

            if (texture_pairs.find(index) != texture_pairs.end()) {  // if index exist
                if (ext == ".json") {
                    texture_pairs.at(index).first = entry.path();
                } else {
                    texture_pairs.at(index).second = entry.path();
                }
            } else {
                if (ext == ".json") {
                    texture_pairs[index] = {entry.path(), fs::path{}};
                } else {
                    texture_pairs[index] = {fs::path{}, entry.path()};
                }
            }
        }

        for (const auto& [index, pair] : texture_pairs) {
            const auto& [json, qoi] = pair;

            if (!json_parse(json, index)) {
                return status{
                    en_status::NOT_OK, "invalid json: " + json.string()
                };
            }

            qoi_desc desc;
            void* pixels = qoi_read(qoi.u8string().c_str(), &desc, 4);
            if (!pixels) {
                return status{
                    en_status::NOT_OK, "invalid qoi: " + qoi.string()
                };
            }

            auto* surface = SDL_CreateSurfaceFrom(
                (int)desc.width, (int)desc.height, SDL_PIXELFORMAT_RGBA32, pixels, (int)desc.width * 4
            );
            m_textures[index] = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_DestroySurface(surface);

            SDL_SetTextureScaleMode(m_textures[index], SDL_SCALEMODE_NEAREST);
        }

        return std::nullopt;
    }

    std::optional<sprite_data> texture_manager::get_sprite(const std::string& name) {
        if (m_sprites.find(name) == m_sprites.end()) return std::nullopt;

        return m_sprites[name];
    }

    std::optional<SDL_Texture*> texture_manager::get_texture(unsigned char index) {
        if (!m_textures[index]) return std::nullopt;

        return m_textures[index];
    }

    bool texture_manager::json_parse(const fs::path& path_to_file, unsigned char texture_index) {
        std::ifstream f(path_to_file.string());
        json data = json::parse(f);

        if (!data.contains("frames")) return false;

        for (const auto& [name, etc] : data["frames"].items()) {
            SDL_FRect rect;

            if (!etc.contains("x")) return false;
            if (!etc.contains("y")) return false;
            if (!etc.contains("w")) return false;
            if (!etc.contains("h")) return false;

            rect.x = etc["x"];
            rect.y = etc["y"];
            rect.w = etc["w"];
            rect.h = etc["h"];

            m_sprites[name] = {rect, texture_index};
        }

        return true;
    }
}

