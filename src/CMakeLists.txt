add_subdirectory(moditor_engine)

add_executable(webtop
    main.cpp
)
target_link_libraries(webtop PRIVATE 
    webui
    process_info_lib
    monitor_engine_lib
)