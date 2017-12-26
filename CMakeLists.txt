cmake_minimum_required(VERSION 3.9)

project(myCADSystem)

set(CMAKE_CXX_STANDARD 11)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )

#qt5_use_modules( Core Widgets Gui )

add_executable(myCADSystem
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
        src/lib/lib_action/action.cpp
        src/lib/lib_action/action.h
        src/lib/lib_action/group.cpp
        src/lib/lib_action/group.h
        src/lib/lib_action/intersection.cpp
        src/lib/lib_action/intersection.h
        src/lib/lib_action/rotate.cpp
        src/lib/lib_action/rotate.h
        src/lib/lib_action/subtraction.cpp
        src/lib/lib_action/subtraction.h
        src/lib/lib_action/translate.cpp
        src/lib/lib_action/translate.h
        src/lib/lib_primitive/cube.cpp
        src/lib/lib_primitive/cube.h
        src/lib/lib_primitive/primitive.cpp
        src/lib/lib_primitive/primitive.h
        src/lib/lib_primitive/pyramid.cpp
        src/lib/lib_primitive/pyramid.h
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
        src/work.h)
