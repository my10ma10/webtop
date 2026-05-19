cmake_minimum_required(VERSION 3.18)
project(webtop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(WEBUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/webui)

add_subdirectory(${WEBUI_DIR})

add_subdirectory(src)