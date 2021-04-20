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

QT += core gui testlib network

TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG += c++17

INCLUDEPATH += \
    $$PWD/../library/googletest/googletest \
    $$PWD/../library/googletest/googletest/include \
    $$PWD/../library/googletest/googlemock \
    $$PWD/../library/googletest/googlemock/include \
    $$PWD/../project/include \
    $$PWD/include

HEADERS += \
    $$PWD/include/core/YAMLLoadableTest.hpp \
    $$PWD/include/game/GameClientLoaderTest.hpp \
    $$PWD/include/game/GameLoaderTest.hpp \
    $$PWD/include/game/GameServerLoaderTest.hpp \
    $$PWD/include/game/GameVersionLoaderTest.hpp \
    $$PWD/include/helper/QStringPrintHelper.hpp

SOURCES += \
    $$PWD/../library/googletest/googletest/src/gtest-all.cc \
    $$PWD/../library/googletest/googlemock/src/gmock-all.cc \
    $$PWD/source/core/main.cpp \
    $$PWD/source/core/YAMLLoadableTest.cpp \
    $$PWD/source/game/GameClientLoaderTest.cpp \
    $$PWD/source/game/GameClientTest.cpp \
    $$PWD/source/game/GameLoaderTest.cpp \
    $$PWD/source/game/GameServerLoaderTest.cpp \
    $$PWD/source/game/GameServerTest.cpp \
    $$PWD/source/game/GameTest.cpp \
    $$PWD/source/game/GameVersionLoaderTest.cpp \
    $$PWD/source/game/GameVersionTest.cpp \
    $$PWD/source/game/QGameTest.cpp \
    $$PWD/source/user/UserTest.cpp

INCLUDEPATH += \
    $$PWD/../library/yaml-cpp/include \
    $$PWD/../library/nlohmann-json/single_include

DEPENDPATH += $$PWD/../library/yaml-cpp/include
win32: LIBS += -L$$PWD/../artifact/x86_64/windows -lyaml-cpp
linux: LIBS += -L$$PWD/../artifact/x86_64/linux -lyaml-cpp

CONFIG(debug, debug|release) {
    TARGET = ltycored-test
    win32: LIBS += -L$$PWD/../artifact/x86_64/windows -lltycored
    linux: LIBS += -L$$PWD/../artifact/x86_64/linux -lltycored
}

CONFIG(release, debug|release) {
    TARGET = ltycore-test
    win32: LIBS += -L$$PWD/../artifact/x86_64/windows -lltycore
    linux: LIBS += -L$$PWD/../artifact/x86_64/linux -lltycore
}

win32: DESTDIR += $$PWD/../artifact/x86_64/windows
linux: DESTDIR += $$PWD/../artifact/x86_64/linux
