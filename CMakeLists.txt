#Change this if you need to target a specific CMake version
cmake_minimum_required (VERSION 3.1)

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

project(game)

# Set version information in a config.h file
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
configure_file(
  "${CMAKE_SOURCE_DIR}/src/config.h.in"
  "${CMAKE_SOURCE_DIR}/src/config.h"
  )
include_directories("${PROJECT_BINARY_DIR}")

# Define sources and executable
set(EXECUTABLE_NAME "game")
file(GLOB_RECURSE source "src/*.cpp")
add_executable(${EXECUTABLE_NAME} ${source})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
include(CPack)

# ENABLE(c++11)
set_property(TARGET game PROPERTY CXX_STANDARD 11)
