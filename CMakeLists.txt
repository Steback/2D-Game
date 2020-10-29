cmake_minimum_required(VERSION 3.16)
project(2D_Game)

set(CMAKE_CXX_STANDARD 20)

file(GLOB HEADER_FILES source/*.hpp)
file(GLOB SOURCE_FILES source/*.cpp)

add_executable(2D_Game ${SOURCE_FILES} ${HEADER_FILES})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES
        OUTPUT_NAME "2D-Game"
)

# OpenGL
find_package(OpenGL REQUIRED)

# glad
add_library(glad thirdparty/glad/src/glad.c)

target_include_directories(glad PRIVATE thirdparty/glad/include)
target_include_directories(${PROJECT_NAME} PRIVATE thirdparty/glad/include)

# glfw
add_subdirectory(thirdparty/glfw)

# glm
add_subdirectory(thirdparty/glm)

# stb_image
include_directories(thirdparty/stb)

# EnTT
include_directories(thirdparty/entt)

# Box2D
add_subdirectory(thirdparty/box2d/src)

# Tinyxml2
add_subdirectory(thirdparty/tinyxml2)
include_directories(thirdparty/tinyxml2)

# Lua
add_subdirectory(thirdparty/lua)
include_directories(thirdparty/lua)

# sol2
include_directories(thirdparty/sol2)

# spdlog
include_directories(thirdparty/spdlog)

target_link_libraries(${PROJECT_NAME} OpenGL::GL glad glfw glm spdlog box2d tinyxml2 lua)