#-------------------------------------------------
#
# Project created by QtCreator 2010-12-20T14:22:30
#
#-------------------------------------------------

QT       -= core gui
TARGET    = core
TEMPLATE  = lib
DESTDIR   = ../../../modules/
QMAKE_CXXFLAGS_RELEASE += -O3 -mmmx -msse -msse2 -msse3 -mfpmath=sse -ftree-vectorize -ffast-math
#-ftree-vectorizer-verbose=2 -DPROFILER_ENABLED
QMAKE_CXXFLAGS_RELEASE -= -O2
INCLUDEPATH += ../../../sdk/include
DEFINES += CORE_LIBRARY
SOURCES += \
    CoreModule.cpp
HEADERS +=
