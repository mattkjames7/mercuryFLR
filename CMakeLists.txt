cmake_minimum_required(VERSION 3.16)

project(mercuryFLR LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS forms)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(FLTK REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(CAIRO REQUIRED IMPORTED_TARGET cairo)

add_executable(mercuryFLR
    src/cutout.cc
    src/flatarrow.cc
    src/flr.cc
    src/legacy/ExampleTraces.cpp
    src/legacy/TraceWrapper.cpp
    src/legacy/kt17.cc
    src/legacy/kt17trace.cc
    src/initbuffers.cc
    src/initgl.cc
    src/magnetopause.cc
    src/main.cc
    src/mainwindow.cc
    src/mercurysurface.cc
    src/ocb.cc
    src/openglwidget.cc
    src/streamline.cc
    src/wiggle.cc
    include/mainwindow.h
    include/openglwidget.h
    forms/mainwindow.ui
    resources.qrc
)

target_include_directories(mercuryFLR
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/legacy
        ${CMAKE_CURRENT_BINARY_DIR}
        ${FLTK_INCLUDE_DIR}
)

target_link_libraries(mercuryFLR
    PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        OpenGL::GL
        OpenGL::GLU
        GLUT::GLUT
        ${FLTK_LIBRARIES}
        PkgConfig::CAIRO
)
