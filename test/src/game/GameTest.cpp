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

#include <gtest/gtest.h>
#include <QSignalSpy>
#include <QString>

#include "game/Game.hpp"
#include "helper/QStringPrintHelper.hpp"

TEST(GameTest, EqualOperator)
{
    lanty::Game gameTest;
    lanty::Game game;
    ASSERT_EQ(game, gameTest);

    gameTest.setName("TEST");
    ASSERT_NE(game, gameTest);
    game.setName("TEST");
    ASSERT_EQ(game, gameTest);

    gameTest.setArchiveAbsoluteFilePath("TEST");
    ASSERT_NE(game, gameTest);
    game.setArchiveAbsoluteFilePath("TEST");
    ASSERT_EQ(game, gameTest);

    gameTest.setClientExecutableRelativeFilePath("TEST");
    ASSERT_NE(game, gameTest);
    game.setClientExecutableRelativeFilePath("TEST");
    ASSERT_EQ(game, gameTest);

    gameTest.setClientArgument("TEST");
    ASSERT_NE(game, gameTest);
    game.setClientArgument("TEST");
    ASSERT_EQ(game, gameTest);

    gameTest.setClientConnectArgument("TEST");
    ASSERT_NE(game, gameTest);
    game.setClientConnectArgument("TEST");
    ASSERT_EQ(game, gameTest);

    gameTest.setServerExecutableRelativeFilePath("TEST");
    ASSERT_NE(game, gameTest);
    game.setServerExecutableRelativeFilePath("TEST");
    ASSERT_EQ(game, gameTest);

    gameTest.setServerArgument("TEST");
    ASSERT_NE(game, gameTest);
    game.setServerArgument("TEST");
    ASSERT_EQ(game, gameTest);

    gameTest.setVersion("TEST");
    ASSERT_NE(game, gameTest);
    game.setVersion("TEST");
    ASSERT_EQ(game, gameTest);

    gameTest.setVersionSource(lanty::GameVersionSource::EXECUTABLE);
    ASSERT_NE(game, gameTest);
    game.setVersionSource(lanty::GameVersionSource::EXECUTABLE);
    ASSERT_EQ(game, gameTest);

    gameTest.setVersionRelativeFilePath("TEST");
    ASSERT_NE(game, gameTest);
    game.setVersionRelativeFilePath("TEST");
    ASSERT_EQ(game, gameTest);

    gameTest.setVersionFileQuery("TEST");
    ASSERT_NE(game, gameTest);
    game.setVersionFileQuery("TEST");
    ASSERT_EQ(game, gameTest);
}

TEST(GameTest, GetterName)
{
    lanty::Game game;
    QString name("TEST");
    game.setName(name);
    ASSERT_EQ(game.getName(), name);
}

TEST(GameTest, NameChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(nameChanged(QString)));
    QString name("TEST");
    game.setName(name);
    ASSERT_EQ(1, spy.count());
}

TEST(GameTest, GetterArchiveFile)
{
    lanty::Game game;
    QString archiveFilePath("TEST");
    game.setArchiveAbsoluteFilePath(archiveFilePath);
    ASSERT_EQ(game.getArchiveAbsoluteFilePath(), archiveFilePath);
}

TEST(GameTest, ArchiveFileChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(archivePathChanged(QString)));
    QString archiveFilePath("TEST");
    game.setArchiveAbsoluteFilePath(archiveFilePath);
    ASSERT_EQ(1, spy.count());
}

TEST(GameTest, GetterClientFile)
{
    lanty::Game game;
    QString clientFilePath("TEST");
    game.setClientExecutableRelativeFilePath(clientFilePath);
    ASSERT_EQ(game.getClientExecutableRelativeFilePath(), clientFilePath);
}

TEST(GameTest, clientFileChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(clientExecutableChanged(QString)));
    QString clientFilePath("TEST");
    game.setClientExecutableRelativeFilePath(clientFilePath);
    ASSERT_EQ(1, spy.count());
}

TEST(GameTest, GetterClientArgument)
{
    lanty::Game game;
    QString clientArgument("TEST");
    game.setClientArgument(clientArgument);
    ASSERT_EQ(game.getClientArgument(), clientArgument);
}

TEST(GameTest, ClientArgumentChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(clientArgumentChanged(QString)));
    QString clientArgument("TEST");
    game.setClientArgument(clientArgument);
    ASSERT_EQ(1, spy.count());
}

TEST(GameTest, GetterClientConnectArgument)
{
    lanty::Game game;
    QString clientConnectArgument("TEST");
    game.setClientConnectArgument(clientConnectArgument);
    ASSERT_EQ(game.getClientConnectArgument(), clientConnectArgument);
}

TEST(GameTest, ClientConnectArgumentChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(clientConnectArgumentChanged(QString)));
    QString clientConnectArgument("TEST");
    game.setClientConnectArgument(clientConnectArgument);
    ASSERT_EQ(1, spy.count());
}

TEST(GameTest, GetterServerExecutable)
{
    lanty::Game game;
    QString serverExecutable("TEST");
    game.setServerExecutableRelativeFilePath(serverExecutable);
    ASSERT_EQ(game.getServerExecutableRelativeFilePath(), serverExecutable);
}

