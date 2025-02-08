cmake_minimum_required(VERSION 3.5)
set(TARGET_NAME MemoryLeak)
project(${TARGET_NAME} VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 COMPONENTS Core Gui Widgets LinguistTools REQUIRED)

file(GLOB SRC_FILES "*.h*" "*.c*" )
set(TS_FILE ${PROJECT_BINARY_DIR}/${TARGET_NAME}_zh_CN.ts)

qt6_create_translation(${TARGET_NAME}_QM_FILE
    ${SRC_FILES}
    ${TS_FILE}
)

add_executable(${TARGET_NAME} ${SRC_FILES} ${${TARGET_NAME}_QM_FILE})

target_link_libraries(${TARGET_NAME} Qt::Widgets)
if(WIN32)
    add_compile_options(/utf-8)
    set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt::Core> $<TARGET_FILE_DIR:${TARGET_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt::Gui> $<TARGET_FILE_DIR:${TARGET_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt::Widgets> $<TARGET_FILE_DIR:${TARGET_NAME}>
)
