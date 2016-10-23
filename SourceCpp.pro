QT += core gui opengl

LIBS += -lglut

TARGET = SourceCpp
TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle

SOURCES += main.cpp \
    vtf.cpp

HEADERS += \
    vtf.h
