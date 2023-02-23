# ----------------------------------------------------------------
# SOFTWARE INTENDED FOR EDUCATIONAL PURPOSES.
# 
# AUTHORS: RENE DIAZ JR
# DATE: 01/23/2023
# ----------------------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR = ../bin

TEMPLATE = app

TARGET = NetworkWatcher

SOURCES += ../src/*.cpp \

HEADERS += ../src/*.h \

FORMS += ../src/ui/*.ui \

INCLUDEPATH += ../dependencies/activemq-cpp-library-3.9.5/src/main
               ../dependencies/apr-1.7.0 \

#LIBS += ../dependencies/activemq-cpp-library-3.9.5/src/main/cms/*.cpp \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
