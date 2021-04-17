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

#include "game/GameClient.hpp"
#include "helper/QStringPrintHelper.hpp"

TEST(GameClient, FieldsShouldBeEmptyAfterCallingDefaultConstructor)
{
    lanty::GameClient gameclient;

    ASSERT_TRUE(gameclient.getExecutableFilePath().isEmpty());
    ASSERT_TRUE(gameclient.getArgument().isEmpty());
    ASSERT_TRUE(gameclient.getConnectArgument().isEmpty());
}

TEST(GameClient, GetterSetterTest)
{
    lanty::GameClient gameclient;

    QString filepath("bin/cod2mp.exe");
    gameclient.setExecutableFilePath(filepath);
    ASSERT_EQ(gameclient.getExecutableFilePath(), filepath);

    QString argument("+map warfare");
    gameclient.setArgument(argument);
    ASSERT_EQ(gameclient.getArgument(), argument);

    QString connectArgument("+ip 127.0.0.1");
    gameclient.setConnectArgument(connectArgument);
    ASSERT_EQ(gameclient.getConnectArgument(), connectArgument);
}

TEST(GameClient, ComparisonOperatorIfBothObjectsAreEqual)
{
    lanty::GameClient gameclientOne("bin/cod2mp.exe", "127.0.0.1", "+map warfare");
    lanty::GameClient gameclientTwo("bin/cod2mp.exe", "127.0.0.1", "+map warfare");

    ASSERT_EQ(gameclientOne, gameclientTwo);
}

TEST(GameClient, ComparisonOperatorIfBothObjectsAreUnEqual)
{
    lanty::GameClient gameclientOne;
    lanty::GameClient gameclientTwo("bin/cod2mp.exe", "127.0.0.1", "+map warfare");

    ASSERT_NE(gameclientOne, gameclientTwo);
}

TEST(GameClient, CopyConstructorAndOperator)
{
    lanty::GameClient gameclient("bin/cod2mp.exe", "127.0.0.1", "+map warfare");

    lanty::GameClient constructor(gameclient);
    ASSERT_EQ(gameclient, constructor);

    lanty::GameClient copyOperator;
    copyOperator = gameclient;
    ASSERT_EQ(gameclient, copyOperator);
}

TEST(GameClient, canJoinServerWithCLIEqualsFalseIfEmptyConnectArgument)
{
    lanty::GameClient gameclient;

    gameclient.setConnectArgument("");

    ASSERT_FALSE(gameclient.canJoinServerWithCLI());
}

TEST(GameClient, canJoinServerWithCLIEqualsTrueIfAnyConnectArgument)
{
    lanty::GameClient gameclient;

    gameclient.setConnectArgument("+connect ?");

    ASSERT_TRUE(gameclient.canJoinServerWithCLI());
}

TEST(GameClient, SerializeToJSON)
{
    QVector<QString> arguments = { "bin/cod2mp.exe", "+connect ?", "+name seternate" };

    lanty::GameClient gameclient(arguments.at(0), arguments.at(1), arguments.at(2));

    nlohmann::json json = gameclient.toJSON();

    ASSERT_EQ(json.size(), arguments.size());
    ASSERT_TRUE(json.contains("executable"));
    ASSERT_TRUE(json.contains("argument"));
    ASSERT_TRUE(json.contains("connect"));

    ASSERT_EQ(json[lanty::GameClient::EXECUTABLE_FILE_PATH_SERIALIZER_KEY], arguments.at(0).toStdString());
    ASSERT_EQ(json[lanty::GameClient::CONNECT_ARGUMENT_SERIALIZER_KEY], arguments.at(1).toStdString());
    ASSERT_EQ(json[lanty::GameClient::ARGUMENT_SERIALIZER_KEY], arguments.at(2).toStdString());
}

TEST(GameClient, DoNotShowEmptyFieldsAtJSON)
{
    lanty::GameClient gameclient;

    nlohmann::json json = gameclient.toJSON();

    EXPECT_EQ(json.size(), 0);
    EXPECT_TRUE(json.empty());
    ASSERT_FALSE(json.contains("executable"));
    ASSERT_FALSE(json.contains("argument"));
    ASSERT_FALSE(json.contains("connect"));
}

TEST(GameClient, SerializeToYAML)
{
    QVector<QString> arguments = { "bin/cod2mp.exe", "+connect ?", "+name seternate" };

    lanty::GameClient gameclient(arguments.at(0), arguments.at(1), arguments.at(2));

    YAML::Node yaml = gameclient.toYAML();

    ASSERT_EQ(yaml.size(), arguments.size());
    ASSERT_TRUE(yaml["executable"]);
    ASSERT_TRUE(yaml["argument"]);
    ASSERT_TRUE(yaml["connect"]);

    ASSERT_EQ(yaml[lanty::GameClient::EXECUTABLE_FILE_PATH_SERIALIZER_KEY].as<std::string>(),
              arguments.at(0).toStdString());
    ASSERT_EQ(yaml[lanty::GameClient::CONNECT_ARGUMENT_SERIALIZER_KEY].as<std::string>(), arguments.at(1).toStdString());
    ASSERT_EQ(yaml[lanty::GameClient::ARGUMENT_SERIALIZER_KEY].as<std::string>(), arguments.at(2).toStdString());
}

TEST(GameClient, DoNotShowEmptyFieldsAtYAML)
{
    lanty::GameClient gameclient;

    YAML::Node yaml = gameclient.toYAML();

    EXPECT_EQ(yaml.size(), 0);
    EXPECT_TRUE(yaml.IsNull());
    ASSERT_FALSE(yaml["executable"]);
    ASSERT_FALSE(yaml["argument"]);
    ASSERT_FALSE(yaml["connect"]);
}
