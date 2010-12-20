#-------------------------------------------------
#
# Project created by QtCreator 2010-12-01T01:02:16
#
#-------------------------------------------------

QT       -= core gui
TARGET = HammerEngine
DESTDIR = ../bin/
CONFIG += console
CONFIG   -= app_bundle
TEMPLATE = app
QMAKE_CXXFLAGS_RELEASE += -O3 -mmmx -msse -msse2 -msse3 -mfpmath=sse -ftree-vectorize -ffast-math
#-ftree-vectorizer-verbose=2 -DPROFILER_ENABLED
QMAKE_CXXFLAGS_RELEASE -= -O2

INCLUDEPATH += ../depends/falcon/include \
               ../depends/SDL-1.3.0/include \
               ../depends/OpenGL/include \
               ../depends/ThreadingBuildingBlocks/include

LIBS += -L../depends/falcon/lib/ -lfalcon_engine.dll \
        -L../depends/SDL-1.3.0/lib -lmingw32 -lSDLmain -lSDL -lopengl32 \
        ../bin/tbb.dll

SOURCES += main.cpp \
    Script.cpp \
    Graphics.cpp \
    Info.cpp \
    Logger.cpp \
    Profiler.cpp \
    ChunkedMemoryPool.cpp \
    Renderer.cpp \
    logic.cpp \
    Messenger.cpp \
    Vector.cpp \
    PipelineProcessor.cpp

HEADERS += \
    Renderer.h \
    Graphics.h \
    Info.h \
    Logger.h \
    Profiler.h \
    ChunkedMemoryPool.h \
    Renderer.h \
    Messenger.h \
    Vector.h \
    Pooled.h \
    PipelineProcessor.h
