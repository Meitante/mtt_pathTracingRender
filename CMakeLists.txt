cmake_minimum_required (VERSION 3.19)
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")

project(mtt_pathTracingRender)


include_directories(./include)
# where you should include your eigen include path
include_directories(/opt/homebrew/include)

set(srcList
    src/Renderer.cpp
    src/Scene.cpp
    src/Ray.cpp
    src/BoundingBox.cpp
    src/Intersection.cpp
    src/Sphere.cpp
    src/Material.cpp
    src/Triangle.cpp
    src/BVH.cpp
)

# SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)
add_library(mylib OBJECT ${srcList})
set(librariesList
    mylib
    # ${OpenCV_LIBRARIES}
)


# Start main compile
add_executable(pathTracing
    src/main.cpp
)
target_link_libraries(pathTracing ${librariesList})



# for unit test
include_directories("${PROJECT_SOURCE_DIR}/submodules/googletest/googletest/include")
link_directories("${PROJECT_SOURCE_DIR}/submodules/googletest/build/lib")
set(UTlibrariesList gtest gtest_main ${librariesList})

add_executable(Renderer_TestSuite
    src/test/Renderer_TestSuite.cpp
)
target_link_libraries(Renderer_TestSuite ${UTlibrariesList})

add_executable(Scene_TestSuite
    src/test/Scene_TestSuite.cpp
)
target_link_libraries(Scene_TestSuite ${UTlibrariesList})

add_executable(Ray_TestSuite
    src/test/Ray_TestSuite.cpp
)
target_link_libraries(Ray_TestSuite ${UTlibrariesList})

add_executable(BoundingBox_TestSuite 
    src/test/BoundingBox_TestSuite.cpp
)
target_link_libraries(BoundingBox_TestSuite ${UTlibrariesList})

add_executable(Intersection_TestSuite
    src/test/Intersection_TestSuite.cpp
)
target_link_libraries(Intersection_TestSuite ${UTlibrariesList})

add_executable(Object_TestSuite
    src/test/Object_TestSuite.cpp
)
target_link_libraries(Object_TestSuite ${UTlibrariesList})