#include "bandit.hpp"

namespace ntcpp {
    void init_bandit(enemy& en) {
        en.m_max_hp = 4;
        en.m_hp = 4;

        en.m_rad_drop = 2;
    }

    void update_bandit(enemy& en, s_bandit& fields) {
        switch (fields.m_state) {
            case en_bandit_state::WAIT:
                fields.m_timer += 1;

                if (fields.m_timer >= fields.m_timer_limit) {
                    ;
                }

                break;
        }
    }
}
