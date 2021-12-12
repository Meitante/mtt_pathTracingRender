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
    src/Ray.cpp
    src/BoundingBox.cpp
    src/Intersection.cpp
    src/Sphere.cpp
)
target_link_libraries(pathTracing ${OpenCV_LIBRARIES})



# for unit test
include_directories("${PROJECT_SOURCE_DIR}/submodules/googletest/googletest/include")
link_directories("${PROJECT_SOURCE_DIR}/submodules/googletest/build/lib")
set(librariesList gtest gtest_main ${OpenCV_LIBRARIES})

add_executable(Renderer_TestSuite 
    src/test/Renderer_TestSuite.cpp
    src/Renderer.cpp
    src/Scene.cpp
)
target_link_libraries(Renderer_TestSuite ${librariesList})

add_executable(Scene_TestSuite
    src/test/Scene_TestSuite.cpp
    src/Scene.cpp
)
target_link_libraries(Scene_TestSuite ${librariesList})

add_executable(Ray_TestSuite 
    src/test/Ray_TestSuite.cpp
    src/Ray.cpp
)

target_link_libraries(Ray_TestSuite ${librariesList})

add_executable(BoundingBox_TestSuite 
    src/test/BoundingBox_TestSuite.cpp
    src/Ray.cpp
    src/BoundingBox.cpp
    src/Sphere.cpp
)

target_link_libraries(BoundingBox_TestSuite ${librariesList})

add_executable(Intersection_TestSuite 
    src/test/Intersection_TestSuite.cpp
    src/Intersection.cpp
)

target_link_libraries(Intersection_TestSuite ${librariesList})