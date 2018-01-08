# TODO Upgrage to 3.10
cmake_minimum_required(VERSION 3.7)

project(myCADSystem)

# TODO change on 17
set (CMAKE_CXX_STANDARD 98)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(OpenGL REQUIRED)
find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5OpenGL)

add_executable(${PROJECT_NAME}
        src/lib/action/action.cpp
        src/lib/action/action.h
        src/lib/action/group.cpp
        src/lib/action/group.h
        src/lib/action/intersection.cpp
        src/lib/action/intersection.h
        src/lib/action/rotate.cpp
        src/lib/action/rotate.h
        src/lib/action/scale.cpp
        src/lib/action/scale.h
        src/lib/action/stretch.cpp
        src/lib/action/stretch.h
        src/lib/action/subtraction.h
        src/lib/action/translate.cpp
        src/lib/action/translate.h
        src/lib/primitive/cube.cpp
        src/lib/primitive/cube.h
        src/lib/primitive/groupprimitive.cpp
        src/lib/primitive/groupprimitive.h
        src/lib/primitive/intersectprimitive.cpp
        src/lib/primitive/intersectprimitive.h
        src/lib/primitive/primitive.cpp
        src/lib/primitive/primitive.h
        src/lib/primitive/pyramid.cpp
        src/lib/primitive/pyramid.h
        src/lib/primitive/sphere.cpp
        src/lib/primitive/sphere.h
        src/lib/primitive/substractprimitive.cpp
        src/lib/primitive/substractprimitive.h
        src/lib/container.cpp
        src/lib/container.h
        src/lib/element.cpp
        src/lib/element.h
        src/lib/lib.h
        src/toolbars/action_primitive_toolbar.cpp
        src/toolbars/action_primitive_toolbar.h
        src/toolbars/list_primitive_toolbar.cpp
        src/toolbars/list_primitive_toolbar.h
        src/toolbars/scene_control_toolbar.cpp
        src/toolbars/scene_control_toolbar.h
        src/toolbars/select_primitive_toolbar.cpp
        src/toolbars/select_primitive_toolbar.h
        src/toolbars/toolbar.cpp
        src/toolbars/toolbar.h
        src/contextmenu.cpp
        src/contextmenu.h
        src/glwidget.cpp
        src/glwidget.h
        src/invers.h
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/matrix.h
        src/menubar.cpp
        src/menubar.h
        src/paintingzone.cpp
        src/paintingzone.h
        src/resource.h
        src/statusbar.cpp
        src/statusbar.h
        src/work.cpp
        src/work.h
)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLUT_INCLUDE_DIRS})

set(QT_USE_QTOPENGL TRUE)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

qt5_use_modules(${PROJECT_NAME} Core Gui Widgets)