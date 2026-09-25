#pragma once

struct WantMove {
    float normalized_x;
    float normalized_y;
};

struct Movement {
    float vel_x;
    float vel_y;
    float speed;
    float max_speed;
    float friction;

    bool on_move;
};

struct MoveAndCollideWall {};
