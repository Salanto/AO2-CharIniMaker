QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

VERSION = 0.2.0

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Needed so that Windows doesn't do `release/` and `debug/` subfolders
# in the output directory.
CONFIG -= \
        copy_dir_files \
        debug_and_release \
        debug_and_release_target

DESTDIR = $$PWD/bin

#Grab all source files, including subfolders.
SOURCES += $$files($$PWD/src/*.cpp, true)

#Grab all headers, including subfolders.
HEADERS += $$files($$PWD/include/*.h, true)
INCLUDEPATH += $$PWD/include/

FORMS += \
    ressources/ui/ao2charmaker.ui
