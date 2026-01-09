cmake_minimum_required(VERSION 3.15)
project(HelloQt VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

if(WIN32)
    add_executable(HelloQt "")
    set_target_properties(HelloQt PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
elseif(APPLE)
    set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/icon/icon.icns")
    qt_add_executable(HelloQt MACOSX_BUNDLE "" ${app_icon_macos})
    set_target_properties(HelloQt PROPERTIES MACOSX_BUNDLE TRUE)
    set_target_properties(HelloQt PROPERTIES MACOSX_BUNDLE_ICON_FILE icon.icns)
    set_target_properties(HelloQt PROPERTIES MACOSX_BUNDLE_GUI_IDENTIFIER "com.yourcompany.HelloQt")
    set_source_files_properties(${app_icon_macos} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
endif()

target_sources(HelloQt
    PRIVATE
        mainwindow.ui
        mainwindow.h
        mainwindow.cpp
        main.cpp
)

target_link_libraries(HelloQt PUBLIC Qt::Widgets)

add_executable(QtTest 
    tests/main.cpp
    tests/test_qstring.cpp
    tests/test_signal.cpp
    tests/counter.h  # The header file should be added, otherwise there will be build errors.
)

target_link_libraries(QtTest PRIVATE Qt::Core Qt::Widgets)

# Deploy Qt dependencies
if(WIN32)
    get_target_property(_qmake_executable Qt6::qmake IMPORTED_LOCATION)
    get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")
    
    if(WINDEPLOYQT_EXECUTABLE)
        add_custom_command(TARGET HelloQt POST_BUILD
            COMMAND "${WINDEPLOYQT_EXECUTABLE}"
                    --no-compiler-runtime
                    --no-translations
                    "$<TARGET_FILE:HelloQt>"
            COMMENT "Deploying Qt libraries"
        )
    endif()
endif()