#ifndef NUCLEAR_THRONE_CPP_TERRAIN_HPP
#define NUCLEAR_THRONE_CPP_TERRAIN_HPP

#include <vector>

#include "wall/wall.hpp"
#include "floor/floor.hpp"
#include "floor_maker/floor_maker.hpp"
#include "wall_trans/wall_trans.hpp"

namespace ntcpp {
    enum class en_gen_status {CREATE_FLOORS, DONE};

    class terrain : obj_interface {
    public:
        void init();

        void update() override;
        void draw(SDL_Renderer* renderer) override;

        std::vector<wall>& get_walls() { return m_walls; }
        std::vector<floor>& get_floors() { return m_floors; }
        std::vector<floor_maker>& get_floor_makers() { return m_floor_makers; }
        std::vector<wall_trans>& get_wall_trans() { return m_wall_trans; }

        void create_wall(vec2 pos);
        void create_floor(vec2 pos);
        void create_floor_maker(vec2 pos);
        void create_wall_trans(vec2 pos);

    private:
        std::vector<wall> m_walls;
        std::vector<floor> m_floors;
        std::vector<floor_maker> m_floor_makers;
        std::vector<wall_trans> m_wall_trans;

        sprite m_wall_out_sprite;
        sprite m_wall_top_sprite;

        en_gen_status m_gen_status = en_gen_status::CREATE_FLOORS;
    };
}

#endif
