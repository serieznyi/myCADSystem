cmake_minimum_required(VERSION 3.15)

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
        src/lib/action/Action.cpp
        src/lib/action/Action.h
        src/lib/action/Group.cpp
        src/lib/action/Group.h
        src/lib/action/Intersection.cpp
        src/lib/action/Intersection.h
        src/lib/action/Rotate.cpp
        src/lib/action/Rotate.h
        src/lib/action/Scale.cpp
        src/lib/action/Scale.h
        src/lib/action/Stretch.cpp
        src/lib/action/Stretch.h
        src/lib/action/Subtraction.h
        src/lib/action/Translate.cpp
        src/lib/action/Translate.h
        src/lib/primitive/Cube.cpp
        src/lib/primitive/Cube.h
        src/lib/primitive/GroupPrimitive.cpp
        src/lib/primitive/GroupPrimitive.h
        src/lib/primitive/IntersectPrimitive.cpp
        src/lib/primitive/IntersectPrimitive.h
        src/lib/primitive/Primitive.cpp
        src/lib/primitive/Primitive.h
        src/lib/primitive/Pyramid.cpp
        src/lib/primitive/Pyramid.h
        src/lib/primitive/Sphere.cpp
        src/lib/primitive/Sphere.h
        src/lib/primitive/SubstractPrimitive.cpp
        src/lib/primitive/SubstractPrimitive.h
        src/lib/Container.cpp
        src/lib/Container.h
        src/lib/Element.cpp
        src/lib/Element.h
        src/lib/lib.h
        src/gui/toolbars/ActionPrimitiveToolBar.cpp
        src/gui/toolbars/ActionPrimitiveToolBar.h
        src/gui/toolbars/ListPrimitiveToolbar.cpp
        src/gui/toolbars/ListPrimitiveToolbar.h
        src/gui/toolbars/SceneControlToolbar.cpp
        src/gui/toolbars/SceneControlToolbar.h
        src/gui/toolbars/SelectPrimitiveToolbar.cpp
        src/gui/toolbars/SelectPrimitiveToolbar.h
        src/gui/toolbars/ToolBar.cpp
        src/gui/toolbars/ToolBar.h
        src/gui/ContextMenu.cpp
        src/gui/ContextMenu.h
        src/GLWidget.cpp
        src/GLWidget.h
        src/invers.h
        src/main.cpp
        src/gui/MainWindow.cpp
        src/gui/MainWindow.h
        src/matrix.h
        src/gui/MenuBar.cpp
        src/gui/MenuBar.h
        src/gui/PaintingZone.cpp
        src/gui/PaintingZone.h
        src/resource.h
        src/gui/StatusBar.cpp
        src/gui/StatusBar.h
        src/Work.cpp
        src/Work.h
)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLUT_INCLUDE_DIRS})

set(QT_USE_QTOPENGL TRUE)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

qt5_use_modules(${PROJECT_NAME} Core Gui Widgets)