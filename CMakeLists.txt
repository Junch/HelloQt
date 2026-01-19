cmake_minimum_required(VERSION 3.15)
project(LearnQt)

set(WINRT_VERSION "2.0.250303.1")

if(WIN32)
    if(NOT EXISTS "${CMAKE_SOURCE_DIR}/packages/Microsoft.Windows.CppWinRT.${WINRT_VERSION}")
        execute_process(
            COMMAND "${CMAKE_SOURCE_DIR}/tools/nuget.exe" install Microsoft.Windows.CppWinRT -Version ${WINRT_VERSION} -OutputDirectory "${CMAKE_SOURCE_DIR}/packages"
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        )
    endif()
endif()

set(CMAKE_CONFIGURATION_TYPES Debug Release)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib") 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

if(MSVC)
    # make the Release version create a PDB
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
    # minimize the size or the resulting EXE
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2")
endif()

add_subdirectory(HelloQt)
add_subdirectory(HelloWidget)
add_subdirectory(HelloOGL)
add_subdirectory(MemoryLeak)
add_subdirectory(ModelView)
add_subdirectory(UndoTest)
add_subdirectory(CustomTitleBar)
add_subdirectory(WebView2Test)
