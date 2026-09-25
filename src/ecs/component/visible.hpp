#pragma once

#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_surface.h"

#include "../../core/manager/texture_manager.hpp"

struct Sprite {
    SDL_FRect texture_rect;
    SDL_FPoint offset;
    unsigned char texture_id;
    SDL_FlipMode flip;
    SDL_FPoint center;
    float rotation_deg;
    bool ignore_camera;
    char z_layer;

    Sprite(
        const std::string& name,
        SDL_FPoint offset,
        char z_layer,
        SDL_FlipMode flip = SDL_FLIP_NONE,
        float rotation_deg = 0.f,
        SDL_FPoint center = {0.f, 0.f},
        bool ignore_camera = false
    ) :
        texture_rect(), offset(offset), texture_id(0), flip(flip), center(center),
        rotation_deg(rotation_deg), ignore_camera(ignore_camera), z_layer(z_layer)
    {
        if (auto spr_data = ntcpp::texture_manager::get_instance().get_sprite(name)) {
            texture_rect = spr_data->first;
            texture_id = spr_data->second;
        }
    }
};
