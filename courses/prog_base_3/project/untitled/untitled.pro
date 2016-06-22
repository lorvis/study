TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    map.cpp \
    view.cpp \
    npc.cpp \
    character.cpp \
    projectile.cpp \
    projectilelist.cpp \
    effect.cpp \
    effectlist.cpp

LIBS += -LC:\SFML-2.3.2\lib\

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += C:\SFML-2.3.2\include\
DEPENDPATH += C:\SFML-2.3.2\include\

HEADERS += \
    map.h \
    view.h \
    projectile.h \
    npc.h \
    character.h \
    projectilelist.h \
    effect.h \
    effectlist.h
