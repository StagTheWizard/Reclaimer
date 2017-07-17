cmake_minimum_required(VERSION 3.7)

project(Reclaimer)

set(CMAKE_CXX_STANDARD 14)

# Define sources and executable
set(EXECUTABLE_NAME "Reclaimer")

if (NOT EXISTS ${CMAKE_SOURCE_DIR}/build)
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/build)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

include_directories(src)

file(GLOB PROJECT_SOURCES
        src/Launcher.cpp
        src/core/Constants.h

        src/core/Engine.h
        src/core/Engine.cpp

        src/core/TextRenderer.h
        src/core/TextRenderer.cpp

        src/core/shaders/ShaderProgram.h
        src/core/shaders/ShaderProgram.cpp
        src/core/shaders/TextShaderProgram.cpp
        src/core/shaders/TextShaderProgram.cpp

        src/core/Camera.h
        src/core/Camera.cpp

        src/core/states/State.h
        src/core/states/State.cpp
        src/core/states/IntroState.h
        src/core/states/IntroState.cpp
        src/core/states/GameState.h
        src/core/states/GameState.cpp
        )

set(PROJECT_SHADERS
        shaders/Text.vert
        shaders/Text.frag)

set(PROJECT_ASSETS
        assets/fonts/Menlo-Regular.ttf)

file(GLOB PROJECT_CONFIGS
        CMakeLists.txt)

source_group("src" FILES ${PROJECT_SOURCES})
source_group("shaders" FILES ${PROJECT_SHADERS})
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

add_executable(Reclaimer
        ${PROJECT_SOURCES}
        ${PROJECT_SHADERS}
        ${PROJECT_ASSETS}
        ${PROJECT_CONFIGS})


# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
if (OPENGL_FOUND)
    target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_LIBRARIES})
    # or: target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_gl_LIBRARY})
    target_link_libraries(${EXECUTABLE_NAME} m)  # if you use maths.h
endif()

# boost::fi lesystem
#set(Boost_ADDITIONAL_VERSIONS "1.78" "1.78.0" "1.79" "1.79.0")
find_package(Boost 1.34.0 REQUIRED system filesystem)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${EXECUTABLE_NAME} ${Boost_LIBRARIES})
endif()

#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)