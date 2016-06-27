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
    effectlist.cpp \
    enemylist.cpp \
    sqlite3.cpp \
    sqlite.cpp

LIBS += -L $$PWD\libs\

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += $$PWD\include\
DEPENDPATH += $$PWD\include\

HEADERS += \
    map.h \
    view.h \
    projectile.h \
    npc.h \
    character.h \
    projectilelist.h \
    effect.h \
    effectlist.h \
    enemylist.h \
    sqlite3.h \
    include/Backup.h \
    include/Column.h \
    include/Database.h \
    include/Exception.h \
    include/SQLiteCpp.h \
    include/Statement.h \
    include/VariadicBind.h \
    include/SQLiteCpp/sqlite3.h \
    include/sqlite3.h \
    sqlite.hpp
