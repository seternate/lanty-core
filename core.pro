QT += core gui

TEMPLATE = lib
DEFINES += LTYCORE_LIBRARY

CONFIG += c++14

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += \
    $$PWD/src/include

SOURCES += \
    $$PWD/src/game/game.cpp \
    $$PWD/src/game/gamelist.cpp \
    $$PWD/src/game/version.cpp \
    $$PWD/src/setting/setting.cpp
	
HEADERS += \
    $$PWD/src/include/ltycore.h \
    $$PWD/src/include/game.h \
    $$PWD/src/include/gamelist.h \
    $$PWD/src/include/version.h \
    $$PWD/src/include/setting.h

TRANSLATIONS += \
    $$PWD/resource/translation/core_de_DE.ts

RESOURCES += \
    $$PWD/resource/core.qrc \
    $$PWD/resource/style.qrc

RC_FILE += \
    $$PWD/resource/core.rc

CONFIG(debug, debug|release) {
    win32 {
        LIBS += -L$$PWD/artifact/x86_64 -llibyaml-cpp
        INCLUDEPATH += $$PWD/library/yaml-cpp/include
        DEPENDPATH += $$PWD/library/yaml-cpp/include
    }
}

CONFIG(release, debug|release) {
    win32 {
        LIBS += -L$$PWD/artifact/x86_64 -llibyaml-cpp
        INCLUDEPATH += $$PWD/library/yaml-cpp/include
        DEPENDPATH += $$PWD/library/yaml-cpp/include
    }
}

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

