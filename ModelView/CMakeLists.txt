﻿cmake_minimum_required(VERSION 3.1.0)
set(TARGET_NAME ModelView)
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

find_package(Qt5 COMPONENTS Core Gui Widgets LinguistTools REQUIRED)

add_compile_options(/utf-8)

file(GLOB SRC_FILES "*.h*" "*.c*" "*.ui")
set(TS_FILE ${PROJECT_BINARY_DIR}/${TARGET_NAME}_zh_CN.ts)

qt5_create_translation(${TARGET_NAME}_QM_FILE
    ${SRC_FILES}
    ${TS_FILE}
)

add_executable(${TARGET_NAME} ${SRC_FILES} ${${TARGET_NAME}_QM_FILE})

target_link_libraries(${TARGET_NAME} Qt5::Widgets)
set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${TARGET_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${TARGET_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${TARGET_NAME}>
)
