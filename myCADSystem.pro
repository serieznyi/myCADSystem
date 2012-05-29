#-------------------------------------------------
#
# Project created by QtCreator 2012-04-07T13:07:27
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = myCADSystem
TEMPLATE = app


SOURCES += \
    work.cpp \
    statusbar.cpp \
    paintingzone.cpp \
    menubar.cpp \
    mainwindow.cpp \
    main.cpp \
    glwidget.cpp \
    contextmenu.cpp \
    toolbars/select_primitive_toolbar.cpp \
    toolbars/scene_control_toolbar.cpp \
    toolbars/list_primitive_toolbar.cpp \
    toolbars/action_primitive_toolbar.cpp \
    lib/element.cpp \
    lib/container.cpp \
    lib/action/translate.cpp \
    lib/action/rotate.cpp \
    lib/action/action.cpp \
    lib/primitive/substractprimitive.cpp \
    lib/primitive/sphere.cpp \
    lib/primitive/pyramid.cpp \
    lib/primitive/primitive.cpp \
    lib/primitive/intersectprimitive.cpp \
    lib/primitive/groupprimitive.cpp \
    lib/primitive/cube.cpp \
    lib/action/scale.cpp

HEADERS  += \
    work.h \
    statusbar.h \
    resource.h \
    paintingzone.h \
    menubar.h \
    mainwindow.h \
    glwidget.h \
    contextmenu.h \
    toolbars/select_primitive_toolbar.h \
    toolbars/scene_control_toolbar.h \
    toolbars/list_primitive_toolbar.h \
    toolbars/action_primitive_toolbar.h \
    lib/lib.h \
    lib/element.h \
    lib/container.h \
    lib/action/translate.h \
    lib/action/rotate.h \
    lib/action/action.h \
    lib/primitive/substractprimitive.h \
    lib/primitive/sphere.h \
    lib/primitive/pyramid.h \
    lib/primitive/primitive.h \
    lib/primitive/intersectprimitive.h \
    lib/primitive/groupprimitive.h \
    lib/primitive/cube.h \
    matrix.h \
    invers.h \
    lib/action/scale.h

FORMS +=

RESOURCES +=

