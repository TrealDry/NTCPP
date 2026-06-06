set(SDL_TEST OFF)
add_subdirectory(SDL)
add_subdirectory(json)

add_library(vendor INTERFACE)
target_link_libraries(vendor INTERFACE SDL3::SDL3 nlohmann_json::nlohmann_json)

target_include_directories(vendor INTERFACE qoi)