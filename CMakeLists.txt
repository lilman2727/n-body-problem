cmake_minimum_required(VERSION 4.0)
project(n_body_problem)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.1.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(n_body_problem
        Body.cpp
        Body.h
        main.cpp
        Vector2D.h
        PhysicsEngine.cpp
        PhysicsEngine.h)

target_link_libraries(n_body_problem PRIVATE SFML::Graphics)
