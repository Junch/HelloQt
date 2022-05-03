cmake_minimum_required(VERSION 3.1.0)
project(HelloQt VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(HelloQt
    mainwindow.ui
    mainwindow.h
    mainwindow.cpp
    main.cpp
)

target_link_libraries(HelloQt Qt5::Widgets)
set_target_properties(HelloQt PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

add_executable(QtTest 
    tests/main.cpp
    tests/test_qstring.cpp
    tests/test_signal.cpp
    tests/counter.h  # The header file should be added, otherwise there will be build errors.
)

target_link_libraries(QtTest PRIVATE Qt5::Core Qt5::Widgets)

add_custom_command(TARGET HelloQt POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:HelloQt>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:HelloQt>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:HelloQt>
)
