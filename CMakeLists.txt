cmake_minimum_required(VERSION 3.9)

project(myCADSystem)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(OpenGL)
find_package(Qt5OpenGL)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/lib")

file(GLOB CPPS "src/*.cpp")

add_definitions(-Wall -O2)

add_executable(${PROJECT_NAME} ${CPPS})

qt5_use_modules(${PROJECT_NAME} Core Gui Widgets)