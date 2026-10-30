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

set(examples "basiese_bal" "hor_lyn" "blaai_teks" "flits" "sin_ontploffing" "mario" "alfa_toets")

foreach(example ${examples})
    add_executable(${example}
    examples/${example}/main.cpp)
    target_link_libraries(${example}
    framebuffer
    )
endforeach()