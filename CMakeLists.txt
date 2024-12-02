cmake_minimum_required(VERSION 3.25)
project(ImageViewer VERSION 1.0.0 LANGUAGES C CXX)

find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
find_package(glm REQUIRED)
find_package(stb REQUIRED)
find_package(imgui REQUIRED)
find_package(spdlog REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(IMGV_CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/core)
set(
    IMGV_CORE_INCLUDE_DIR 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/events
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/subcore
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/renderer
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/apis
)

set(
    IMGV_CORE_HEADERS
        ${IMGV_CORE_DIR}/subcore/typedef.hpp
        ${IMGV_CORE_DIR}/subcore/base.hpp
        ${IMGV_CORE_DIR}/subcore/asserts.hpp
        ${IMGV_CORE_DIR}/subcore/log.hpp
        ${IMGV_CORE_DIR}/subcore/keycodes.hpp
        ${IMGV_CORE_DIR}/events/events.hpp
        ${IMGV_CORE_DIR}/events/mouse_events.hpp
        ${IMGV_CORE_DIR}/events/keyboard_events.hpp
        ${IMGV_CORE_DIR}/events/window_events.hpp
        ${IMGV_CORE_DIR}/renderer/buffers.hpp
        ${IMGV_CORE_DIR}/renderer/renderer.hpp
        ${IMGV_CORE_DIR}/apis/opengl/opengl.hpp
        ${IMGV_CORE_DIR}/apis/opengl/gl_buffers.hpp
        ${IMGV_CORE_DIR}/apis/opengl/gl_renderer.hpp

)

set(
    IMGV_CORE_SOURCES
        ${IMGV_CORE_DIR}/subcore/log.cpp
        ${IMGV_CORE_DIR}/renderer/buffers.cpp
        ${IMGV_CORE_DIR}/renderer/renderer.cpp
        ${IMGV_CORE_DIR}/apis/opengl/gl_buffers.cpp
        ${IMGV_CORE_DIR}/apis/opengl/gl_renderer.cpp
)

add_library(imgv_core STATIC ${IMGV_CORE_HEADERS} ${IMGV_CORE_SOURCES})
target_include_directories(imgv_core PUBLIC ${IMGV_CORE_INCLUDE_DIR})
target_link_libraries(imgv_core PUBLIC glad::glad glfw spdlog::spdlog glm::glm stb::stb imgui::imgui)

if(CMAKE_BUILD_TYPE_INIT STREQUAL "Debug")
    add_compile_definitions(IMGV_DEBUG)
else()
    add_compile_definitions(IMGV_RELEASE)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(imgv_core PUBLIC IMGV_PLATFORM_WINDOWS)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions(imgv_core PUBLIC IMGV_PLATFORM_LINUX)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(imgv_core PUBLIC IMGV_PLATFORM_MACOS)
endif()

if(BUILD_SHARED_LIBS)
    add_compile_definitions(IMGV_SHARED)
else()
    add_compile_definitions(IMGV_STATIC)
endif()

