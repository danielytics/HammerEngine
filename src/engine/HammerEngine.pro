#-------------------------------------------------
#
# Project created by QtCreator 2010-12-01T01:02:16
#
#-------------------------------------------------

QT       -= core gui
TARGET = HammerEngine
DESTDIR = ../../bin/
CONFIG += console
CONFIG   -= app_bundle
TEMPLATE = app
QMAKE_CXXFLAGS_RELEASE += -O3 -mmmx -msse -msse2 -msse3 -mfpmath=sse -ftree-vectorize -ffast-math
#-ftree-vectorizer-verbose=2 -DPROFILER_ENABLED
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_DEBUG += -mmmx -msse -msse2 -msse3 -mfpmath=sse

INCLUDEPATH += ../depends/falcon/include \
               ../depends/SDL-1.3.0/include \
               ../depends/OpenGL/include \
               ../depends/ThreadingBuildingBlocks/include \
               ../../sdk/include

LIBS += -L../depends/falcon/lib/ -lfalcon_engine.dll \
        -L../depends/SDL-1.3.0/lib -lmingw32 -lSDLmain -lSDL -lopengl32 \
        ../../bin/tbb.dll

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
    PipelineProcessor.cpp \
    EntitySystem/EntitySystem.cpp

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
    PipelineProcessor.h \
    EntitySystem.h \
    EntitySystem/Trait.h \
    EntitySystem/EntitySystem.h \
    ../../sdk/include/HammerEngine/EntitySystem/Trait.h \
    ../../sdk/include/HammerEngine/EntitySystem/EntitySystem.h \
    ../../sdk/include/HammerEngine/EntitySystem/Entity.h \
    ../../sdk/include/HammerEngine/Module.h \
    Resource/Resource.h \
    ../../sdk/include/HammerEngine/Types/Vector.h \
    ../../sdk/include/HammerEngine/Types/Texture.h \
    ../../sdk/include/HammerEngine/Types/Ray.h \
    ../../sdk/include/HammerEngine/Types/Polygon.h \
    ../../sdk/include/HammerEngine/Types/Polar3D.h \
    ../../sdk/include/HammerEngine/Types/Polar2D.h \
    ../../sdk/include/HammerEngine/Types/Plane.h \
    ../../sdk/include/HammerEngine/Types/Line.h \
    ../../sdk/include/HammerEngine/Types/Color4.h \
    ../../sdk/include/HammerEngine/Types/Color.h \
    ../../sdk/include/HammerEngine/Types/AABB.h \
    ../../sdk/include/HammerEngine/SIMD/Packed.h \
    ../../sdk/include/HammerEngine/SIMD/GenericVector.h \
    ../../sdk/include/HammerEngine/Types/Matrix4x4.h \
    ../../sdk/include/HammerEngine/Types/Matrix3x3.h \
    ../../sdk/include/HammerEngine/Types/Matrix2x2.h \
    ../../sdk/include/HammerEngine/Resources/Handle.h \
    ../../sdk/include/HammerEngine/Memory/StreamPool.h \
    ../../sdk/include/HammerEngine/EntitySystem/BehaviorFunctor.h
