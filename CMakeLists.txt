cmake_minimum_required(VERSION 3.16)

project(Framebuffer
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples")

set(SOURCES
    src/bitmap_cvw.cpp
    src/framebuffer.cpp
)

add_library(framebuffer
    ${SOURCES}
)

add_library(framebuffer::framebuffer ALIAS framebuffer)

target_include_directories(framebuffer
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(framebuffer PUBLIC cxx_std_20)

set(examples "basiese_bal" "hor_lyn" "blaai_teks" "flits" "sin_ontploffing" "mario" "alfa_toets" "toets")

foreach(example ${examples})
    add_executable(${example}
    examples/${example}/main.cpp)
    target_link_libraries(${example}
    framebuffer
    )
endforeach()
