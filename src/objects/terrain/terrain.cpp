#include "terrain.hpp"

#include "../../core/manager/collision_manager.hpp"

namespace ntcpp {
    void terrain::init() {
        create_floor_maker({0.f, 0.f});

        // TODO я не обрабатываю ошибки спрайтов
        m_wall_out_sprite.init("sprWall1Out_0", {4.f, 12.f});
    }

    void terrain::create_wall(vec2 pos) {
        if (collision_manager::has_wall(pos)) return;

        m_walls.emplace_back();
        m_walls.back().init(pos);
    }

    void terrain::create_floor(vec2 pos) {
        if (collision_manager::has_floor(pos)) return;

        m_floors.emplace_back();
        m_floors.back().init(pos);
    }

    void terrain::create_floor_maker(vec2 pos) {
        m_floor_makers.emplace_back();
        m_floor_makers.back().init(110, pos);  // TODO сменить goal позже
    }

    void terrain::create_wall_trans(vec2 pos) {
        if (collision_manager::has_wall_trans(pos)) return;

        m_wall_trans.emplace_back();
        m_wall_trans.back().init(pos);
    }

    void terrain::update() {
        std::vector<vec2> new_floor_makers;

        // update floor maker
        for (auto& _floor_maker : m_floor_makers) {
            _floor_maker.update();

            if (_floor_maker.create_duplicate) {
                new_floor_makers.emplace_back(_floor_maker.get_pos());
                _floor_maker.create_duplicate = false;
            }
        }

        // delete
        m_floor_makers.erase(
            std::remove_if(m_floor_makers.begin(), m_floor_makers.end(), [](auto& _floor_maker) {
                return _floor_maker.delete_me;
            }), m_floor_makers.end()
        );

        // add new fm
        std::for_each(new_floor_makers.begin(), new_floor_makers.end(), [this](vec2& new_pos) {
            create_floor_maker(new_pos);
        });

        if (m_floor_makers.empty() && m_gen_status == en_gen_status::CREATE_FLOORS) {
            std::for_each(m_floors.begin(), m_floors.end(), [](floor& _floor) {
                _floor.create_walls();
            });

            std::for_each(m_floors.begin(), m_floors.end(), [](floor& _floor) {
                _floor.create_trans();
            });

            m_gen_status = en_gen_status::DONE;
        }
    }

    void terrain::draw(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 175, 143, 106, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        for (auto& _floor : m_floors) {
            _floor.draw(renderer);
        }

        for (auto& _wall : m_walls) _wall.draw(renderer);
    }

    void terrain::draw_top_layer(SDL_Renderer* renderer) {
        for (auto& _wall : m_walls) m_wall_out_sprite.draw(renderer, _wall.get_pos());
        for (auto& _wall : m_walls) _wall.draw_top(renderer);

        for (auto& _wall_trans : m_wall_trans) {
            _wall_trans.draw(renderer);
        }
    }
}
