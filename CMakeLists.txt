cmake_minimum_required(VERSION 3.18)
project(webtop)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_BUILD_TYPE "DEBUG")


include(FetchContent)
FetchContent_Declare(
    webui
    GIT_REPOSITORY https://github.com/webui-dev/webui.git
    GIT_TAG main 
)
FetchContent_MakeAvailable(webui)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG develop 
)
FetchContent_MakeAvailable(nlohmann_json)


add_subdirectory(src)