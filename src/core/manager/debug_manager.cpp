#include "debug_manager.hpp"

#include "obj_manager.hpp"
#include "input_manager.hpp"

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

        ImGui::Render();
    }
}
