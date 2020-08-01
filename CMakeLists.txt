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
        OUTPUT_NAME "Editor"
)

# OpenGL
find_package(OpenGL REQUIRED)

# glad
set(GLAD_DIR dependences/glad)

add_library(glad ${GLAD_DIR}/src/glad.c)

target_include_directories(glad PRIVATE ${GLAD_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLAD_DIR}/include)

# glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(dependences/glfw)

# glm
add_subdirectory(dependences/glm)

# {fmt}
add_subdirectory(dependences/fmt)

# stb_image
include_directories(dependences/stb)

# EnTT
add_subdirectory(dependences/entt)

target_link_libraries(${PROJECT_NAME} OpenGL::GL glad glfw glm fmt entt)