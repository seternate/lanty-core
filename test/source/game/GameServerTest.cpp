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
#include <QVector>

#include "game/GameServer.hpp"
#include "helper/QStringPrintHelper.hpp"

TEST(GameServer, FieldsShouldBeEmptyAfterCallingDefaultConstructor)
{
    lanty::GameServer gameserver;

    ASSERT_TRUE(gameserver.getExecutableFilePath().isEmpty());
    ASSERT_TRUE(gameserver.getArgument().isEmpty());
}

TEST(GameServer, GetterSetterTest)
{
    lanty::GameServer gameserver;

    QString serverExecutable("bin/cod2mp.exe");
    gameserver.setExecutableFilePath(serverExecutable);
    ASSERT_EQ(gameserver.getExecutableFilePath(), serverExecutable);

    QString serverArgument("+map lily");
    gameserver.setArgument(serverArgument);
    ASSERT_EQ(gameserver.getArgument(), serverArgument);
}

TEST(GameServer, ComparisonOperatorIfBothObjectsAreEqual)
{
    lanty::GameServer gameserverOne("bin/cod2mp.exe", "+map lily");
    lanty::GameServer gameserverTwo("bin/cod2mp.exe", "+map lily");

    ASSERT_EQ(gameserverOne, gameserverTwo);
}

TEST(GameServer, ComparisonOperatorIfBothObjectsAreUnEqual)
{
    lanty::GameServer gameserverOne;
    lanty::GameServer gameserverTwo("bin/cod2mp.exe", "+map lily");

    ASSERT_NE(gameserverOne, gameserverTwo);
}

TEST(GameServer, CopyConstructorAndOperator)
{
    lanty::GameServer gameserver("bin/cod2mp.exe", "+map lily");

    lanty::GameServer constructor(gameserver);
    ASSERT_EQ(gameserver, constructor);

    lanty::GameServer copyOperator;
    copyOperator = gameserver;
    ASSERT_EQ(gameserver, copyOperator);
}

TEST(GameServer, MoveConstructorAndOperator)
{
    lanty::GameServer gameserver("bin/cod2mp.exe", "+map warfare");

    lanty::GameServer temp = lanty::GameServer("bin/cod2mp.exe", "+map warfare");
    lanty::GameServer constructor(std::move(temp));
    ASSERT_EQ(gameserver, constructor);

    lanty::GameServer moveOperator;
    temp = lanty::GameServer("bin/cod2mp.exe", "+map warfare");
    moveOperator = std::move(temp);
    ASSERT_EQ(gameserver, moveOperator);
}

TEST(GameServer, canOpenDedicatedServerEqualsFalseIfNoServerExeAndEmptyArgument)
{
    lanty::GameServer gameserver;

    gameserver.setExecutableFilePath("");
    gameserver.setArgument("");

    ASSERT_FALSE(gameserver.canOpenDedicatedServer());
}

TEST(GameServer, canOpenDedicatedServerEqualsFalseIfNoServerExeAndAnyArgument)
{
    lanty::GameServer gameserver;

    gameserver.setExecutableFilePath("");
    gameserver.setArgument("+map crossfire");

    ASSERT_FALSE(gameserver.canOpenDedicatedServer());
}

TEST(GameServer, canOpenDedicatedServerEqualsTrueIfServerExeAndEmptyArgument)
{
    lanty::GameServer gameserver;

    gameserver.setExecutableFilePath("bin/cod2server.exe");
    gameserver.setArgument("");

    ASSERT_TRUE(gameserver.canOpenDedicatedServer());
}

TEST(GameServer, canOpenDedicatedServerEqualsTrueIfServerExeAndAnyArgument)
{
    lanty::GameServer gameserver;

    gameserver.setExecutableFilePath("bin/cod2.exe");
    gameserver.setArgument("+map crossfire");

    ASSERT_TRUE(gameserver.canOpenDedicatedServer());
}

TEST(GameServer, canOpenServerEqualsFalseIfNoServerExeAndEmptyArgument)
{
    lanty::GameServer gameserver;

    gameserver.setExecutableFilePath("");
    gameserver.setArgument("");

    ASSERT_FALSE(gameserver.canOpenServer());
}

TEST(GameServer, canOpenServerEqualsTrueIfServerExeAndEmptyArgument)
{
    lanty::GameServer gameserver;

    gameserver.setExecutableFilePath("bin/cod2.exe");
    gameserver.setArgument("");

    ASSERT_TRUE(gameserver.canOpenServer());
}

TEST(GameServer, canOpenServerEqualsTrueIfNoServerExeAndAnyArgument)
{
    lanty::GameServer gameserver;

    gameserver.setExecutableFilePath("");
    gameserver.setArgument("+map crossfire");

    ASSERT_TRUE(gameserver.canOpenServer());
}

TEST(GameServer, canOpenServerEqualsTrueIfServerExeAndAnyArgument)
{
    lanty::GameServer gameserver;

    gameserver.setExecutableFilePath("bin/cod2.exe");
    gameserver.setArgument("+map crossfire");

    ASSERT_TRUE(gameserver.canOpenServer());
}

TEST(GameServer, SerializeToJSON)
{
    QVector<QString> arguments = { "bin/cod2mp.exe", "+map crossfire" };

    lanty::GameServer gameserver(arguments.at(0), arguments.at(1));

    nlohmann::json json = gameserver.toJSON();

    ASSERT_EQ(json.size(), arguments.size());
    ASSERT_TRUE(json.contains("executable"));
    ASSERT_TRUE(json.contains("argument"));

    ASSERT_EQ(json[lanty::GameServer::EXECUTABLE_FILE_PATH_SERIALIZER_KEY], arguments.at(0).toStdString());
    ASSERT_EQ(json[lanty::GameServer::ARGUMENT_SERIALIZER_KEY], arguments.at(1).toStdString());
}

TEST(GameServer, DoNotShowEmptyFieldsAtJSON)
{
    lanty::GameServer gameserver;

    nlohmann::json json = gameserver.toJSON();

    EXPECT_EQ(json.size(), 0);
    EXPECT_TRUE(json.empty());
    ASSERT_FALSE(json.contains("executable"));
    ASSERT_FALSE(json.contains("argument"));
}

TEST(GameServer, SerializeToYAML)
{
    QVector<QString> arguments = { "bin/cod2mp.exe", "+map crossfire" };

    lanty::GameServer gameserver(arguments.at(0), arguments.at(1));

    YAML::Node yaml = gameserver.toYAML();

    ASSERT_EQ(yaml.size(), arguments.size());
    ASSERT_TRUE(yaml["executable"]);
    ASSERT_TRUE(yaml["argument"]);

    ASSERT_EQ(yaml[lanty::GameServer::EXECUTABLE_FILE_PATH_SERIALIZER_KEY].as<std::string>(),
              arguments.at(0).toStdString());
    ASSERT_EQ(yaml[lanty::GameServer::ARGUMENT_SERIALIZER_KEY].as<std::string>(), arguments.at(1).toStdString());
}

TEST(GameServer, DoNotShowEmptyFieldsAtYAML)
{
    lanty::GameServer gameserver;

    YAML::Node yaml = gameserver.toYAML();

    EXPECT_EQ(yaml.size(), 0);
    EXPECT_TRUE(yaml.IsNull());
    ASSERT_FALSE(yaml["executable"]);
    ASSERT_FALSE(yaml["argument"]);
}
