#-------------------------------------------------
#
# Project created by QtCreator 2011-01-11T23:05:56
#
#-------------------------------------------------


QT       -= core gui

TARGET = EntitySystem
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
QMAKE_CXXFLAGS_RELEASE += -std=gnu++0x -O3 -mmmx -msse -DPERFORM_PREFETCH -DNDEBUG
QMAKE_CXXFLAGS_DEBUG += -std=gnu++0x -O3 -mmmx -msse -DPERFORM_PREFETCH

SOURCES += main.cpp \
    Position.cpp \
    Movement.cpp \
    HammerEntitySystem.cpp \
    Observed.cpp

HEADERS += \
    Position.h \
    Trait.h \
    BehaviorBuilder.h \
    BehaviorFunctor.h \
    Entity.h \
    EntitySystem.h \
    TraitBuilder.h \
    TypeConstraints.h \
    Movement.h \
    HammerEntitySystem.h \
    Observed.h \
    MemoryPool.h \
    DebugTools.h \
    TemplateTools.h \
    AlignedMemoryPool.h
