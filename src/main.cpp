#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>

#include <SDL3_mixer/SDL_mixer.h>

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"

#include "core/game.hpp"

constexpr int c_window_width  = 320;
constexpr int c_window_height = 240;

constexpr uint64_t c_target_ns = 1'000'000'000ULL / 30;

constexpr char c_title[] = "Can you reach nuclear throne?";
constexpr char c_version[] = "0.1.0";

uint64_t last_time;
int frame_count = 0;

SDL_Window* window;
SDL_Renderer* renderer;

SDL_Texture* render_target = nullptr;

auto& win = ntcpp::game::get_instance();

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    SDL_SetAppMetadata(
        c_title, c_version, "com.trealdry.ntcpp"
    );

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(
        c_title, c_window_width, c_window_height,
        SDL_WINDOW_RESIZABLE, &window, &renderer)
    ) {
        SDL_Log("couldn't create window/renderer: %s", SDL_GetError());
    }

    // imgui init
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    if (!MIX_Init()) {
        SDL_Log("mixer error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    render_target = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA32,
        SDL_TEXTUREACCESS_TARGET,
        c_window_width, c_window_height
    );
    SDL_SetTextureScaleMode(render_target, SDL_SCALEMODE_NEAREST);

    auto win_init_status = win.init(window, renderer);

    if (win_init_status.has_value()) {
        SDL_Log("%s", win_init_status.value().msg.c_str());
        return SDL_APP_FAILURE;
    }

    SDL_HideCursor();
    SDL_srand(0);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    uint64_t start_time = SDL_GetTicksNS();

    // start render
    SDL_SetRenderTarget(renderer, render_target);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // game processing
    win.update();
    win.draw();

    // resize texture and blit on screen
    SDL_SetRenderTarget(renderer, nullptr);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    int win_w, win_h;
    SDL_GetWindowSize(window, &win_w, &win_h);

    float scale = std::min(
        (float)win_w / c_window_width,
        (float)win_h / c_window_height
    );
    float dst_w = c_window_width  * scale;
    float dst_h = c_window_height * scale;
    SDL_FRect dst = {
        (win_w - dst_w) / 2.f,
        (win_h - dst_h) / 2.f,
        dst_w, dst_h
    };

    SDL_RenderTexture(renderer, render_target, nullptr, &dst);

    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

    SDL_RenderPresent(renderer);

    // fps counter
    frame_count++;
    if (auto current_time = SDL_GetTicks(); current_time - last_time >= 1000) {
        win.current_fps = frame_count;
        frame_count = 0;
        last_time = current_time;
    }

    // fps limit
    uint64_t elapsed = SDL_GetTicksNS() - start_time;

    if (elapsed < c_target_ns) {
        SDL_DelayNS(c_target_ns - elapsed);
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    ImGui_ImplSDL3_ProcessEvent(event);

    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    if (event->type == SDL_EVENT_MOUSE_MOTION) {
        int win_w, win_h;
        SDL_GetWindowSize(window, &win_w, &win_h);

        float scale = std::min(
            (float)win_w / (float)c_window_width,
            (float)win_h / (float)c_window_height
        );
        float offset_x = ((float)win_w - (float)c_window_width  * scale) / 2.f;
        float offset_y = ((float)win_h - (float)c_window_height * scale) / 2.f;

        win.m_mouse_pos.x = (event->motion.x - offset_x) / scale;
        win.m_mouse_pos.y = (event->motion.y - offset_y) / scale;
    }

    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        switch (event->button.button) {
        case SDL_BUTTON_LEFT:
            win.m_mouse_buttons[ntcpp::en_mouse_buttons::LEFT] = true;
            break;
        case SDL_BUTTON_RIGHT:
            win.m_mouse_buttons[ntcpp::en_mouse_buttons::RIGHT] = true;
            break;
        case SDL_BUTTON_MIDDLE:
            win.m_mouse_buttons[ntcpp::en_mouse_buttons::MIDDLE] = true;
            break;
        }
    }

    if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
        switch (event->button.button) {
        case SDL_BUTTON_LEFT:
            win.m_mouse_buttons[ntcpp::en_mouse_buttons::LEFT] = false;
            break;
        case SDL_BUTTON_RIGHT:
            win.m_mouse_buttons[ntcpp::en_mouse_buttons::RIGHT] = false;
            break;
        case SDL_BUTTON_MIDDLE:
            win.m_mouse_buttons[ntcpp::en_mouse_buttons::MIDDLE] = false;
            break;
        }
    }

    if (event->type == SDL_EVENT_MOUSE_WHEEL) {
        if (event->wheel.y > 0.0f) {
            win.m_mouse_buttons[ntcpp::en_mouse_buttons::WHEEL_UP] = true;
            win.m_mouse_buttons[ntcpp::en_mouse_buttons::WHEEL_DOWN] = false;
        }
        else if (event->wheel.y < 0.0f) {
            win.m_mouse_buttons[ntcpp::en_mouse_buttons::WHEEL_UP] = false;
            win.m_mouse_buttons[ntcpp::en_mouse_buttons::WHEEL_DOWN] = true;
        }
    } else {
        win.m_mouse_buttons[ntcpp::en_mouse_buttons::WHEEL_UP] = false;
        win.m_mouse_buttons[ntcpp::en_mouse_buttons::WHEEL_UP] = false;
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}
