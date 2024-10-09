QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminview.cpp \
    data.cpp \
    editpost.cpp \
    editrating.cpp \
    main.cpp \
    loginwindow.cpp \
    post.cpp \
    postview.cpp \
    registration.cpp \
    user.cpp

HEADERS += \
    adminview.h \
    data.h \
    editpost.h \
    editrating.h \
    loginwindow.h \
    post.h \
    postview.h \
    registration.h \
    user.h

FORMS += \
    adminview.ui \
    editpost.ui \
    loginwindow.ui \
    postview.ui \
    registration.ui \
    user.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
