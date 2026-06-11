#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>

#include "core/window.hpp"

constexpr int c_window_width  = 320;
constexpr int c_window_height = 240;

constexpr uint64_t c_target_ns = 1'000'000'000ULL / 30;

constexpr char c_title[] = "Can you reach nuclear throne?";
constexpr char c_version[] = "0.1.0";

SDL_Window* window;
SDL_Renderer* renderer;

SDL_Texture* render_target = nullptr;

auto& win = ntcpp::window::get_instance();

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

    render_target = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA32,
        SDL_TEXTUREACCESS_TARGET,
        c_window_width, c_window_height
    );
    SDL_SetTextureScaleMode(render_target, SDL_SCALEMODE_NEAREST);

    auto win_init_status = win.init(window, renderer);

    if (win_init_status.has_value()) {
        SDL_Log(win_init_status.value().msg.c_str());
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
    SDL_RenderPresent(renderer);

    // fps limit
    uint64_t elapsed = SDL_GetTicksNS() - start_time;

    if (elapsed < c_target_ns) {
        SDL_DelayNS(c_target_ns - elapsed);
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
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

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    ;
}
