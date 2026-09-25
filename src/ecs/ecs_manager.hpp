#pragma once

#include <memory>

#include "system/template/ecs_system.hpp"

class ecs_manager {
    public:
        static ecs_manager& get_instance() {
            static ecs_manager instance;
            return instance;
        }

        ecs_manager(ecs_manager const&)  = delete;
        void operator=(ecs_manager const&) = delete;

        void init();

        void update();
        void draw();

    private:
        entt::registry m_registry{};

        std::vector<std::unique_ptr<ecs_system>> m_update_systems{};
        std::vector<std::unique_ptr<ecs_system>> m_draw_systems{};

    private:
        ecs_manager() {}
};
