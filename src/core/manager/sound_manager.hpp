#ifndef NUCLEAR_THRONE_CPP_SOUND_MANAGER_HPP
#define NUCLEAR_THRONE_CPP_SOUND_MANAGER_HPP

#include <optional>
#include <string>
#include <unordered_map>
#include <SDL3_mixer/SDL_mixer.h>

#include "../status.hpp"

namespace ntcpp {
    class sound_manager {
    public:
        static sound_manager& get_instance() {
            static sound_manager instance;
            return instance;
        }

        sound_manager(sound_manager const&)  = delete;
        void operator=(sound_manager const&) = delete;

        std::optional<status> init();

        std::optional<MIX_Audio*> get_audio(const std::string& name);
        void play_audio(const std::string& name);

    private:
        MIX_Mixer* m_mixer;
        std::unordered_map<std::string, MIX_Audio*> m_sounds;

    private:
        sound_manager() {}
    };
}

#endif
