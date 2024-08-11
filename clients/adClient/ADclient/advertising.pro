QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#SOURCES += src/ *.cpp

#HEADERS += inc/ *.h

#FORMS += ui/ *.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    photo.qrc

HEADERS += \
    inc/EClient.h \
    inc/add.h \
    inc/alter.h \
    inc/alter1.h \
    inc/dele.h \
    inc/log_in.h \
    inc/look.h \
    inc/mainwindow.h

SOURCES += \
    src/EClient.cpp \
    src/add.cpp \
    src/alter.cpp \
    src/alter1.cpp \
    src/dele.cpp \
    src/log_in.cpp \
    src/look.cpp \
    src/main.cpp \
    src/mainwindow.cpp

FORMS += \
    ui/add.ui \
    ui/alter.ui \
    ui/alter1.ui \
    ui/dele.ui \
    ui/log_in.ui \
    ui/look.ui \
    ui/mainwindow.ui

DISTFILES += \
    image.rc

RC_FILE=image.rc
