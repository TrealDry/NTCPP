#ifndef NUCLEAR_THRONE_CPP_DEBUG_MANAGER_HPP
#define NUCLEAR_THRONE_CPP_DEBUG_MANAGER_HPP

namespace ntcpp {
    class debug_manager {
    public:
        bool m_is_active = false;

    public:
        static debug_manager& get_instance() {
            static debug_manager instance;
            return instance;
        }

        debug_manager(debug_manager const&)  = delete;
        void operator=(debug_manager const&) = delete;

        void update();
    private:
        debug_manager() {}
    };
}

#endif
