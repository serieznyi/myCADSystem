cmake_minimum_required(VERSION 3.7)

project(myCADSystem)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(OpenGL REQUIRED)
find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5OpenGL)

file(GLOB_RECURSE CPPS "src/*/*.cpp")
add_executable(${PROJECT_NAME} ${CPPS})

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLUT_INCLUDE_DIRS})

set(QT_USE_QTOPENGL TRUE)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

qt5_use_modules(${PROJECT_NAME} Core Gui Widgets)