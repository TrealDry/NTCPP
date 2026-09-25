#include "debug_manager.hpp"

#include "../game.hpp"

#include "obj_manager.hpp"
#include "input_manager.hpp"

#include "../../ecs/ecs_manager.hpp"
#include "../../ecs/component/entity.hpp"
#include "../../ecs/component/projectile.hpp"

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"

namespace ntcpp {
    void debug_manager::update() {
        if (input_manager::get_instance().get_key_status(en_keys::DEBUG) == 1)
            m_is_active = !m_is_active;

        imgui_handler();
    }

    void debug_manager::imgui_handler() {
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();

        ImGui::NewFrame();

        ImGui::Begin("Player");
        ImGui::Text("hspeed = %f", obj_manager::get_instance().m_player.get_velocity().x);
        ImGui::Text("vspeed = %f", obj_manager::get_instance().m_player.get_velocity().y);
        ImGui::End();

        ImGui::Begin("Projectiles");

        auto& reg = ecs_manager::get_instance().get_registry();

        unsigned long long proj_count = 0;
        unsigned long long proj_dead_count = 0;

        auto view = reg.view<Projectile, Health>();
        view.each([&](const Projectile& proj, const Health& health) {
            proj_count++;

            if (!health.is_alive) proj_dead_count++;
        });

        ImGui::Text("all = %llu", proj_count);
        ImGui::Text("dead = %llu", proj_dead_count);
        ImGui::End();

        ImGui::Begin("Other");
        ImGui::Text("fps = %d", game::get_instance().current_fps);
        ImGui::End();

        ImGui::Render();
    }
}
