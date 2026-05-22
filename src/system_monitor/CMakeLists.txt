add_library(system_monitor_lib STATIC
    system_monitor.hpp
    system_monitor.cpp
)
target_link_libraries(system_monitor_lib PUBLIC
    process_info_lib
)