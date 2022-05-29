QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    canvas.cpp \
    circle.cpp \
    figure.cpp \
    free_drawing.cpp \
    image.cpp \
    line.cpp \
    main.cpp \
    main_window.cpp \
    panel.cpp \
    rectangle.cpp

HEADERS += \
    canvas.h \
    circle.h \
    figure.h \
    free_drawing.h \
    image.h \
    line.h \
    main_window.h \
    panel.h \
    rectangle.h \
    type_of_figure.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
