/* Copyright <2020> <Levin Jeck>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef MOCK_MOCKGAME_HPP
#define MOCK_MOCKGAME_HPP

#include <gmock/gmock.h>

#include "game/Game.hpp"

class MockGame : public lanty::Game
{
public:
    MOCK_METHOD(QString, getName, (), (const, override));
    MOCK_METHOD(QString, getArchiveFileName, (), (const, override));
    MOCK_METHOD(QString, getClientExecutableRelativeFilePath, (), (const, override));
    MOCK_METHOD(QString, getClientArgument, (), (const, override));
    MOCK_METHOD(QString, getClientConnectArgument, (), (const, override));
    MOCK_METHOD(QString, getServerExecutableRelativeFilePath, (), (const, override));
    MOCK_METHOD(QString, getServerArgument, (), (const, override));
    MOCK_METHOD(QString, getVersion, (), (const, override));
    MOCK_METHOD(lanty::GameVersionSource, getVersionSource, (), (const, override));
    MOCK_METHOD(QString, getVersionRelativeFilePath, (), (const, override));
    MOCK_METHOD(QString, getVersionFileQuery, (), (const, override));
    MOCK_METHOD(lanty::QPixmapAdapter, getCoverImage, (), (const, override));
    MOCK_METHOD(lanty::QPixmapAdapter, getIconImage, (), (const, override));
    MOCK_METHOD(bool, isVersion, (), (const, override));
    MOCK_METHOD(bool, canJoinServerWithCLI, (), (const, override));
    MOCK_METHOD(bool, canOpenDedicatedServer, (), (const, override));
    MOCK_METHOD(bool, canOpenServer, (), (const, override));
    MOCK_METHOD(bool, load, (const lanty::YamlNode &yamlNode), (override));


public slots:
    MOCK_METHOD(void, setName, (const QString &name), (override));
    MOCK_METHOD(void, setArchiveFileName, (const QString &archiveAbsoluteFilePath), (override));
    MOCK_METHOD(void, setClientExecutableRelativeFilePath, (const QString &clientExecutableRelativeFilePath), (override));
    MOCK_METHOD(void, setClientArgument, (const QString &clientArgument), (override));
    MOCK_METHOD(void, setClientConnectArgument, (const QString &clientConnectArgument), (override));
    MOCK_METHOD(void, setServerExecutableRelativeFilePath, (const QString &serverExecutableRelativeFilePath), (override));
    MOCK_METHOD(void, setServerArgument, (const QString &serverArgument), (override));
    MOCK_METHOD(void, setVersion, (const QString &version), (override));
    MOCK_METHOD(void, setVersionSource, (const lanty::GameVersionSource &gameVersionSource), (override));
    MOCK_METHOD(void, setVersionRelativeFilePath, (const QString &versionRelativeFilePath), (override));
    MOCK_METHOD(void, setVersionFileQuery, (const QString &versionFileQuery), (override));
    MOCK_METHOD(void, setCoverImage, (const lanty::QPixmapAdapter &coverImage), (override));
    MOCK_METHOD(void, setIconImage, (const lanty::QPixmapAdapter &iconImage), (override));
};

#endif /* MOCK_MOCKGAME_HPP */
