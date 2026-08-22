cmake_minimum_required(VERSION 4.0)
project(n_body_problem)

# Oni doporučují minimálně 17, což už máme.
set(CMAKE_CXX_STANDARD 17)

include_directories(.)

include(FetchContent)
FetchContent_Declare(
        webview
        GIT_REPOSITORY https://github.com/webview/webview
        GIT_TAG 0.12.0
)
FetchContent_MakeAvailable(webview)

# Tady přidáme to WIN32, jak to mají oni. Zabrání to navíc tomu,
# aby se na pozadí otevíralo černé terminálové okno.
add_executable(n_body_problem WIN32
        Body.cpp
        Body.h
        main.cpp
        Vector2D.h
        PhysicsEngine.cpp
        PhysicsEngine.h)

# 1. Zahoď ten řádek s target_include_directories
# target_include_directories(n_body_problem PRIVATE ${webview_SOURCE_DIR})

# 2. ZMĚNA JMENOVKY ZDE:
target_link_libraries(n_body_problem PRIVATE webview::core)