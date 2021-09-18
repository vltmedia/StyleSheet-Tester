#-------------------------------------------------
#
# Project created by QtCreator 2018-05-07T20:18:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QStyleSheetTester
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# //////////////////////////////////////////////////////////////////////

# Copy Extra Files to the Directory this way
COPIES += styles_files
styles_files.files = $$files(./*.qss)
styles_files.path =  $$OUT_PWD/debug/
COPIES += styles_files_Release
styles_files_Release.files = $$files(./*.qss)
styles_files_Release.path =  $$OUT_PWD/release/
COPIES += palette_files
palette_files.files = $$files(./*.json)
palette_files.path =  $$OUT_PWD/debug/
COPIES += palette_files_Release
palette_files_Release.files = $$files(./*.json)
palette_files_Release.path =  $$OUT_PWD/release/

# //////////////////////////////////////////////////////////////////////

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui
