/* Copyright <2021> <Levin Jeck>
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

#include "game/QGame.hpp"
#include "helper/QStringPrintHelper.hpp"

TEST(QGameTest, ComparisonOperatorIfBothObjectsAreEqual)
{
    lanty::QGame gameOne;
    gameOne.setVersion("1.2.3");
    lanty::QGame gameTwo;
    gameTwo.setVersion("1.2.3");

    ASSERT_EQ(gameOne, gameTwo);
}

TEST(QGameTest, ComparisonOperatorIfBothObjectsAreUnEqual)
{
    lanty::QGame gameOne;
    gameOne.setVersion("1.2.3");
    lanty::QGame gameTwo;

    ASSERT_NE(gameOne, gameTwo);
}

TEST(QGameTest, LessThanOperator)
{
    lanty::QGame gameOne;
    gameOne.setName("World of Warcraft");
    lanty::QGame gameTwo;
    gameTwo.setName("Team Fortress 2");

    ASSERT_LT(gameTwo, gameOne);
}

TEST(QGameTest, CopyConstructorAndOperatorForGames)
{
    lanty::Game game;
    game.setName("test");

    lanty::QGame constructor(game);
    ASSERT_EQ(constructor, game);

    lanty::QGame copyOperator;
    copyOperator = game;
    ASSERT_EQ(copyOperator, game);
}

TEST(QGameTest, ChangedSignal)
{
    lanty::QGame game;
    QSignalSpy spy(&game, SIGNAL(changed(void)));

    game.setName("name");
    ASSERT_EQ(spy.count(), 1);
    game.setArchiveFileName("archive.zip");
    ASSERT_EQ(spy.count(), 2);
    game.setClientExecutableFilePath("wow.exe");
    ASSERT_EQ(spy.count(), 3);
    game.setClientArgument("argument");
    ASSERT_EQ(spy.count(), 4);
    game.setClientConnectArgument("connect");
    ASSERT_EQ(spy.count(), 5);
    game.setServerExecutableFilePath("wow.exe");
    ASSERT_EQ(spy.count(), 6);
    game.setServerArgument("argument");
    ASSERT_EQ(spy.count(), 7);
    game.setVersion("version");
    ASSERT_EQ(spy.count(), 8);
    game.setVersionSource(lanty::GameVersion::Source::NONE);
    ASSERT_EQ(spy.count(), 9);
    game.setVersionFilePath("path");
    ASSERT_EQ(spy.count(), 10);
    game.setVersionFileQuery("query");
    ASSERT_EQ(spy.count(), 11);
    game.setCover(QPixmap());
    ASSERT_EQ(spy.count(), 12);
    game.setIcon(QPixmap());

    ASSERT_EQ(spy.count(), 13);
}

TEST(QGameTest, NameChangedSignal)
{
    lanty::QGame game;
    QSignalSpy spy(&game, SIGNAL(nameChanged(const QString&)));

    game.setName("name");

    ASSERT_EQ(spy.count(), 1);
}

TEST(QGameTest, ArchiveFileNameChangedSignal)
{
    lanty::QGame game;
    QSignalSpy spy(&game, SIGNAL(archiveFileNameChanged(const QString&)));

    game.setArchiveFileName("archive.zip");

    ASSERT_EQ(spy.count(), 1);
}

TEST(QGameTest, ClientExecutableFilePathChangedSignal)
{
    lanty::QGame game;
    QSignalSpy spy(&game, SIGNAL(clientExecutableFilePathChanged(const QString&)));

    game.setClientExecutableFilePath("wow.exe");

    ASSERT_EQ(spy.count(), 1);
}

TEST(QGameTest, ClientArgumentChanged)
{
    lanty::QGame game;
    QSignalSpy spy(&game, SIGNAL(clientArgumentChanged(const QString&)));

    game.setClientArgument("argument");

    ASSERT_EQ(spy.count(), 1);
}

TEST(QGameTest, ClientConnectArgumentChangedSignal)
{
    lanty::QGame game;
    QSignalSpy spy(&game, SIGNAL(clientConnectArgumentChanged(const QString&)));

    game.setClientConnectArgument("connect");

    ASSERT_EQ(spy.count(), 1);
}

TEST(QGameTest, ServerExecutableFilePathChangedSignal)
{
    lanty::QGame game;
    QSignalSpy spy(&game, SIGNAL(serverExecutableFilePathChanged(const QString&)));

    game.setServerExecutableFilePath("wow.exe");

    ASSERT_EQ(spy.count(), 1);
}

TEST(QGameTest, ServerArgumentChangedSignal)
{
    lanty::QGame game;
    QSignalSpy spy(&game, SIGNAL(serverArgumentChanged(const QString&)));

    game.setServerArgument("argument");

    ASSERT_EQ(spy.count(), 1);
}

TEST(QGameTest, VersionChangedSignal)
{
    lanty::QGame game;
    QSignalSpy spy(&game, SIGNAL(versionChanged(const QString&)));

    game.setVersion("1.0.0");

    ASSERT_EQ(spy.count(), 1);
}

TEST(QGameTest, VersionSourceChangedSignal)
{
    lanty::QGame game;
    QSignalSpy spy(&game, SIGNAL(versionSourceChanged(const lanty::GameVersion::Source)));

    game.setVersionSource(lanty::GameVersion::Source::NONE);

    ASSERT_EQ(spy.count(), 1);
}

TEST(QGameTest, VersionFilePathChangedSignal)
{
    lanty::QGame game;
    QSignalSpy spy(&game, SIGNAL(versionFilePathChanged(const QString&)));

    game.setVersionFilePath("filepath");

    ASSERT_EQ(spy.count(), 1);
}

TEST(QGameTest, VersionFileQueryChangedSignal)
{
    lanty::QGame game;
    QSignalSpy spy(&game, SIGNAL(versionFileQueryChanged(const QString&)));

    game.setVersionFileQuery("query");

    ASSERT_EQ(spy.count(), 1);
}

TEST(QGameTest, CoverChangedSignal)
{
    lanty::QGame game;
    QSignalSpy spy(&game, SIGNAL(coverChanged(const QPixmap&)));

    game.setCover(QPixmap());

    ASSERT_EQ(spy.count(), 1);
}

TEST(QGameTest, IconChangedSignal)
{
    lanty::QGame game;
    QSignalSpy spy(&game, SIGNAL(iconChanged(const QPixmap&)));

    game.setIcon(QPixmap());

    ASSERT_EQ(spy.count(), 1);
}
