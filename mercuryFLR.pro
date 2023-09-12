TEMPLATE = app
TARGET = mercuryFLR
QT = core gui widgets

SOURCES += \
    src/initbuffers.cc \
    src/initgl.cc \
    src/magnetopause.cc \
    src/main.cc \
    src/mainwindow.cc \
    src/mercurysurface.cc \
    src/wiggle.cc \

HEADERS += \
    include/initbuffers.h \
    include/initgl.h \
    include/magnetopause.h \
    include/mainwindow.h \
    include/mercurysurface.h \
    include/ui_mainwindow.h \
    include/wiggle.h \

FORMS += \
    forms/mainwindow.ui \

RESOURCES += resources.qrc
