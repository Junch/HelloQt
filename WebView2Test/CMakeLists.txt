cmake_minimum_required(VERSION 3.15)
project(WebView2Test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# 手动配置WebView2
set(WEBVIEW2_ROOT "C:/github/vcpkg/installed/x64-windows")
set(WEBVIEW2_INCLUDE_DIR "${WEBVIEW2_ROOT}/include")
set(WEBVIEW2_LIB_DIR "${WEBVIEW2_ROOT}/lib")
set(WEBVIEW2_BIN_DIR "${WEBVIEW2_ROOT}/bin")

add_library(WebView2::WebView2 SHARED IMPORTED)
set_target_properties(WebView2::WebView2 PROPERTIES
    IMPORTED_LOCATION "${WEBVIEW2_LIB_DIR}/WebView2Loader.dll.lib"
    IMPORTED_IMPLIB "${WEBVIEW2_LIB_DIR}/WebView2Loader.dll.lib"
    INTERFACE_INCLUDE_DIRECTORIES "${WEBVIEW2_INCLUDE_DIR}"
)

add_executable(WebView2Test
  main.cpp
  qwebview2.cpp
  qwebview2.h
)

target_link_libraries(WebView2Test PRIVATE Qt6::Widgets WebView2::WebView2)

target_compile_definitions(WebView2Test PRIVATE UNICODE _UNICODE)

# 复制WebView2Loader.dll到输出目录（重要！）
add_custom_command(TARGET WebView2Test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${WEBVIEW2_BIN_DIR}/WebView2Loader.dll"
        $<TARGET_FILE_DIR:WebView2Test>
    COMMENT "Copying WebView2Loader.dll"
)
