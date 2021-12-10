cmake_minimum_required (VERSION 3.19)
SET(CMAKE_C_COMPILER "/usr/bin/clang")
SET(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_STANDARD 17)
add_definitions("-Wall -g")


project(mtt_pathTracingRender)


include_directories(./include)

add_executable(pathTracing 
    src/main.cpp
    src/Renderer.cpp
)


# for unit test
include_directories("./submodules/googletest/googletest/include")
link_directories("./submodules/googletest/build/lib")

add_executable(Renderer_TestSuite 
    src/test/Renderer_TestSuite.cpp
    src/Renderer.cpp
)
target_link_libraries(Renderer_TestSuite gtest gtest_main)