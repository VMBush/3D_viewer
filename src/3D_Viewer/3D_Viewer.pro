QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += SRCDIR=\\\"$$PWD/\\\"

SOURCES += \
    3rdparty/gif.cpp \
    c_code/parser.c \
    c_code/vectors.c \
    c_code/work_with_matrix.c \
    glview.cpp \
    main.cpp \
    mainwindow.cpp \
    modules/sceneModelling.cpp


HEADERS += \
    3rdparty/gif.h \
    c_code/cModules.h \
    c_code/vectors.h \
    glview.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

LIBS += -lglu32 -lopengl32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    options.conf \
    shaders/dot.frag \
    shaders/dot.geo.frag \
    shaders/dot.vert \
    shaders/dot/dot.frag \
    shaders/dot/dot.vert \
    shaders/dot/dot_round.geo.frag \
    shaders/dot/dot_square.geo.frag \
    shaders/edge.frag \
    shaders/edge.geo.vert \
    shaders/edge.vert \
    shaders/edge/edge.frag \
    shaders/edge/edge.vert \
    shaders/edge/edge_dashed.geo.vert \
    shaders/edge_dashed.geo.vert \
    shaders/vertex/vertex.frag \
    shaders/vertex/vertex.vert \
    shaders/vertex/vertex_round.geo.frag \
    shaders/vertex/vertex_square.geo.frag

RESOURCES += \
    resources.qrc
