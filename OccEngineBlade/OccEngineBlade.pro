QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    jsonreader.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    jsonreader.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

CASROOT = "D:\\Programs\\OpenCASCADE-7.7.0-vc14-64\\opencascade-7.7.0"
#CASROOT = D:/OpenCASCADE7.4.0/opencascade-7.4.0

INCLUDEPATH += $${CASROOT}/inc #Подключение *.h файлов библиотеки Open Cascade
LIBS += -L$${CASROOT}/win64/vc14/lib/ #Подключение пути до статических библиотек *.lib Open Cascade


#
#LIBS +=         \
#    -lTKernel   \
#    -lTKMath    \
#    -lTKG3d     \
#    -lTKBRep    \
#    -lTKGeomBase\
#    -lTKGeomAlgo\
#    -lTKTopAlgo \
#    -lTKPrim    \
#    -lTKBO      \
#    -lTKBool    \
#    -lTKOffset  \
#    -lTKService \
#    -lTKV3d     \
#    -lTKOpenGl  \
#    -lTKFillet  \
#    -lTKXSBase  \
#    -lTKG2d     \
#    -lTKG3d     \
#    -lTKTopAlgo \
#    -lTKGeomBase\
#    -lTKSTEP209 \
#    -lTKSTEPAttr\
#    -lTKSTEPBase\
#    -lTKSTep    \
#    -lTKXmlXCAF \
#    -lTKXCAF    \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
