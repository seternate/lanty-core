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

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <QSignalSpy>
#include <QString>
#include <string>
#include <system/QPixmapAdapter.hpp>
#include <yaml/YamlNode.hpp>

#include "game/Game.hpp"
#include "helper/QStringPrintHelper.hpp"
#include "mock/MockYamlNode.hpp"

using ::testing::A;
using ::testing::NiceMock;
using ::testing::Return;

TEST(GameTest, EqualOperator)
{
    lanty::Game gameTest;
    lanty::Game game;
    ASSERT_EQ(game, gameTest);

    gameTest.setName("Call of Duty 2");
    ASSERT_NE(game, gameTest);
    game.setName("Call of Duty 2");
    ASSERT_EQ(game, gameTest);

    gameTest.setArchiveFileName("cod2.zip");
    ASSERT_NE(game, gameTest);
    game.setArchiveFileName("cod2.zip");
    ASSERT_EQ(game, gameTest);

    gameTest.setClientExecutableRelativeFilePath("bin/iwp2mp.exe");
    ASSERT_NE(game, gameTest);
    game.setClientExecutableRelativeFilePath("bin/iwp2mp.exe");
    ASSERT_EQ(game, gameTest);

    gameTest.setClientArgument("+map crossfire");
    ASSERT_NE(game, gameTest);
    game.setClientArgument("+map crossfire");
    ASSERT_EQ(game, gameTest);

    gameTest.setClientConnectArgument("?");
    ASSERT_NE(game, gameTest);
    game.setClientConnectArgument("?");
    ASSERT_EQ(game, gameTest);

    gameTest.setServerExecutableRelativeFilePath("bin/iwp2mp_server.exe");
    ASSERT_NE(game, gameTest);
    game.setServerExecutableRelativeFilePath("bin/iwp2mp_server.exe");
    ASSERT_EQ(game, gameTest);

    gameTest.setServerArgument("+server 1");
    ASSERT_NE(game, gameTest);
    game.setServerArgument("+server 1");
    ASSERT_EQ(game, gameTest);

    gameTest.setVersion("1.0.0.0");
    ASSERT_NE(game, gameTest);
    game.setVersion("1.0.0.0");
    ASSERT_EQ(game, gameTest);

    gameTest.setVersionSource(lanty::GameVersionSource::EXECUTABLE);
    ASSERT_NE(game, gameTest);
    game.setVersionSource(lanty::GameVersionSource::EXECUTABLE);
    ASSERT_EQ(game, gameTest);

    gameTest.setVersionRelativeFilePath("version.conf");
    ASSERT_NE(game, gameTest);
    game.setVersionRelativeFilePath("version.conf");
    ASSERT_EQ(game, gameTest);

    gameTest.setVersionFileQuery("version=");
    ASSERT_NE(game, gameTest);
    game.setVersionFileQuery("version=");
    ASSERT_EQ(game, gameTest);
}

TEST(GameTest, GetterName)
{
    lanty::Game game;
    QString name("Call of Duty 2");

    game.setName(name);

    ASSERT_EQ(game.getName(), name);
}

TEST(GameTest, GetterArchiveFile)
{
    lanty::Game game;
    QString archiveFilePath("cod2.zip");

    game.setArchiveFileName(archiveFilePath);

    ASSERT_EQ(game.getArchiveFileName(), archiveFilePath);
}

TEST(GameTest, GetterClientFile)
{
    lanty::Game game;
    QString clientFilePath("bin/iw2mp.exe");

    game.setClientExecutableRelativeFilePath(clientFilePath);

    ASSERT_EQ(game.getClientExecutableRelativeFilePath(), clientFilePath);
}

TEST(GameTest, GetterClientArgument)
{
    lanty::Game game;
    QString clientArgument("+map crossfire");

    game.setClientArgument(clientArgument);

    ASSERT_EQ(game.getClientArgument(), clientArgument);
}

