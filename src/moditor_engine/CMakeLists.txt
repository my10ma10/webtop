add_library(process_info_lib STATIC
    process_info/process_info.hpp
    process_info/process_info.cpp
)

add_library(monitor_engine_lib STATIC
    monitor_engine.hpp
    monitor_engine.cpp
)
target_link_libraries(monitor_engine_lib PUBLIC
    process_info_lib
)