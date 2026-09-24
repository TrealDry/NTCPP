#ifndef NUCLEAR_THRONE_CPP_BANDIT_HPP
#define NUCLEAR_THRONE_CPP_BANDIT_HPP

#include "../../enemy.hpp"

namespace ntcpp {
    enum class en_bandit_state {
        WAIT = 0, MOVE_TO_PLAYER, MOVE_FROM_PLAYER, SHOOT, JUST_MOVE
    };

    struct s_bandit {
        en_bandit_state m_state = en_bandit_state::WAIT;
        bool m_on_enter = false;

        unsigned char m_timer = 0.f;
        unsigned char m_timer_limit = 20.f;
    };

    void init_bandit(enemy& en);
    void update_bandit(enemy& en, s_bandit& fields);
}

#endif
