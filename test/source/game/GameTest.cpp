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

#include "game/Game.hpp"
#include "helper/QStringPrintHelper.hpp"

TEST(GameTest, FieldsShouldBeEmptyAfterCallingDefaultConstructor)
{
    lanty::Game game;

    ASSERT_TRUE(game.getName().isEmpty());
    ASSERT_TRUE(game.getArchiveFileName().isEmpty());
    ASSERT_TRUE(game.getClient().getArgument().isEmpty());
    ASSERT_TRUE(game.getClient().getConnectArgument().isEmpty());
    ASSERT_TRUE(game.getClient().getExecutableFilePath().isEmpty());
    ASSERT_TRUE(game.getServer().getArgument().isEmpty());
    ASSERT_TRUE(game.getServer().getExecutableFilePath().isEmpty());
    ASSERT_TRUE(game.getVersion().getVersion().isEmpty());
    ASSERT_TRUE(game.getVersion().getSource() == lanty::GameVersion::Source::NONE);
    ASSERT_TRUE(game.getVersion().getFilePath().isEmpty());
    ASSERT_TRUE(game.getVersion().getFileQuery().isEmpty());
    ASSERT_TRUE(game.getCover().isNull());
    ASSERT_TRUE(game.getIcon().isNull());
}

TEST(GameTest, DefaultDestructor)
{
    lanty::Game* game = new lanty::Game;
    delete game;
}

TEST(GameTest, GetterSetterTest)
{
    lanty::Game game;

    QString name("Call of Duty 2");
    game.setName(name);
    ASSERT_EQ(game.getName(), name);

    QString archive("D:\\lan\\games");
    game.setArchiveFileName(archive);
    ASSERT_EQ(game.getArchiveFileName(), archive);

    QString clientExecutable("bin/cod2.exe");
    game.setClientExecutableFilePath(clientExecutable);
    ASSERT_EQ(game.getClient().getExecutableFilePath(), clientExecutable);

    QString clientArgument("+map warfare");
    game.setClientArgument(clientArgument);
    ASSERT_EQ(game.getClient().getArgument(), clientArgument);

    QString clientConnectArgument("+ip 127.0.0.1");
    game.setClientConnectArgument(clientConnectArgument);
    ASSERT_EQ(game.getClient().getConnectArgument(), clientConnectArgument);

    QString serverExecutable("bin/cod2mp.exe");
    game.setServerExecutableFilePath(serverExecutable);
    ASSERT_EQ(game.getServer().getExecutableFilePath(), serverExecutable);

    QString serverArgument("+map lily");
    game.setServerArgument(serverArgument);
    ASSERT_EQ(game.getServer().getArgument(), serverArgument);

    QString version("1.0.0");
    game.setVersion(version);
    ASSERT_EQ(game.getVersion().getVersion(), version);

    lanty::GameVersion::Source versionSource = lanty::GameVersion::Source::FILE;
    game.setVersionSource(versionSource);
    ASSERT_EQ(game.getVersion().getSource(), versionSource);

    QString versionFile("version.txt");
    game.setVersionFilePath(versionFile);
    ASSERT_EQ(game.getVersion().getFilePath(), versionFile);

    QString versionQuery("Ext=");
    game.setVersionFileQuery(versionQuery);
    ASSERT_EQ(game.getVersion().getFileQuery(), versionQuery);

    QPixmap cover;
    game.setCover(cover);
    ASSERT_EQ(game.getCover().toImage(), cover.toImage());

    QPixmap icon;
    game.setIcon(icon);
    ASSERT_EQ(game.getIcon().toImage(), icon.toImage());
}

TEST(GameTest, ComparisonOperatorIfBothObjectsAreEqual)
{
    lanty::Game gameOne;
    gameOne.setName("CoD2");
    gameOne.setVersion("1.0.0");
    lanty::Game gameTwo(gameOne);

    ASSERT_EQ(gameOne, gameTwo);
}

TEST(GameTest, ComparisonOperatorIfBothObjectsAreUnEqual)
{
    lanty::Game gameOne;
    gameOne.setName("CoD2");
    gameOne.setVersion("1.0.0");
    lanty::Game gameTwo;

    ASSERT_NE(gameOne, gameTwo);
}

TEST(GameTest, CopyConstructorAndOperator)
{
    lanty::Game game;
    game.setName("CoD2");
    game.setVersion("1.0.0");

    lanty::Game constructor(game);
    ASSERT_EQ(game, constructor);

    lanty::Game copyOperator;
    copyOperator = game;
    ASSERT_EQ(game, copyOperator);
}

TEST(GameTest, SerializeToJSON)
{
    lanty::Game game("Call of Duty 2", "cod2.zip");

    game.setClientExecutableFilePath("bin/cod2mp.exe");
    game.setServerExecutableFilePath("bin/cod2mp.exe");
    game.setVersion("1.2.0");
    game.setVersionSource(lanty::GameVersion::Source::EXECUTABLE);

    nlohmann::json json = game.toJSON();

    ASSERT_EQ(json.size(), 5);
    ASSERT_TRUE(json.contains("name"));
    ASSERT_TRUE(json.contains("archive"));
    ASSERT_TRUE(json.contains("version"));
    ASSERT_TRUE(json.contains("client"));
    ASSERT_TRUE(json.contains("server"));

    ASSERT_EQ(json[lanty::Game::NAME_SERIALIZER_KEY], "Call of Duty 2");
    ASSERT_EQ(json[lanty::Game::ARCHIVE_SERIALIZER_KEY], "cod2.zip");
}

TEST(GameTest, DoNotShowEmptyFieldsAtJSON)
{
    lanty::Game game;

    nlohmann::json json = game.toJSON();

    ASSERT_TRUE(json.empty());
    ASSERT_FALSE(json.contains("name"));
    ASSERT_FALSE(json.contains("archive"));
    ASSERT_FALSE(json.contains("version"));
    ASSERT_FALSE(json.contains("client"));
    ASSERT_FALSE(json.contains("server"));
}
