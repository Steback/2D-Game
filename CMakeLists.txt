cmake_minimum_required(VERSION 3.16)
project(2D_Game)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE HEADER_FILES source/*.hpp)
file(GLOB_RECURSE SOURCE_FILES source/*.cpp)
file(GLOB_RECURSE GUI_HEADER_FILES source/gui/*.hpp)
file(GLOB_RECURSE GUI_SOURCE_FILES source/gui/*.cpp)

add_executable(2D_Game ${SOURCE_FILES} ${HEADER_FILES} ${GUI_SOURCE_FILES} ${GUI_HEADER_FILES})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

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
add_subdirectory(thirdparty/spdlog)

# NoesisGUI
file(GLOB NOESIS_BIN thirdparty/NoesisGUI/Bin/linux_x86_64/libNoesis.so)
file(GLOB NOESISAPP_BIN thirdparty/NoesisGUI/Bin/linux_x86_64/libNoesisApp.so)

include_directories(thirdparty/NoesisGUI/Include)
include_directories(thirdparty/NoesisGUI/Src/Packages/Render/GLRenderDevice/Include)
include_directories(thirdparty/NoesisGUI/Src/Packages/App/Providers/Include)
include_directories(thirdparty/NoesisGUI/Src/Packages/App/Theme/Include)
include_directories(thirdparty/NoesisGUI/Src/Packages/App/ApplicationLauncher/Include)
include_directories(thirdparty/NoesisGUI/Src/Packages/App/Display/Include)
include_directories(thirdparty/NoesisGUI/Src/Packages/App/Interactivity/Include)

set(BIN2H ${PROJECT_SOURCE_DIR}/thirdparty/NoesisGUI/Src/Tools/Bin2h/bin2h.py)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/data)

file(GLOB_RECURSE xamlFiles ${PROJECT_SOURCE_DIR}/data/*.xaml)
foreach(xamlFile ${xamlFiles})
    get_filename_component(fileName ${xamlFile} NAME)
    message("[NOESIS] ${fileName} > ${fileName}.bin.h")
    execute_process(COMMAND python ${BIN2H} ${xamlFile}
            OUTPUT_FILE ${PROJECT_BINARY_DIR}/data/${fileName}.bin.h)
    set(XAML_SRC ${XAML_SRC} data/${fileName}.bin.h)
endforeach()

file(GLOB_RECURSE mp3Files ${PROJECT_SOURCE_DIR}/data/*.mp3)
foreach(mp3File ${mp3Files})
    get_filename_component(fileName ${mp3File} NAME)
    message("[NOESIS] ${fileName} > ${fileName}.bin.h")
    execute_process(COMMAND python ${BIN2H} ${mp3File}
            OUTPUT_FILE ${PROJECT_BINARY_DIR}/data/${fileName}.bin.h)
    set(MP3_SRC ${MP3_SRC} data/${fileName}.bin.h)
endforeach()

file(GLOB_RECURSE ttfFiles ${PROJECT_SOURCE_DIR}/data/fonts/*.ttf)
foreach(ttfFile ${ttfFiles})
    get_filename_component(fileName ${ttfFile} NAME)
    message("[NOESIS] ${fileName} > ${fileName}.bin.h")
    execute_process(COMMAND python ${BIN2H} ${ttfFile}
            OUTPUT_FILE ${PROJECT_BINARY_DIR}/data/${fileName}.bin.h)
    set(TTF_SRC ${TTF_SRC} data/${fileName}.bin.h)
endforeach()

include_directories(${PROJECT_BINARY_DIR}/data)

target_link_libraries(${PROJECT_NAME} OpenGL::GL glad glfw glm spdlog box2d tinyxml2 lua ${NOESIS_BIN} ${NOESISAPP_BIN})
target_sources(${PROJECT_NAME} PRIVATE ${XAML_SRC} ${MP3_SRC} ${TTF_SRC})