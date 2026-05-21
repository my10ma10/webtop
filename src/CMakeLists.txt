include_directories(${CMAKE_SOURCE_DIR}/src)
add_subdirectory(moditor_engine)

add_library(cpu_collector_lib STATIC
    collectors/cpu_collector.hpp
    collectors/cpu_collector.cpp
)

add_library(memory_collector_lib STATIC
    collectors/memory_collector.hpp
    collectors/memory_collector.cpp
)


add_executable(webtop
    main.cpp
)
target_link_libraries(webtop PRIVATE 
    webui
    process_info_lib
    monitor_engine_lib
    cpu_collector_lib
    memory_collector_lib
)