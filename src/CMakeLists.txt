add_executable(${PROJECT_NAME}
        core/window.cpp
        core/window.hpp
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
        core/manager/input_manager.hpp
        core/sprite.hpp
        objects/terrain/terrain.cpp
        objects/terrain/terrain.hpp
        objects/terrain/wall/wall.cpp
        objects/terrain/wall/wall.hpp
        math/circle.hpp
        core/manager/collision_manager.cpp
        core/manager/collision_manager.hpp
        math/frect.hpp
        core/manager/debug_manager.cpp
        core/manager/debug_manager.hpp
        objects/terrain/floor/floor.cpp
        objects/terrain/floor/floor.hpp
        objects/terrain/floor_maker/floor_maker.cpp
        objects/terrain/floor_maker/floor_maker.hpp
        core/camera.hpp
        core/camera.cpp
)

target_sources(${PROJECT_NAME} PRIVATE main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE vendor)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)