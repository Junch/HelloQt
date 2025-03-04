cmake_minimum_required(VERSION 3.5)
set(TARGET_NAME HelloOGL)
project(${TARGET_NAME} VERSION 1.0.0 LANGUAGES CXX)

message("CMAKE_PROJECT_NAKE ${CMAKE_PROJECT_NAKE}")
message("PROJECT_NAKE ${PROJECT_NAKE}")

message("CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")
message("CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
message("CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
message("CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
message("PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
message("PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}")

message("CMAKE_CURRENT_LIST_FILE ${CMAKE_CURRENT_LIST_FILE}")
message("CMAKE_CURRENT_LIST_LINE ${CMAKE_CURRENT_LIST_LINE}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 COMPONENTS Core Gui Widgets OpenGLWidgets OpenGL LinguistTools REQUIRED)

file(GLOB SRC_FILES "*.h*" "*.c*" )
set(TS_FILE ${PROJECT_BINARY_DIR}/${TARGET_NAME}_zh_CN.ts)

qt6_create_translation(${TARGET_NAME}_QM_FILE
    ${SRC_FILES}
    ${TS_FILE}
)

if(WIN32)
    add_executable(${TARGET_NAME} WIN32 ${SRC_FILES} ${${TARGET_NAME}_QM_FILE})
elseif(APPLE) # Add macOS specific icon settings
    # https://www.svgrepo.com/svg/511301/3d-modelling-819
    set(APP_ICON_MACOSX ${CMAKE_CURRENT_SOURCE_DIR}/resources/app.icns)
    qt_add_executable(${TARGET_NAME} MACOSX_BUNDLE ${SRC_FILES} ${APP_ICON_MACOSX})
    set_source_files_properties(${APP_ICON_MACOSX} PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources"
    )
    set_target_properties(${TARGET_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_ICON_FILE app.icns
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.yourcompany.HelloOGL"
    )
endif()

target_link_libraries(${TARGET_NAME} PUBLIC Qt::Widgets Qt::OpenGLWidgets Qt::OpenGL)
if(WIN32)
    add_compile_options(/utf-8)
    set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt::Core> $<TARGET_FILE_DIR:${TARGET_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt::Gui> $<TARGET_FILE_DIR:${TARGET_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt::Widgets> $<TARGET_FILE_DIR:${TARGET_NAME}>
)