TEST(GameTest, GetterClientConnectArgument)
{
    lanty::Game game;
    QString clientConnectArgument("+connect ?");

    game.setClientConnectArgument(clientConnectArgument);

    ASSERT_EQ(game.getClientConnectArgument(), clientConnectArgument);
}

TEST(GameTest, GetterServerExecutable)
{
    lanty::Game game;
    QString serverExecutable("bin/iwp2mp_server.exe");

    game.setServerExecutableRelativeFilePath(serverExecutable);

    ASSERT_EQ(game.getServerExecutableRelativeFilePath(), serverExecutable);
}

TEST(GameTest, GetterServerArgument)
{
    lanty::Game game;
    QString serverArgument("+server 1");

    game.setServerArgument(serverArgument);

    ASSERT_EQ(game.getServerArgument(), serverArgument);
}

TEST(GameTest, GetterVersion)
{
    lanty::Game game;
    QString version("1.0.0.0");

    game.setVersion(version);

    ASSERT_EQ(game.getVersion(), version);
}

TEST(GameTest, GetterVersionSource)
{
    lanty::Game game;

    game.setVersionSource(lanty::GameVersionSource::EXECUTABLE);

    ASSERT_EQ(game.getVersionSource(), lanty::GameVersionSource::EXECUTABLE);
}

TEST(GameTest, GetterVersionFilePath)
{
    lanty::Game game;
    QString versionFilePath("version.conf");

    game.setVersionRelativeFilePath(versionFilePath);

    ASSERT_EQ(game.getVersionRelativeFilePath(), versionFilePath);
}

TEST(GameTest, GetterVersionFileQuery)
{
    lanty::Game game;
    QString versionFileQuery("version=");

    game.setVersionFileQuery(versionFileQuery);

    ASSERT_EQ(game.getVersionFileQuery(), versionFileQuery);
}

TEST(GameTest, GetterCoverImage)
{
    lanty::Game game;
    QSize size(100, 100);
    lanty::QPixmapAdapter pixmap(size);

    game.setCoverImage(pixmap);

    ASSERT_FALSE(game.getCoverImage().isNull());
    ASSERT_EQ(game.getCoverImage().size(), size);
}

TEST(GameTest, GetterIconImage)
{
    lanty::Game game;
    QSize size(100, 100);
    lanty::QPixmapAdapter pixmap(size);

    game.setIconImage(pixmap);

    ASSERT_FALSE(game.getIconImage().isNull());
    ASSERT_EQ(game.getIconImage().size(), size);
}


TEST(GameTest, isVersionEmptyStringAndSourceNONE)
{
    lanty::Game game;
    QString version("");

    game.setVersion(version);
    game.setVersionSource(lanty::GameVersionSource::NONE);

    ASSERT_FALSE(game.isVersion());
}

TEST(GameTest, isVersionAnyStringAndSourceNONE)
{
    lanty::Game game;
    QString version("a23asfsg3asda");

    game.setVersion(version);
    game.setVersionSource(lanty::GameVersionSource::NONE);

    ASSERT_FALSE(game.isVersion());
}

TEST(GameTest, isVersionEmptyStringAndSourceNotNONE)
{
    lanty::Game game;
    QString version("");

    game.setVersion(version);

    game.setVersionSource(lanty::GameVersionSource::EXECUTABLE);
    ASSERT_FALSE(game.isVersion());

    game.setVersionSource(lanty::GameVersionSource::FILE);
    ASSERT_FALSE(game.isVersion());
}

TEST(GameTest, isVersionAnyStringAndSourceNotNONE)
{
    lanty::Game game;
    QString version("a23asfsg3asda");

    game.setVersion(version);

    game.setVersionSource(lanty::GameVersionSource::EXECUTABLE);
    ASSERT_TRUE(game.isVersion());

    game.setVersionSource(lanty::GameVersionSource::FILE);
    ASSERT_TRUE(game.isVersion());
}


TEST(GameTest, canJoinServerWithoutArgument)
{
    lanty::Game game;
    QString connect("");

    game.setClientConnectArgument(connect);

    ASSERT_FALSE(game.canJoinServerWithCLI());
}

