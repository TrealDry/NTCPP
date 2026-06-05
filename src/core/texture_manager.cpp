#include "texture_manager.hpp"
#include "nlohmann/json.hpp"

#include <fstream>

namespace fs = std::filesystem;
using json = nlohmann::json;

namespace ntcpp {
    en_tex_mng_status texture_manager::init(SDL_Renderer* renderer) {
        fs::path dir = "assets/textures";
        std::unordered_map<unsigned char, std::pair<fs::path, fs::path>> texture_pairs;

        if (!fs::exists(dir) || !fs::is_directory(dir)) return en_tex_mng_status::FOLDER_NOT_FOUND;

        for (const auto& entry : fs::directory_iterator(dir)) {
            auto filename = entry.path().stem().string();
            auto ext = entry.path().extension().string();

            if (filename == ".gitkeep") continue;

            unsigned char index = std::atoi(filename.substr(filename.find('-') + 1).c_str());

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
            const auto& [json, png] = pair;

            if (!json_parse(json, index)) return en_tex_mng_status::INVALID_JSON;

            auto* surface = SDL_LoadPNG(png.u8string().c_str());
            m_textures[index] = SDL_CreateTextureFromSurface(renderer, surface);

            SDL_SetTextureScaleMode(m_textures[index], SDL_SCALEMODE_NEAREST);
        }

        return en_tex_mng_status::OK;
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

            if (!etc.contains("frame")) return false;

            auto& frame = etc["frame"];
            if (!frame.contains("x")) return false;
            if (!frame.contains("y")) return false;
            if (!frame.contains("w")) return false;
            if (!frame.contains("h")) return false;

            rect.x = frame["x"];
            rect.y = frame["y"];
            rect.w = frame["w"];
            rect.h = frame["h"];

            m_sprites[name] = {rect, texture_index};
        }

        return true;
    }
}

