add_executable(${PROJECT_NAME}
        core/window.cpp
        core/window.hpp
        core/obj_interface.cpp
        core/obj_interface.hpp
        objects/player/player.cpp
        objects/player/player.hpp
        math/vec2.hpp
        core/obj_manager.cpp
        core/obj_manager.hpp)

target_sources(${PROJECT_NAME} PRIVATE main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE vendor)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)