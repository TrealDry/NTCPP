#pragma once

#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_surface.h"

#include "../../core/manager/texture_manager.hpp"

struct Sprite {
    SDL_FRect texture_rect;
    SDL_FPoint origin;
    SDL_FlipMode flip;
    float rotation_deg;
    unsigned char texture_id;
    bool ignore_camera;
    char z_layer;
    bool hide;

    Sprite(
        const std::string& name,
        SDL_FPoint origin = {0.f, 0.f},
        char z_layer = 0,
        SDL_FlipMode flip = SDL_FLIP_NONE,
        float rotation_deg = 0.f,
        bool ignore_camera = false,
        bool hide = false
    ) :
        texture_rect(), origin(origin), flip(flip), rotation_deg(rotation_deg), texture_id(0),
        ignore_camera(ignore_camera), z_layer(z_layer), hide(hide)
    {
        if (auto spr_data = ntcpp::texture_manager::get_instance().get_sprite(name)) {
            texture_rect = spr_data->first;
            texture_id = spr_data->second;
        }
    }

    Sprite(
        char z_layer = 0,
        float rotation_deg = 0.f,
        bool ignore_camera = false,
        bool hide = false
    ) :
        texture_rect(), origin({0.f, 0.f}), flip(SDL_FLIP_NONE), rotation_deg(rotation_deg), texture_id(0),
        ignore_camera(ignore_camera), z_layer(z_layer), hide(hide)
    {
        ;
    }
};

struct Animation {
    uint32_t clip_id;
    uint32_t current_frame;
    float timer;
    bool stop;

    Animation(
        uint32_t clip_id, uint32_t current_frame = 0
    ) :
        clip_id(clip_id), current_frame(current_frame),
        timer(0.f), stop(false)
    {
        ;
    }
};
