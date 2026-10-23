cmake_minimum_required(VERSION 3.16)

project(framebuffer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    include/*.h
    fonts/*.h
)

add_executable(framebuffer
    ${SOURCES}
)

target_include_directories(framebuffer PRIVATE
    include
    fonts
)

include(GNUInstallDirs)

install(TARGETS framebuffer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
