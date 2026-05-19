cmake_minimum_required(VERSION 3.18)
project(webtop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(WEBUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/webui)

include(FetchContent)
FetchContent_Declare(
    webui
    GIT_REPOSITORY https://github.com/webui-dev/webui.git
    GIT_TAG main 
)
FetchContent_MakeAvailable(webui)

add_subdirectory(src)