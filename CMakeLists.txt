cmake_minimum_required(VERSION 3.16)

project(Framebuffer)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples")

set(SOURCES
    src/bitmap_cvw.cpp
    src/framebuffer.cpp
)

add_library(framebuffer
    ${SOURCES}
)

target_include_directories(framebuffer
    PUBLIC
    include
    fonts
)

add_executable(animation1
    examples/animation1/main.cpp
)

target_link_libraries(animation1
    framebuffer
)

add_executable(animation2
    examples/animation2/main.cpp
)

target_link_libraries(animation2
    framebuffer
)

add_executable(animation5
    examples/animation5/main.cpp
)

target_link_libraries(animation5
    framebuffer
)

add_executable(animation6
    examples/animation6/main.cpp
)

target_link_libraries(animation6
    framebuffer
)
