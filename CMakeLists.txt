cmake_minimum_required(VERSION 3.1.0)

project(HelloQt VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "/Users/juchen3/Qt/5.15.2/clang_64")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(HelloQt
    mainwindow.ui
    mainwindow.cpp
    main.cpp
    mainwindow.h
)

target_link_libraries(HelloQt Qt5::Widgets)
