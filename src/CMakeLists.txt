include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(cpu_collector_lib STATIC
    collectors/cpu_collector.hpp
    collectors/cpu_collector.cpp
)

add_library(memory_collector_lib STATIC
    collectors/memory_collector.hpp
    collectors/memory_collector.cpp
)


add_library(process_info_lib STATIC
    process_info/process_info.hpp
    process_info/process_info.cpp
)
add_library(process_collector_lib STATIC
    collectors/process_collector.hpp
    collectors/process_collector.cpp
)
target_link_libraries(process_collector_lib
    process_info_lib
)


add_subdirectory(system_monitor)

add_library(serializer_lib STATIC
    serializer/serializer.hpp    
    serializer/serializer.cpp
)
target_link_libraries(serializer_lib
    nlohmann_json
)


add_library(frontend_bridge_lib STATIC
    frontend_bridge/frontend_bridge.hpp    
    frontend_bridge/frontend_bridge.cpp
)
target_link_libraries(frontend_bridge_lib PUBLIC
    webui
)

add_library(stat_updater_lib STATIC
    stat_updater/stat_updater.hpp    
    stat_updater/stat_updater.cpp
)
target_link_libraries(stat_updater_lib
    system_monitor_lib
    frontend_bridge_lib
    serializer_lib
)


add_executable(webtop
    main.cpp
)
target_link_libraries(webtop PRIVATE 
    stat_updater_lib
    frontend_bridge_lib
)