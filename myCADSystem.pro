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
    lib/lib_action/translate.cpp \
    lib/lib_action/subtraction.cpp \
    lib/lib_action/rotate.cpp \
    lib/lib_action/intersection.cpp \
    lib/lib_action/group.cpp \
    lib/lib_action/action.cpp \
    lib/lib_primitive/pyramid.cpp \
    lib/lib_primitive/cube.cpp \
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
    lib/lib_primitive/primitive.cpp \
    toolbars/toolbar.cpp

HEADERS  += \
    lib/element.h \
    lib/lib_action/translate.h \
    lib/lib_action/subtraction.h \
    lib/lib_action/rotate.h \
    lib/lib_action/intersection.h \
    lib/lib_action/group.h \
    lib/lib_action/action.h \
    lib/lib_primitive/pyramid.h \
    lib/lib_primitive/cube.h \
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
    lib/lib_primitive/primitive.h \
    toolbars/toolbar.h

FORMS +=

RESOURCES +=

