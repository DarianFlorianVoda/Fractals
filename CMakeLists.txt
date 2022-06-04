cmake_minimum_required(VERSION 3.21)
project(Fractals)

set(CMAKE_CXX_STANDARD 14)

add_executable(Barnsley_fern 2DBarnsley_fern.cpp)
target_link_libraries(Barnsley_fern -lopengl32 -lglu32 -lfreeglut)

add_executable(3D_Sierpinski "3D Sierpinski.cpp")
target_link_libraries(3D_Sierpinski -lopengl32 -lglu32 -lfreeglut)

add_executable(3D_new 3D_new.cpp)
target_link_libraries(3D_new -lopengl32 -lglu32 -lfreeglut)

add_executable(3D_second 3D_second.cpp)
target_link_libraries(3D_second -lopengl32 -lglu32 -lfreeglut)