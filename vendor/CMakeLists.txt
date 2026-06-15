set(SDL_TEST OFF)
add_subdirectory(SDL)

set(SDLMIXER_FLAC OFF)
set(SDLMIXER_AIFF OFF)
set(SDLMIXER_VOC OFF)
set(SDLMIXER_AU OFF)
set(SDLMIXER_GME OFF)
set(SDLMIXER_MOD OFF)
set(SDLMIXER_MP3 OFF)
set(SDLMIXER_MIDI OFF)
set(SDLMIXER_OPUS OFF)

set(SDLMIXER_TESTS OFF)
set(SDLMIXER_EXAMPLES OFF)

add_subdirectory(SDL_mixer)

add_subdirectory(json)

add_library(vendor INTERFACE)
target_link_libraries(vendor INTERFACE SDL3::SDL3 SDL3_mixer::SDL3_mixer nlohmann_json::nlohmann_json)

target_include_directories(vendor INTERFACE qoi)