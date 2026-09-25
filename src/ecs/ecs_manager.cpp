#include "ecs_manager.hpp"

#include "system/health_dead.hpp"
#include "system/movement.hpp"
#include "system/sprite_render.hpp"
#include "system/move_and_collide_wall.hpp"
#include "system/projectile.hpp"

void ecs_manager::init() {
    // update
    m_update_systems.push_back(std::make_unique<health_dead_system>());
    m_update_systems.push_back(std::make_unique<projectile_system>());

    m_update_systems.push_back(std::make_unique<movement_system>());
    m_update_systems.push_back(std::make_unique<move_and_collide_wall_system>());

    // draw
    m_draw_systems.push_back(std::make_unique<sprite_render_system>());

    // auto test_entity = m_registry.create();
    // m_registry.emplace<Position>(test_entity, 0.f, 0.f);
    // m_registry.emplace<Sprite>(test_entity, "sprBigPortrait_0", SDL_FPoint{0.f, 0.f}, 0);
}

void ecs_manager::update() {
    for (auto& sys : m_update_systems)
        sys.get()->update(m_registry);
}

void ecs_manager::draw() {
    for (auto& sys : m_draw_systems)
        sys.get()->update(m_registry);
}
