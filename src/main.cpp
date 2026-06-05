#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "core/window.hpp"

constexpr int c_window_width  = 320;
constexpr int c_window_height = 240;

constexpr uint64_t c_target_ns = 1'000'000'000ULL / 30;

constexpr char c_title[] = "Can you reach nuclear throne?";
constexpr char c_version[] = "0.1.0";

SDL_Window* window;
SDL_Renderer* renderer;

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

    SDL_SetRenderLogicalPresentation(
        renderer, c_window_width, c_window_height,
        SDL_LOGICAL_PRESENTATION_LETTERBOX
    );

    auto win_init_status = win.init(window, renderer);
    if (win_init_status != ntcpp::en_win_status::OK) {
        switch (win_init_status) {
        case ntcpp::en_win_status::TEX_MANAGER_INIT_FAILED:
            SDL_Log("texture manager init failed!");
            break;
        default:
            SDL_Log("unknown error!");
            break;
        }

        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    uint64_t start_time = SDL_GetTicksNS();

    // clean renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // win processing
    win.update();
    win.draw();

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

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    ;
}
