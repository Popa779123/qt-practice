QT       += core gui widgets

TARGET = ChessApp
TEMPLATE = app

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    piece.cpp

HEADERS += \
    mainwindow.h \
    piece.h

FORMS += \
    chess.ui

RESOURCES += \
    resources.qrc
