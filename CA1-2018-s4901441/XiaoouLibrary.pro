
TEMPLATE = app
TARGET = XiaoouLibrary
QT += core gui widgets opengl \
          widgets

CONFIG += c++11
OBJECTS_DIR = obj/

HEADERS += \
    Mainwindow.h \
    GLWidget.h \
    ParticleTypes.h \
    Particles.h \
    ParticleFactory.h \
    Emitter.h \
    sphere.h \
    cube.h \
    BoudingSphere.h \
    IntersectingData.h \
    AABB.h \
    CollidePlane.h \
    Collider.h \
    plane.h \
    Cloth_Particle.h \
    Cloth_object.h


SOURCES += \
    main.cpp \
    Mainwindow.cpp \
    GLWidget.cpp \
    Particles.cpp \
    ParticleFactory.cpp \
    Emitter.cpp \
    sphere.cpp \
    cube.cpp \
    BoudingSphere.cpp \
    IntersectingData.cpp \
    AABB.cpp \
    CollidePlane.cpp \
    Collider.cpp \
    plane.cpp \
    CollisionResponse.cpp \
    Friction_Impulse_Calc.cpp \
    Penetration_Remove.cpp \
    Cloth_Particle.cpp \
    Cloth_object.cpp


FORMS += \
    MainWindow.ui

OTHER_FILES += shaders/*.glsl




DISTFILES += \
    shaders/PhongFragment.glsl \
    shaders/PhongVertex.glsl \
    shaders/diffuseFrag.glsl \
    shaders/diffuseVertex.glsl



NGLPATH=$$(NGLDIR)
isEmpty(NGLPATH){ # note brace must be here
  message("including $HOME/NGL")
  include($(HOME)/NGL/UseNGL.pri)
}
