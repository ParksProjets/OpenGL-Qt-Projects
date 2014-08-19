#-------------------------------------------------
#
# Project created by QtCreator 2014-05-20T16:45:17
#
#-------------------------------------------------

QT       += core gui widgets opengl 3d

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -lGLU

TARGET = CatmullRomCurveEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    interpolation.cpp \
    openglview.cpp \
    interaction.cpp \
    animation.cpp \
    arclength.cpp

HEADERS  += mainwindow.h \
    openglview.h \
    interpolation.h \
    interaction.h \
    animation.h \
    arclength.h

FORMS    += mainwindow.ui
