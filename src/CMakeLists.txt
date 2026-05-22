include_directories(${CMAKE_SOURCE_DIR}/src)
add_subdirectory(system_monitor)

add_library(cpu_collector_lib STATIC
    collectors/cpu_collector.hpp
    collectors/cpu_collector.cpp
)

add_library(memory_collector_lib STATIC
    collectors/memory_collector.hpp
    collectors/memory_collector.cpp
)

add_library(process_collector_lib STATIC
    collectors/process_collector.hpp
    collectors/process_collector.cpp
)


add_library(process_info_lib STATIC
    process_info/process_info.hpp
    process_info/process_info.cpp
)

add_library(serializer STATIC
    serializer/serializer.hpp    
    serializer/serializer.cpp
)
target_link_libraries(serializer
    nlohmann_json
)


add_executable(webtop
    main.cpp
)
target_link_libraries(webtop PRIVATE 
    webui
    process_info_lib
    system_monitor_lib
    cpu_collector_lib
    memory_collector_lib
    process_collector_lib
)