TEST(GameTest, canJoinServerWithArgument)
{
    lanty::Game game;
    QString connect("+connect ?");

    game.setClientConnectArgument(connect);

    ASSERT_TRUE(game.canJoinServerWithCLI());
}


TEST(GameTest, canOpenDedicatedServerWithoutServerAndWithoutArgumentExecutable)
{
    lanty::Game game;
    QString serverExecutable("");
    QString serverArgument("");

    game.setServerExecutableRelativeFilePath(serverExecutable);
    game.setServerArgument(serverArgument);

    ASSERT_FALSE(game.canOpenDedicatedServer());
}

TEST(GameTest, canOpenDedicatedServerWithoutServerAndWithArgumentExecutable)
{
    lanty::Game game;
    QString serverExecutable("");
    QString serverArgument("asdtzjsd");

    game.setServerExecutableRelativeFilePath(serverExecutable);
    game.setServerArgument(serverArgument);

    ASSERT_FALSE(game.canOpenDedicatedServer());
}

TEST(GameTest, canOpenDedicatedServerWithServerAndWithoutArgumentExecutable)
{
    lanty::Game game;
    QString serverExecutable("asdasd.exe");
    QString serverArgument("");

    game.setServerExecutableRelativeFilePath(serverExecutable);
    game.setServerArgument(serverArgument);

    ASSERT_TRUE(game.canOpenDedicatedServer());
}

TEST(GameTest, canOpenDedicatedServerWithServerAndWithArgumentExecutable)
{
    lanty::Game game;
    QString serverExecutable("asdasd.exe");
    QString serverArgument("asdibsdg");

    game.setServerExecutableRelativeFilePath(serverExecutable);
    game.setServerArgument(serverArgument);

    ASSERT_TRUE(game.canOpenDedicatedServer());
}


TEST(GameTest, canOpenServerWithoutServerAndWithoutArgumentExecutable)
{
    lanty::Game game;
    QString serverExecutable("");
    QString serverArgument("");

    game.setServerExecutableRelativeFilePath(serverExecutable);
    game.setServerArgument(serverArgument);

    ASSERT_FALSE(game.canOpenServer());
}

TEST(GameTest, canOpenServerWithServerAndWithoutArgumentExecutable)
{
    lanty::Game game;
    QString serverExecutable("asd");
    QString serverArgument("");

    game.setServerExecutableRelativeFilePath(serverExecutable);
    game.setServerArgument(serverArgument);

    ASSERT_TRUE(game.canOpenServer());
}

TEST(GameTest, canOpenServerWithoutServerAndWithArgumentExecutable)
{
    lanty::Game game;
    QString serverExecutable("");
    QString serverArgument("asdGHhN");

    game.setServerExecutableRelativeFilePath(serverExecutable);
    game.setServerArgument(serverArgument);

    ASSERT_TRUE(game.canOpenServer());
}

TEST(GameTest, canOpenServerWithServerAndWithArgumentExecutable)
{
    lanty::Game game;
    QString serverExecutable("asdaasd.exe");
    QString serverArgument("asdpsjünb");

    game.setServerExecutableRelativeFilePath(serverExecutable);
    game.setServerArgument(serverArgument);

    ASSERT_TRUE(game.canOpenServer());
}


TEST(GameTest, NameChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(nameChanged(QString)));
    QString name("Call of Duty 2");

    game.setName(name);

    ASSERT_EQ(1, spy.count());
}

TEST(GameTest, ArchiveFileChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(archiveFileNameChanged(QString)));
    QString archiveFilePath("cod2.zip");

    game.setArchiveFileName(archiveFilePath);

    ASSERT_EQ(1, spy.count());
}

TEST(GameTest, clientFileChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(clientExecutableChanged(QString)));
    QString clientFilePath("bin/iwp2mp.exe");

    game.setClientExecutableRelativeFilePath(clientFilePath);

    ASSERT_EQ(1, spy.count());
}

TEST(GameTest, ClientArgumentChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(clientArgumentChanged(QString)));
    QString clientArgument("+map 123eh");

    game.setClientArgument(clientArgument);

    ASSERT_EQ(1, spy.count());
}

