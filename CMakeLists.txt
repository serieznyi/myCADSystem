cmake_minimum_required(VERSION 3.10)

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
        src/gui/toolbars/action_primitive_toolbar.cpp
        src/gui/toolbars/action_primitive_toolbar.h
        src/gui/toolbars/list_primitive_toolbar.cpp
        src/gui/toolbars/list_primitive_toolbar.h
        src/gui/toolbars/scene_control_toolbar.cpp
        src/gui/toolbars/scene_control_toolbar.h
        src/gui/toolbars/select_primitive_toolbar.cpp
        src/gui/toolbars/select_primitive_toolbar.h
        src/gui/toolbars/toolbar.cpp
        src/gui/toolbars/toolbar.h
        src/gui/contextmenu.cpp
        src/gui/contextmenu.h
        src/glwidget.cpp
        src/glwidget.h
        src/invers.h
        src/main.cpp
        src/gui/mainwindow.cpp
        src/gui/mainwindow.h
        src/matrix.h
        src/gui/menubar.cpp
        src/gui/menubar.h
        src/gui/paintingzone.cpp
        src/gui/paintingzone.h
        src/resource.h
        src/gui/statusbar.cpp
        src/gui/statusbar.h
        src/work.cpp
        src/work.h
)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLUT_INCLUDE_DIRS})

set(QT_USE_QTOPENGL TRUE)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

qt5_use_modules(${PROJECT_NAME} Core Gui Widgets)