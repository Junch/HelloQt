cmake_minimum_required(VERSION 3.15)
project(CustomTitleBar)

find_package(Qt6 COMPONENTS Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(CustomTitleBar
    main.cpp
    mainwindow.cpp
    mainwindow.h
    framelesswindow.cpp
    framelesswindow.h
    CustomTitleBar.qrc
)

target_link_libraries(CustomTitleBar PRIVATE Qt6::Widgets)

# Embed app icon into Windows executable if available
if(WIN32)
    set(APP_ICON_RC "${CMAKE_CURRENT_SOURCE_DIR}/CustomTitleBar.rc")
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/icons/app.ico")
        target_sources(CustomTitleBar PRIVATE ${APP_ICON_RC})
    endif()
endif()

set_target_properties(CustomTitleBar PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

if(WIN32)
    add_compile_options(/utf-8)
    set_target_properties(CustomTitleBar PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()
