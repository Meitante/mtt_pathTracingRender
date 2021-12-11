cmake_minimum_required (VERSION 3.19)
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_STANDARD 17)
set(PROJECT_SOURCE_DIR "-Wall -g")

project(mtt_pathTracingRender)


include_directories(./include)
# where you should include your eigen include path
include_directories(/opt/homebrew/include)


# Start main compile
add_executable(pathTracing 
    src/main.cpp
    src/Renderer.cpp
    src/Scene.cpp
)
target_link_libraries(pathTracing ${OpenCV_LIBRARIES})



# for unit test
include_directories("${PROJECT_SOURCE_DIR}/submodules/googletest/googletest/include")
link_directories("${PROJECT_SOURCE_DIR}/submodules/googletest/build/lib")



add_executable(Renderer_TestSuite 
    src/test/Renderer_TestSuite.cpp
    src/Renderer.cpp
    src/Scene.cpp
)
target_link_libraries(Renderer_TestSuite gtest gtest_main ${OpenCV_LIBRARIES})

add_executable(Scene_TestSuite 
    src/test/Scene_TestSuite.cpp
    src/Scene.cpp
)
target_link_libraries(Scene_TestSuite gtest gtest_main ${OpenCV_LIBRARIES})