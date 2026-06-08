add_executable(${PROJECT_NAME}
        core/window.cpp
        core/window.hpp
        core/obj_interface.cpp
        core/obj_interface.hpp
        objects/player/player.cpp
        objects/player/player.hpp
        math/vec2.hpp
        core/manager/obj_manager.cpp
        core/manager/obj_manager.hpp
        core/manager/texture_manager.cpp
        core/manager/texture_manager.hpp
        core/status.hpp
        core/animation.cpp
        core/animation.hpp
        core/manager/animation_manager.cpp
        core/manager/animation_manager.hpp
        objects/hud/cursor/cursor.cpp
        objects/hud/cursor/cursor.hpp
        core/manager/input_manager.cpp
        core/manager/input_manager.hpp)

target_sources(${PROJECT_NAME} PRIVATE main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE vendor)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)