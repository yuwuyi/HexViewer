# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

# This is a reminder that you are using a generated .pro file.
# Remove it when you are finished editing this file.
message("You are running qmake on a generated .pro file. This may not work!")


TEMPLATE = app
TARGET = HexViewer
DESTDIR = ../Debug
QT += core gui qtmain opengl
CONFIG += debug console
DEFINES += QT_LARGEFILE_SUPPORT QT_OPENGL_LIB
INCLUDEPATH += ./GeneratedFiles \
    ./GeneratedFiles/Debug \
    .
LIBS += -lkernel32 \
    -luser32 \
    -lshell32 \
    -luuid \
    -lole32 \
    -ladvapi32 \
    -lws2_32 \
    -lgdi32 \
    -lcomdlg32 \
    -loleaut32 \
    -limm32 \
    -lwinmm \
    -lwinspool \
    -lws2_32 \
    -lole32 \
    -luser32 \
    -ladvapi32 \
    -lopengl32 \
    -lglu32
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(HexViewer.pri)