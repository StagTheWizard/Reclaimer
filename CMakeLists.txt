cmake_minimum_required(VERSION 3.7)

project(Reclaimer)

set(CMAKE_CXX_STANDARD 14)

# Define sources and executable
set(EXECUTABLE_NAME "Reclaimer")

if (NOT EXISTS ${CMAKE_SOURCE_DIR}/build)
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/build)
endif()

if (NOT EXISTS ${CMAKE_SOURCE_DIR}/build/assets)
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/build/assets)
endif()

if (NOT EXISTS ${CMAKE_SOURCE_DIR}/build/shaders)
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/build/shaders)
endif()

if (NOT EXISTS ${CMAKE_SOURCE_DIR}/build/saves)
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/build/saves)
endif()


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_DEBUG")


option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(deps/glfw)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(deps/assimp)

include_directories(
        src
        deps/assimp/include
        deps/glad/include
        deps/glfw/include
        deps/glm
        deps/freetype/include)

file(GLOB DEPS_SOURCES
        deps/glad/src/glad.c)

file(GLOB PROJECT_SOURCES
        src/Launcher.cpp
        src/core/Constants.h

        src/core/Engine.h
        src/core/Engine.cpp

        src/core/world/World.h
        src/core/world/World.cpp
        src/core/world/FilterMapConfig.h
        src/core/world/TerrainMesh.h
        src/core/structs/Light.h

        src/core/world/Chunk.h
        src/core/world/Chunk.cpp

        src/core/world/Tile.h
        src/core/world/TileTypes.h
        src/core/world/TileType.h

        src/core/rendering/WorldRenderer.h
        src/core/rendering/WorldRenderer.cpp
        src/core/rendering/TextRenderer.h
        src/core/rendering/TextRenderer.cpp

        src/core/text/FontTextureAtlas.h
        src/core/text/FontTextureAtlas.cpp
        src/core/text/FontChar.h
        src/core/text/FontData.h

        src/core/rendering/shaders/ShaderProgram.h
        src/core/rendering/shaders/ShaderProgram.cpp
        src/core/rendering/shaders/TerrainShaderProgram.h
        src/core/rendering/shaders/TerrainShaderProgram.cpp
        src/core/rendering/shaders/TextShaderProgram.cpp
        src/core/rendering/shaders/TextShaderProgram.cpp

        src/core/Camera.h
        src/core/Camera.cpp
        src/core/timing/Timer.h
        src/core/timing/Timer.cpp

        src/core/states/State.h
        src/core/states/State.cpp
        src/core/states/IntroState.h
        src/core/states/IntroState.cpp
        src/core/states/GameState.h
        src/core/states/GameState.cpp

        src/extensions/text/NumericToString.h
        src/extensions/geometry/SpacialChecks.h
        src/extensions/fastnoise/FastNoise.h
        src/extensions/fastnoise/FastNoise.cpp
        )

set(PROJECT_SHADERS
        shaders/Terrain.vert
        shaders/Terrain.tesc
        shaders/Terrain.tese
        shaders/Terrain.frag
        shaders/Text.vert
        shaders/Text.frag)

set(PROJECT_ASSETS
        assets/fonts/Menlo-Regular.ttf)

file(GLOB PROJECT_CONFIGS
        CMakeLists.txt)

source_group("src" FILES ${PROJECT_SOURCES})
source_group("shaders" FILES ${PROJECT_SHADERS})
source_group("deps" FILES ${DEPS_SOURCES})
source_group("assets" FILES ${PROJECT_ASSETS})

# Copy all the resources into the bin
set(PROJECT_RESOURCES ${PROJECT_SHADERS} ${PROJECT_ASSETS})
if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
    foreach(item IN LISTS PROJECT_RESOURCES)
        add_custom_command(
                OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${item}"
                COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${item}" "${CMAKE_CURRENT_BINARY_DIR}/${item}"
                DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${item}"
        )
        message(STATUS "COPYING " ${item})
        message(STATUS "from " "${CMAKE_CURRENT_SOURCE_DIR}/${item}" " to " "${CMAKE_CURRENT_BINARY_DIR}/${item}")
    endforeach()
endif()

add_custom_target(data-target ALL DEPENDS ${PROJECT_RESOURCES})

add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
        ${PROJECT_SHADERS}
        ${PROJECT_ASSETS}
        ${PROJECT_CONFIGS}
        ${DEPS_SOURCES})

target_link_libraries(${PROJECT_NAME}
        glfw
        assimp
        freetype
        ${GLFW_LIBRARIES})

# boost::filesystem
set(Boost_ADDITIONAL_VERSIONS "1.78" "1.78.0" "1.79" "1.79.0")
find_package(Boost 1.34.0 REQUIRED system filesystem serialization)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${EXECUTABLE_NAME} ${Boost_LIBRARIES})
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)