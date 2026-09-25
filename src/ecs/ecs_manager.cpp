#include "ecs_manager.hpp"

#include "system/movement.hpp"
#include "system/sprite_render.hpp"
#include "system/move_and_collide_wall.hpp"

void ecs_manager::init() {
    m_update_systems.push_back(std::make_unique<movement_system>());
    m_update_systems.push_back(std::make_unique<move_and_collide_wall_system>());

    m_draw_systems.push_back(std::make_unique<sprite_render_system>());
}

void ecs_manager::update() {
    for (auto& sys : m_update_systems)
        sys.get()->update(m_registry);
}

void ecs_manager::draw() {
    for (auto& sys : m_draw_systems)
        sys.get()->update(m_registry);
}
