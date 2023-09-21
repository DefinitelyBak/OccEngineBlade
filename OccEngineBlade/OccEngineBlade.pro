QT       += widgets core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    builderaisshape.cpp \
    jsonreader.cpp \
    main.cpp \
    occQt.cpp \
    occView.cpp

HEADERS += \
    builderaisshape.h \
    jsonreader.h \
    occQt.h \
    occView.h

FORMS += \
    occQt.ui

RESOURCES += \
    occqt.qrc

CASROOT = "D:\\Programs\\OpenCASCADE-7.7.0-vc14-64\\opencascade-7.7.0"

INCLUDEPATH += $${CASROOT}/inc        #Подключение *.h файлов библиотеки Open Cascade
LIBS += -L$${CASROOT}/win64/vc14/lib/ #Подключение пути до статических библиотек *.lib Open Cascade



LIBS +=         \
    -lTKernel   \
    -lTKMath    \
    -lTKG3d     \
    -lTKBRep    \
    -lTKGeomBase\
    -lTKGeomAlgo\
    -lTKTopAlgo \
    -lTKPrim    \
    -lTKBO      \
    -lTKBool    \
    -lTKOffset  \
    -lTKService \
    -lTKV3d     \
    -lTKOpenGl  \
    -lTKFillet  \
    -lTKXSBase  \
    -lTKG2d     \
    -lTKG3d     \
    -lTKTopAlgo \
    -lTKGeomBase\
    -lTKSTEP209 \
    -lTKSTEPAttr\
    -lTKSTEPBase\
    -lTKSTep    \
    -lTKXmlXCAF \
    -lTKXCAF    \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
