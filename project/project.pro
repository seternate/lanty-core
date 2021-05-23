# Copyright <2020> <Levin Jeck>

# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
# documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

QT += core gui network

TEMPLATE = lib
VERSION = 0.1.0
DEFINES += LTYCORE_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++17
CONFIG += skip_target_version_ext
# CONFIG += object_parallel_to_source

QMAKE_CXXFLAGS += --coverage
QMAKE_LFLAGS += --coverage
LIBS += -lgcov

INCLUDEPATH += $$PWD/include

SOURCES += \
    $$PWD/source/core/FileExtension.cpp \
    $$PWD/source/game/Game.cpp \
    $$PWD/source/game/GameClient.cpp \
    $$PWD/source/game/GameClientLoader.cpp \
    $$PWD/source/game/GameImage.cpp \
    $$PWD/source/game/GameLoader.cpp \
    $$PWD/source/game/GameServer.cpp \
    $$PWD/source/game/GameServerLoader.cpp \
    $$PWD/source/game/GameVersion.cpp \
    $$PWD/source/game/GameVersionLoader.cpp \
    $$PWD/source/game/QGame.cpp \
    $$PWD/source/game/QGamelist.cpp \
    $$PWD/source/user/User.cpp

HEADERS += \
    $$PWD/include/core/FileExtension.hpp \
    $$PWD/include/core/ltycore_global.hpp \
    $$PWD/include/core/Serializable.hpp \
    $$PWD/include/core/version.hpp \
    $$PWD/include/core/YAMLLoadable.hpp \
    $$PWD/include/game/Game.hpp \
    $$PWD/include/game/GameClient.hpp \
    $$PWD/include/game/GameClientLoader.hpp \
    $$PWD/include/game/GameImage.hpp \
    $$PWD/include/game/GameLoader.hpp \
    $$PWD/include/game/GameServer.hpp \
    $$PWD/include/game/GameServerLoader.hpp \
    $$PWD/include/game/GameVersion.hpp \
    $$PWD/include/game/GameVersionLoader.hpp \
    $$PWD/include/game/QGame.hpp \
    $$PWD/include/game/QGamelist.hpp \
    $$PWD/include/user/User.hpp

TRANSLATIONS += $$PWD/../resource/translation/core_de_DE.ts

RESOURCES += \
    $$PWD/../resource/core.qrc \
    $$PWD/../resource/style.qrc

win32 {
    RC_ICONS = $$PWD/../resource/image/icon.ico
    QMAKE_TARGET_DESCRIPTION = "Core library for the Lanty suite applications."
    QMAKE_TARGET_COPYRIGHT = "MIT <2021> <Levin Jeck>"
}

win32: DESTDIR += $$PWD/../artifact/x86_64/windows
linux: DESTDIR += $$PWD/../artifact/x86_64/linux

INCLUDEPATH += \
    $$PWD/../library/yaml-cpp/include \
    $$PWD/../library/nlohmann-json/single_include

DEPENDPATH += $$PWD/../library/yaml-cpp/include

LIBS += -L$$DESTDIR -lyaml-cpp

CONFIG(debug, debug|release) {
    TARGET = ltycored
}

CONFIG(release, debug|release) {
    TARGET = ltycore
}
