#include "sound_manager.hpp"

#include <filesystem>

namespace fs = std::filesystem;

namespace ntcpp {
    std::optional<status> sound_manager::init() {
        m_mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);

        if (!m_mixer) {
            return status{
                en_status::NOT_OK,
                "create mixer error: " + std::string(SDL_GetError())
            };
        }

        fs::path dir = fs::path("assets") / "sounds";

        for (const auto& entry : fs::directory_iterator(dir)) {
            auto filename = entry.path().stem().string();
            auto ext = entry.path().extension().string();

            if (filename == ".gitkeep" || ext == ".ogg") continue;

            fs::path full_path = dir / (filename + ext);
            MIX_Audio* sound = MIX_LoadAudio(m_mixer, full_path.u8string().c_str(), true);

            if (!sound) {
                return status{
                    en_status::NOT_OK,
                    "load sound failed: " + std::string(SDL_GetError())
                };
            }

            m_sounds.insert({filename, sound});
        }

        return std::nullopt;
    }

    std::optional<MIX_Audio*> sound_manager::get_audio(const std::string& name) {
        if (m_sounds.find(name) == m_sounds.end()) return std::nullopt;

        return m_sounds[name];
    }

    void sound_manager::play_audio(const std::string& name) {
        if (auto sound = get_audio(name)) {
            MIX_PlayAudio(m_mixer, sound.value());
        }
    }
}
