#-------------------------------------------------
#
# Project created by QtCreator 2012-04-07T13:07:27
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = myCADSystem
TEMPLATE = app


SOURCES += \
    lib/element.cpp \
    work.cpp \
    statusbar.cpp \
    paintingzone.cpp \
    menubar.cpp \
    mainwindow.cpp \
    main.cpp \
    glwidget.cpp \
    toolbars/select_primitive_toolbar.cpp \
    toolbars/scene_control_toolbar.cpp \
    toolbars/action_primitive_toolbar.cpp \
    toolbars/toolbar.cpp \
    lib/action/translate.cpp \
    lib/action/subtraction.cpp \
    lib/action/rotate.cpp \
    lib/action/intersection.cpp \
    lib/action/group.cpp \
    lib/action/action.cpp \
    lib/primitive/pyramid.cpp \
    lib/primitive/primitive.cpp \
    lib/primitive/cube.cpp \
    lib/primitive/sphere.cpp \
    toolbars/list_primitive_toolbar.cpp

HEADERS  += \
    lib/element.h \
    work.h \
    statusbar.h \
    resource.h \
    paintingzone.h \
    menubar.h \
    mainwindow.h \
    glwidget.h \
    toolbars/select_primitive_toolbar.h \
    toolbars/scene_control_toolbar.h \
    toolbars/action_primitive_toolbar.h \
    toolbars/toolbar.h \
    lib/action/translate.h \
    lib/action/subtraction.h \
    lib/action/rotate.h \
    lib/action/intersection.h \
    lib/action/group.h \
    lib/action/action.h \
    lib/primitive/pyramid.h \
    lib/primitive/primitive.h \
    lib/primitive/cube.h \
    lib/lib.h \
    lib/primitive/sphere.h \
    toolbars/list_primitive_toolbar.h

FORMS +=

RESOURCES +=

