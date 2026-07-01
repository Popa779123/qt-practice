QT += testlib core
QT -= gui

CONFIG += qt console warn_on testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    tst_integernumber.cpp \
    ../IntegerNumber.cpp

HEADERS += \
    ../IntegerNumber.h
