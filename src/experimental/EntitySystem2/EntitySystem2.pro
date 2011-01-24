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
QMAKE_CXXFLAGS_RELEASE += -O3 -mmmx -msse -msse2 -mfpmath=sse -ftree-vectorize -ffast-math -DPERFORM_PREFETCH -DNDEBUG
QMAKE_CXXFLAGS_DEBUG += -O0 -mmmx -msse

INCLUDEPATH += ../HammerEngine/src/depends/ThreadingBuildingBlocks/include
LIBS += ../EntitySystem2-build-desktop/release/tbb.dll

SOURCES += main.cpp \
    Position.cpp \
    Movement.cpp \
    HammerEntitySystem.cpp \
    Observed.cpp \
    Collidable.cpp \
    HammerEventDispatcher.cpp

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
    AlignedMemoryPool.h \
    BlockMemoryPoolImpl.h \
    UnalignedMemoryPool.h \
    Collidable.h \
    Null.h \
    SimdMacros.h \
    ReadOnlyEntitySystem.h \
    EntityState.h \
    EventDispatcher.h \
    Event.h \
    Attribute.h \
    HammerEventDispatcher.h
