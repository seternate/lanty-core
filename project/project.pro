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
CONFIG += object_parallel_to_source

QMAKE_CXXFLAGS += --coverage
LIBS += -lgcov

INCLUDEPATH += $$PWD/include

SOURCES += \
    $$PWD/source/game/Game.cpp \
    $$PWD/source/game/Gamelist.cpp \
    $$PWD/source/game/GamelistFactory.cpp \
    $$PWD/source/helper/GameHelper.cpp \
    $$PWD/source/serializer/Serializable.cpp \
    $$PWD/source/system/FileExtension.cpp \
    $$PWD/source/system/QDirAdapter.cpp \
    $$PWD/source/system/QPixmapAdapter.cpp \
    $$PWD/source/user/User.cpp \
    $$PWD/source/user/Userlist.cpp \
    $$PWD/source/yaml/YamlNode.cpp \


HEADERS += \
    $$PWD/include/core/ltycore_global.hpp \
    $$PWD/include/core/version.hpp \
    $$PWD/include/game/Game.hpp \
    $$PWD/include/game/Gamelist.hpp \
    $$PWD/include/game/GamelistFactory.hpp \
    $$PWD/include/game/GameVersionSource.hpp \
    $$PWD/include/helper/GameHelper.hpp \
    $$PWD/include/serializer/Serializable.hpp \
    $$PWD/include/system/FileExtension.hpp \
    $$PWD/include/system/QDirAdapter.hpp \
    $$PWD/include/system/QPixmapAdapter.hpp \
    $$PWD/include/user/User.hpp \
    $$PWD/include/user/Userlist.hpp \
    $$PWD/include/yaml/YamlNode.hpp

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