TEST(GameTest, ClientConnectArgumentChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(clientConnectArgumentChanged(QString)));
    QString clientConnectArgument("+connect ?");

    game.setClientConnectArgument(clientConnectArgument);

    ASSERT_EQ(1, spy.count());
}

TEST(GameTest, ServerExecutableChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(serverExecutableChanged(QString)));
    QString serverExecutable("iahsgn.exe");

    game.setServerExecutableRelativeFilePath(serverExecutable);

    ASSERT_EQ(1, spy.count());
}

TEST(GameTest, ServerArgumentChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(serverArgumentChanged(QString)));
    QString serverArgument("+dedicated 1");

    game.setServerArgument(serverArgument);

    ASSERT_EQ(1, spy.count());
}

TEST(GameTest, VersionChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(versionChanged(QString)));
    QString version("1.2.0.3");

    game.setVersion(version);

    ASSERT_EQ(1, spy.count());
}

TEST(GameTest, VersionSourceChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(versionSourceChanged(GameVersionSource)));

    game.setVersionSource(lanty::GameVersionSource::EXECUTABLE);

    ASSERT_EQ(1, spy.count());
}

TEST(GameTest, VersionFileChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(versionFileChanged(QString)));
    QString versionFilePath("version.conf");

    game.setVersionRelativeFilePath(versionFilePath);

    ASSERT_EQ(1, spy.count());
}

TEST(GameTest, VersionFileQueryChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(versionFileQueryChanged(QString)));
    QString versionFileQuery("version=");

    game.setVersionFileQuery(versionFileQuery);

    ASSERT_EQ(1, spy.count());
}

TEST(GameTest, CoverImageChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(coverImageChanged(lanty::QPixmapAdapter)));
    QSize size(100, 100);
    lanty::QPixmapAdapter pixmap(size);

    game.setCoverImage(pixmap);

    ASSERT_EQ(1, spy.count());
}

TEST(GameTest, IconImageChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(iconImageChanged(lanty::QPixmapAdapter)));
    QSize size(100, 100);
    lanty::QPixmapAdapter pixmap(size);

    game.setIconImage(pixmap);

    ASSERT_EQ(1, spy.count());
}

TEST(GameTest, SerializeJSON)
{
    lanty::Game game;
    nlohmann::json* json;

    QString jsonExpected("{\"game\":{\"archive\":\"test.zip\",\"client\":{\"executable\":\"test.exe\"},\"name\":\"test\"}}");

    game.setName("test");
    game.setArchiveFileName("test.zip");
    game.setClientExecutableRelativeFilePath("test.exe");

    json = game.toJSON();
    std::string s = json->dump();

    ASSERT_EQ(s, jsonExpected.toStdString());

    delete json;
}

TEST(GameTest, DeserializeJSON)
{
    QString name = "test";
    QString archive = "test.zip";
    QString clientExecutable = "test.exe";

    nlohmann::json json
        = "{\"game\":{\"archive\":\"test.zip\",\"client\":{\"executable\":\"test.exe\"},\"name\":\"test\"}}"_json;

    lanty::Game game;
    game.fromJSON(json);

    ASSERT_EQ(game.getName(), name);
    ASSERT_EQ(game.getArchiveFileName(), archive);
    ASSERT_EQ(game.getClientExecutableRelativeFilePath(), clientExecutable);
    ASSERT_TRUE(game.getClientArgument().isEmpty());
    ASSERT_TRUE(game.getClientConnectArgument().isEmpty());
    ASSERT_TRUE(game.getServerArgument().isEmpty());
    ASSERT_EQ(game.getServerExecutableRelativeFilePath(), game.getClientExecutableRelativeFilePath());
    ASSERT_TRUE(game.getVersion().isEmpty());
    ASSERT_TRUE(game.getVersionFileQuery().isEmpty());
    ASSERT_TRUE(game.getVersionRelativeFilePath().isEmpty());
}
