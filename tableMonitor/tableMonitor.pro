TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

SOURCES += main.cpp \
    tableinteraction.cpp \
    checker.cpp \
    iotable.cpp \
    export.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    checker.h\
    tableinteraction.h \
    iotable.h \
    export.h


unix:!macx: LIBS += -L$$PWD/../build-checkLib-Desktop_Qt_5_7_0_GCC_64bit-Release/ -lcheckLib

INCLUDEPATH += $$PWD/../checkLib
DEPENDPATH += $$PWD/../checkLib
