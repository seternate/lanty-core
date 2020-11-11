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

#include <game/GameTest.hpp>

#include <QSignalSpy>
#include <QString>
#include <gtest/gtest.h>

#include <helper/QStringPrintHelper.hpp>

TEST_F(GameTest, MoveOperator)
{
    lanty::Game gameTest;
    QSize size(100, 100);
    QPixmap pixmap(size);

    gameTest.setName("TEST");
    gameTest.setArchiveAbsoluteFilePath("TEST");
    gameTest.setClientExecutableRelativeFilePath("TEST");
    gameTest.setClientArgument("TEST");
    gameTest.setClientConnectArgument("TEST");
    gameTest.setServerExecutableRelativeFilePath("TEST");
    gameTest.setServerArgument("TEST");
    gameTest.setVersion("TEST");
    gameTest.setVersionSource(lanty::GameVersionSource::EXECUTABLE);
    gameTest.setVersionRelativeFilePath("TEST");
    gameTest.setVersionFileQuery("TEST");
    gameTest.setCoverImage(pixmap);
    gameTest.setIconImage(pixmap);
    ASSERT_NE(game, gameTest);

    game = gameTest;
    ASSERT_EQ(game, gameTest);
}

TEST_F(GameTest, EqualOperator)
{
    lanty::Game gameTest;
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

TEST_F(GameTest, GetterName)
{
    QString name("TEST");
    game.setName(name);
    ASSERT_EQ(game.getName(), name);
}

TEST_F(GameTest, NameChangeSignal)
{
    QSignalSpy spy(&game, SIGNAL(nameChanged(QString)));
    QString name("TEST");
    game.setName(name);
    ASSERT_EQ(1, spy.count());
}

TEST_F(GameTest, GetterArchiveFile)
{
    QString archiveFilePath("TEST");
    game.setArchiveAbsoluteFilePath(archiveFilePath);
    ASSERT_EQ(game.getArchiveAbsoluteFilePath(), archiveFilePath);
}

TEST_F(GameTest, ArchiveFileChangeSignal)
{
    QSignalSpy spy(&game, SIGNAL(archivePathChanged(QString)));
    QString archiveFilePath("TEST");
    game.setArchiveAbsoluteFilePath(archiveFilePath);
    ASSERT_EQ(1, spy.count());
}

TEST_F(GameTest, GetterClientFile)
{
    QString clientFilePath("TEST");
    game.setClientExecutableRelativeFilePath(clientFilePath);
    ASSERT_EQ(game.getClientExecutableRelativeFilePath(), clientFilePath);
}

TEST_F(GameTest, clientFileChangeSignal)
{
    QSignalSpy spy(&game, SIGNAL(clientExecutableChanged(QString)));
    QString clientFilePath("TEST");
    game.setClientExecutableRelativeFilePath(clientFilePath);
    ASSERT_EQ(1, spy.count());
}

TEST_F(GameTest, GetterClientArgument)
{
    QString clientArgument("TEST");
    game.setClientArgument(clientArgument);
    ASSERT_EQ(game.getClientArgument(), clientArgument);
}

TEST_F(GameTest, ClientArgumentChangeSignal)
{
    QSignalSpy spy(&game, SIGNAL(clientArgumentChanged(QString)));
    QString clientArgument("TEST");
    game.setClientArgument(clientArgument);
    ASSERT_EQ(1, spy.count());
}

TEST_F(GameTest, GetterClientConnectArgument)
{
    QString clientConnectArgument("TEST");
    game.setClientConnectArgument(clientConnectArgument);
    ASSERT_EQ(game.getClientConnectArgument(), clientConnectArgument);
}

TEST_F(GameTest, ClientConnectArgumentChangeSignal)
{
    QSignalSpy spy(&game, SIGNAL(clientConnectArgumentChanged(QString)));
    QString clientConnectArgument("TEST");
    game.setClientConnectArgument(clientConnectArgument);
    ASSERT_EQ(1, spy.count());
}

TEST_F(GameTest, GetterServerExecutable)
{
    QString serverExecutable("TEST");
    game.setServerExecutableRelativeFilePath(serverExecutable);
    ASSERT_EQ(game.getServerExecutableRelativeFilePath(), serverExecutable);
}

TEST_F(GameTest, ServerExecutableChangeSignal)
{
    QSignalSpy spy(&game, SIGNAL(serverExecutableChanged(QString)));
    QString serverExecutable("TEST");
    game.setServerExecutableRelativeFilePath(serverExecutable);
    ASSERT_EQ(1, spy.count());
}

TEST_F(GameTest, GetterServerArgument)
{
    QString serverArgument("TEST");
    game.setServerArgument(serverArgument);
    ASSERT_EQ(game.getServerArgument(), serverArgument);
}

TEST_F(GameTest, ServerArgumentChangeSignal)
{
    QSignalSpy spy(&game, SIGNAL(serverArgumentChanged(QString)));
    QString serverArgument("TEST");
    game.setServerArgument(serverArgument);
    ASSERT_EQ(1, spy.count());
}

TEST_F(GameTest, GetterVersion)
{
    QString version("TEST");
    game.setVersion(version);
    ASSERT_EQ(game.getVersion(), version);
}

TEST_F(GameTest, VersionChangeSignal)
{
    QSignalSpy spy(&game, SIGNAL(versionChanged(QString)));
    QString version("TEST");
    game.setVersion(version);
    ASSERT_EQ(1, spy.count());
}

TEST_F(GameTest, GetterVersionSource)
{
    game.setVersionSource(lanty::GameVersionSource::EXECUTABLE);
    ASSERT_EQ(game.getVersionSource(), lanty::GameVersionSource::EXECUTABLE);
}

TEST_F(GameTest, VersionSourceChangeSignal)
{
    QSignalSpy spy(&game, SIGNAL(versionSourceChanged(GameVersionSource)));
    game.setVersionSource(lanty::GameVersionSource::EXECUTABLE);
    ASSERT_EQ(1, spy.count());
}

TEST_F(GameTest, GetterVersionFilePath)
{
    QString versionFilePath("TEST");
    game.setVersionRelativeFilePath(versionFilePath);
    ASSERT_EQ(game.getVersionRelativeFilePath(), versionFilePath);
}

TEST_F(GameTest, VersionFileChangeSignal)
{
    QSignalSpy spy(&game, SIGNAL(versionFileChanged(QString)));
    QString versionFilePath("TEST");
    game.setVersionRelativeFilePath(versionFilePath);
    ASSERT_EQ(1, spy.count());
}

TEST_F(GameTest, GetterVersionFileQuery)
{
    QString versionFileQuery("TEST");
    game.setVersionFileQuery(versionFileQuery);
    ASSERT_EQ(game.getVersionFileQuery(), versionFileQuery);
}

TEST_F(GameTest, VersionFileQueryChangeSignal)
{
    QSignalSpy spy(&game, SIGNAL(versionFileQueryChanged(QString)));
    QString versionFileQuery("TEST");
    game.setVersionFileQuery(versionFileQuery);
    ASSERT_EQ(1, spy.count());
}

TEST_F(GameTest, GetterCoverImage)
{
    QSize size(100, 100);
    QPixmap pixmap(size);
    game.setCoverImage(pixmap);
    ASSERT_FALSE(game.getCoverImage().isNull());
    ASSERT_EQ(game.getCoverImage().size(), size);
}

TEST_F(GameTest, CoverImageChangeSignal)
{
    QSignalSpy spy(&game, SIGNAL(coverImageChanged(QPixmap)));
    QSize size(100, 100);
    QPixmap pixmap(size);
    game.setCoverImage(pixmap);
    ASSERT_EQ(1, spy.count());
}

TEST_F(GameTest, GetterIconImage)
{
    QSize size(100, 100);
    QPixmap pixmap(size);
    game.setIconImage(pixmap);
    ASSERT_FALSE(game.getIconImage().isNull());
    ASSERT_EQ(game.getIconImage().size(), size);
}

TEST_F(GameTest, IconImageChangeSignal)
{
    QSignalSpy spy(&game, SIGNAL(iconImageChanged(QPixmap)));
    QSize size(100, 100);
    QPixmap pixmap(size);
    game.setIconImage(pixmap);
    ASSERT_EQ(1, spy.count());
}

TEST_F(GameTest, isVersionEmptyStringAndSourceNONE)
{
    QString version("");
    game.setVersion(version);
    game.setVersionSource(lanty::GameVersionSource::NONE);
    ASSERT_FALSE(game.isVersion());
}

TEST_F(GameTest, isVersionEmptyStringAndSourceNotNONE)
{
    QString version("");
    game.setVersion(version);
    game.setVersionSource(lanty::GameVersionSource::EXECUTABLE);
    ASSERT_FALSE(game.isVersion());
    game.setVersionSource(lanty::GameVersionSource::FILE);
    ASSERT_FALSE(game.isVersion());
}

TEST_F(GameTest, isVersionAnyStringAndSourceNONE)
{
    QString version("a23asfsg3asda");
    game.setVersion(version);
    game.setVersionSource(lanty::GameVersionSource::NONE);
    ASSERT_FALSE(game.isVersion());
}

TEST_F(GameTest, isVersionAnyStringAndSourceNotNONE)
{
    QString version("a23asfsg3asda");
    game.setVersion(version);
    game.setVersionSource(lanty::GameVersionSource::EXECUTABLE);
    ASSERT_TRUE(game.isVersion());
    game.setVersionSource(lanty::GameVersionSource::FILE);
    ASSERT_TRUE(game.isVersion());
}

TEST_F(GameTest, canJoinServerWithoutArgument)
{
    QString connect("");
    game.setClientConnectArgument(connect);
    ASSERT_FALSE(game.canJoinServerWithCLI());
}

TEST_F(GameTest, canJoinServerWithArgument)
{
    QString connect("asdad");
    game.setClientConnectArgument(connect);
    ASSERT_TRUE(game.canJoinServerWithCLI());
}

TEST_F(GameTest, canOpenDedicatedServerWithoutServerAndWithoutArgumentExecutable)
{
    QString serverExecutable("");
    QString serverArgument("");
    game.setServerExecutableRelativeFilePath(serverExecutable);
    game.setServerArgument(serverArgument);
    ASSERT_FALSE(game.canOpenDedicatedServer());
}

TEST_F(GameTest, canOpenDedicatedServerWithoutServerAndWithArgumentExecutable)
{
    QString serverExecutable("");
    QString serverArgument("asd");
    game.setServerExecutableRelativeFilePath(serverExecutable);
    game.setServerArgument(serverArgument);
    ASSERT_FALSE(game.canOpenDedicatedServer());
}

TEST_F(GameTest, canOpenDedicatedServerWithServerAndWithoutArgumentExecutable)
{
    QString serverExecutable("asdasd");
    QString serverArgument("");
    game.setServerExecutableRelativeFilePath(serverExecutable);
    game.setServerArgument(serverArgument);
    ASSERT_TRUE(game.canOpenDedicatedServer());
}

TEST_F(GameTest, canOpenDedicatedServerWithServerAndWithArgumentExecutable)
{
    QString serverExecutable("asdasd");
    QString serverArgument("asd");
    game.setServerExecutableRelativeFilePath(serverExecutable);
    game.setServerArgument(serverArgument);
    ASSERT_TRUE(game.canOpenDedicatedServer());
}

TEST_F(GameTest, canOpenServerWithoutServerAndWithoutArgumentExecutable)
{
    QString serverExecutable("");
    QString serverArgument("");
    game.setServerExecutableRelativeFilePath(serverExecutable);
    game.setServerArgument(serverArgument);
    ASSERT_FALSE(game.canOpenServer());
}

TEST_F(GameTest, canOpenServerWithServerAndWithoutArgumentExecutable)
{
    QString serverExecutable("asd");
    QString serverArgument("");
    game.setServerExecutableRelativeFilePath(serverExecutable);
    game.setServerArgument(serverArgument);
    ASSERT_TRUE(game.canOpenServer());
}

TEST_F(GameTest, canOpenServerWithoutServerAndWithArgumentExecutable)
{
    QString serverExecutable("");
    QString serverArgument("asd");
    game.setServerExecutableRelativeFilePath(serverExecutable);
    game.setServerArgument(serverArgument);
    ASSERT_TRUE(game.canOpenServer());
}

TEST_F(GameTest, canOpenServerWithServerAndWithArgumentExecutable)
{
    QString serverExecutable("asdaasd");
    QString serverArgument("asd");
    game.setServerExecutableRelativeFilePath(serverExecutable);
    game.setServerArgument(serverArgument);
    ASSERT_TRUE(game.canOpenServer());
}
