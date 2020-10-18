QT += core gui

TEMPLATE = lib
DEFINES += LTYCORE_LIBRARY

CONFIG += c++14

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += \
    $$PWD/src/include

SOURCES += \
    $$PWD/src/game/Game.cpp \
    $$PWD/src/game/GameList.cpp \
    $$PWD/src/game/GameVersion.cpp \
    $$PWD/src/setting/Setting.cpp
	
HEADERS += \
    $$PWD/src/include/ltycore.hpp \
    $$PWD/src/core/ltycore_global.hpp \
    $$PWD/src/game/Game.hpp \
    $$PWD/src/game/GameList.hpp \
    $$PWD/src/game/GameVersion.hpp \
    $$PWD/src/setting/Setting.hpp

TRANSLATIONS += \
    $$PWD/resource/translation/core_de_DE.ts

RESOURCES += \
    $$PWD/resource/core.qrc \
    $$PWD/resource/style.qrc

RC_FILE += \
    $$PWD/resource/core.rc

CONFIG(debug, debug|release) {
    INCLUDEPATH += $$PWD/library/yaml-cpp/include
    DEPENDPATH += $$PWD/library/yaml-cpp/include

    win32 {
        LIBS += -L$$PWD/artifact/x86_64 -llibyaml-cpp 
    }
}

CONFIG(release, debug|release) {
    INCLUDEPATH += $$PWD/library/yaml-cpp/include
    DEPENDPATH += $$PWD/library/yaml-cpp/include
    
    win32 {
        LIBS += -L$$PWD/artifact/x86_64 -llibyaml-cpp
    }
}

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

