cmake_minimum_required(VERSION 3.26.4x)
project(zappy_gui)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(OpenGlLinkers -lglut -lGLU -lGL) # setting all the Glut libraries as one variable.

include_directories(src)

add_executable(zappy_gui
        Main.cpp
)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
target_link_libraries(zappy_gui ${OpenGlLinkers}) # linking opengl libraries to the project
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
