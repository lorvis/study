TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    player.cpp \
    map.cpp \
    view.cpp

LIBS += -LC:\SFML-2.3.2\lib\

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += C:\SFML-2.3.2\include\
DEPENDPATH += C:\SFML-2.3.2\include\

HEADERS += \
    player.h \
    map.h \
    view.h
