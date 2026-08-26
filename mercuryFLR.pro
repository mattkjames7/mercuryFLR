TEMPLATE = app
TARGET = mercuryFLR
QT = core gui widgets
CONFIG += link_pkgconfig
PKGCONFIG += cairo

SOURCES += \
    src/cutout.cc \
    src/flatarrow.cc \
    src/flr.cc \
    src/initbuffers.cc \
    src/initgl.cc \
    src/magnetopause.cc \
    src/main.cc \
    src/mainwindow.cc \
    src/mercurysurface.cc \
    src/ocb.cc \
    src/openglwidget.cc \
    src/streamline.cc \
    src/wiggle.cc \

HEADERS += \
    include/cutout.h \
    include/flatarrow.h \
    include/flr.h \
    include/initbuffers.h \
    include/initgl.h \
    include/magnetopause.h \
    include/mainwindow.h \
    include/mercurysurface.h \
    include/ocb.h \
    include/openglwidget.h \
    include/streamline.h \
    include/ui_mainwindow.h \
    include/wiggle.h \

FORMS += \
    forms/mainwindow.ui \

RESOURCES += resources.qrc
