TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

SOURCES += main.cpp \
    tableinteraction.cpp \
    checker.cpp \
    iotable.cpp

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
    iotable.h


unix:!macx: LIBS += -L$$PWD/../build-checkLib-Desktop_Qt_5_7_0_GCC_64bit-Release/ -lcheckLib
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-checkLib-Desktop_Qt_5_7_0_MinGW_32bit-Debug/release/ -lcheckLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-checkLib-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug/ -lcheckLib


INCLUDEPATH += $$PWD/../checkLib
DEPENDPATH += $$PWD/../checkLib
