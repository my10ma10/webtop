add_library(monitor_engine_lib STATIC
    monitor_engine.hpp
    monitor_engine.cpp
)
target_link_libraries(monitor_engine_lib PUBLIC
    process_info_lib
)