TEST(GameTest, ServerExecutableChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(serverExecutableChanged(QString)));
    QString serverExecutable("TEST");
    game.setServerExecutableRelativeFilePath(serverExecutable);
    ASSERT_EQ(1, spy.count());
}

TEST(GameTest, GetterServerArgument)
{
    lanty::Game game;
    QString serverArgument("TEST");
    game.setServerArgument(serverArgument);
    ASSERT_EQ(game.getServerArgument(), serverArgument);
}

TEST(GameTest, ServerArgumentChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(serverArgumentChanged(QString)));
    QString serverArgument("TEST");
    game.setServerArgument(serverArgument);
    ASSERT_EQ(1, spy.count());
}

TEST(GameTest, GetterVersion)
{
    lanty::Game game;
    QString version("TEST");
    game.setVersion(version);
    ASSERT_EQ(game.getVersion(), version);
}

TEST(GameTest, VersionChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(versionChanged(QString)));
    QString version("TEST");
    game.setVersion(version);
    ASSERT_EQ(1, spy.count());
}

TEST(GameTest, GetterVersionSource)
{
    lanty::Game game;
    game.setVersionSource(lanty::GameVersionSource::EXECUTABLE);
    ASSERT_EQ(game.getVersionSource(), lanty::GameVersionSource::EXECUTABLE);
}

TEST(GameTest, VersionSourceChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(versionSourceChanged(GameVersionSource)));
    game.setVersionSource(lanty::GameVersionSource::EXECUTABLE);
    ASSERT_EQ(1, spy.count());
}

TEST(GameTest, GetterVersionFilePath)
{
    lanty::Game game;
    QString versionFilePath("TEST");
    game.setVersionRelativeFilePath(versionFilePath);
    ASSERT_EQ(game.getVersionRelativeFilePath(), versionFilePath);
}

TEST(GameTest, VersionFileChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(versionFileChanged(QString)));
    QString versionFilePath("TEST");
    game.setVersionRelativeFilePath(versionFilePath);
    ASSERT_EQ(1, spy.count());
}

TEST(GameTest, GetterVersionFileQuery)
{
    lanty::Game game;
    QString versionFileQuery("TEST");
    game.setVersionFileQuery(versionFileQuery);
    ASSERT_EQ(game.getVersionFileQuery(), versionFileQuery);
}

TEST(GameTest, VersionFileQueryChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(versionFileQueryChanged(QString)));
    QString versionFileQuery("TEST");
    game.setVersionFileQuery(versionFileQuery);
    ASSERT_EQ(1, spy.count());
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

TEST(GameTest, CoverImageChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(coverImageChanged(lanty::QPixmapAdapter)));
    QSize size(100, 100);
    lanty::QPixmapAdapter pixmap(size);
    game.setCoverImage(pixmap);
    ASSERT_EQ(1, spy.count());
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

TEST(GameTest, IconImageChangeSignal)
{
    lanty::Game game;
    QSignalSpy spy(&game, SIGNAL(iconImageChanged(lanty::QPixmapAdapter)));
    QSize size(100, 100);
    lanty::QPixmapAdapter pixmap(size);
    game.setIconImage(pixmap);
    ASSERT_EQ(1, spy.count());
}

TEST(GameTest, isVersionEmptyStringAndSourceNONE)
{
    lanty::Game game;
    QString version("");
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

TEST(GameTest, isVersionAnyStringAndSourceNONE)
{
    lanty::Game game;
    QString version("a23asfsg3asda");
    game.setVersion(version);
    game.setVersionSource(lanty::GameVersionSource::NONE);
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
    QString connect("asdad");
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
    QString serverArgument("asd");
    game.setServerExecutableRelativeFilePath(serverExecutable);
    game.setServerArgument(serverArgument);
    ASSERT_FALSE(game.canOpenDedicatedServer());
}

TEST(GameTest, canOpenDedicatedServerWithServerAndWithoutArgumentExecutable)
{
    lanty::Game game;
    QString serverExecutable("asdasd");
    QString serverArgument("");
    game.setServerExecutableRelativeFilePath(serverExecutable);
    game.setServerArgument(serverArgument);
    ASSERT_TRUE(game.canOpenDedicatedServer());
}

TEST(GameTest, canOpenDedicatedServerWithServerAndWithArgumentExecutable)
{
    lanty::Game game;
    QString serverExecutable("asdasd");
    QString serverArgument("asd");
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
    QString serverArgument("asd");
    game.setServerExecutableRelativeFilePath(serverExecutable);
    game.setServerArgument(serverArgument);
    ASSERT_TRUE(game.canOpenServer());
}

TEST(GameTest, canOpenServerWithServerAndWithArgumentExecutable)
{
    lanty::Game game;
    QString serverExecutable("asdaasd");
    QString serverArgument("asd");
    game.setServerExecutableRelativeFilePath(serverExecutable);
    game.setServerArgument(serverArgument);
    ASSERT_TRUE(game.canOpenServer());
}
