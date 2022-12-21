cmake_minimum_required(VERSION 3.5)

project(shape_primitives LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(FLTK_SKIP_FLUID True)
set(OpenGL_GL_PREFERENCE "GLVND")

find_package(FLTK REQUIRED)
find_package(OpenGL REQUIRED)


set(GRAPHLIB_DIR "../../../lib")

include_directories(
    ${GRAPHLIB_DIR}
    SYSTEM
    ${FLTK_INCLUDE_DIR}
)

add_executable(
    shape_primitives
    main.cpp
    ${GRAPHLIB_DIR}/Graph_lib/Graph.cpp
    ${GRAPHLIB_DIR}/Graph_lib/GUI.cpp
    ${GRAPHLIB_DIR}/Graph_lib/Window.cpp
)

target_link_libraries(
    shape_primitives
    ${FLTK_LIBRARIES}
    ${OPENGL_LIBRARIES}
)

install(TARGETS shape_primitives)
