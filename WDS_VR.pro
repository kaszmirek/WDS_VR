QT       += core gui
QT       += serialport
QT       += opengl
QT       += quickwidgets
QT += 3dcore 3drender 3dinput 3dquick qml quick 3dquickextras serialport

QML_IMPORT_NAME = sensor.backend
QML_IMPORT_MAJOR_VERSION = 1

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    comunication.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    comunication.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    AdsEffect.qml \
    AdsMaterial.qml \
    Flame.qml \
    GroundPlane.qml \
    ShadowMapFrameGraph.qml \
    ShadowMapLight.qml \
    Stick.qml \
    Torch.qml \
    Toyplane.qml \
    Trefoil.qml \
    fshader.glsl \
    main.qml \
    vshader.glsl

RESOURCES += \
    E:/QT/Examples/Qt-5.15.2/qt3d/exampleresources/obj.qrc \
    shadow-map-qml.qrc
