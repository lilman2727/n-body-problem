cmake_minimum_required(VERSION 4.0)
project(n_body_problem)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

include(FetchContent)
FetchContent_Declare(
        webview
        GIT_REPOSITORY https://github.com/webview/webview
        GIT_TAG 0.12.0
)
FetchContent_MakeAvailable(webview)

FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)

add_executable(n_body_problem WIN32
        Body.cpp
        Body.h
        main.cpp
        Vector2D.h
        PhysicsEngine.cpp
        PhysicsEngine.h)

target_link_libraries(n_body_problem PRIVATE webview::core nlohmann_json::nlohmann_json)