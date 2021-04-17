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
#include <QString>

#include "game/GameVersion.hpp"
#include "helper/QStringPrintHelper.hpp"

TEST(GameVersion, FieldsShouldBeEmptyAfterCallingDefaultConstructor)
{
    lanty::GameVersion gameversion;

    ASSERT_TRUE(gameversion.getVersion().isEmpty());
    ASSERT_EQ(gameversion.getSource(), lanty::GameVersion::Source::NONE);
    ASSERT_TRUE(gameversion.getFilePath().isEmpty());
    ASSERT_TRUE(gameversion.getFileQuery().isEmpty());
}

TEST(GameVersion, GetterSetterTest)
{
    lanty::GameVersion gameversion;

    QString version("1.0.0");
    gameversion.setVersion(version);
    ASSERT_EQ(gameversion.getVersion(), version);

    lanty::GameVersion::Source source = lanty::GameVersion::Source::FILE;
    gameversion.setSource(source);
    ASSERT_EQ(gameversion.getSource(), source);

    QString file("version.txt");
    gameversion.setFilePath(file);
    ASSERT_EQ(gameversion.getFilePath(), file);

    QString query("Ext=");
    gameversion.setFileQuery(query);
    ASSERT_EQ(gameversion.getFileQuery(), query);
}

TEST(GameVersion, ComparisonOperatorIfBothObjectsAreEqual)
{
    lanty::GameVersion gameversionOne;
    gameversionOne.setVersion("1.2.3");
    lanty::GameVersion gameversionTwo(gameversionOne);

    ASSERT_EQ(gameversionOne, gameversionTwo);
}

TEST(GameVersion, ComparisonOperatorIfBothObjectsAreUnEqual)
{
    lanty::GameVersion gameversionOne;
    gameversionOne.setVersion("1.2.3");
    lanty::GameVersion gameversionTwo;

    ASSERT_NE(gameversionOne, gameversionTwo);
}

TEST(GameVersion, CopyConstructorAndOperator)
{
    lanty::GameVersion gameversion;
    gameversion.setVersion("2.31.1");

    lanty::GameVersion constructor(gameversion);
    ASSERT_EQ(gameversion, constructor);

    lanty::GameVersion copyOperator;
    copyOperator = gameversion;
    ASSERT_EQ(gameversion, copyOperator);
}


TEST(GameVersion, isVersionEqualsFalseIfNoVersionStringAndSourceIsNONE)
{
    lanty::GameVersion gameversion;

    gameversion.setVersion("");
    gameversion.setSource(lanty::GameVersion::Source::NONE);

    ASSERT_FALSE(gameversion.isVersion());
}

TEST(GameVersion, isVersionEqualsFalseIfAnyVersionStringAndSourceIsNONE)
{
    lanty::GameVersion gameversion;

    gameversion.setVersion("12.42.2");
    gameversion.setSource(lanty::GameVersion::Source::NONE);

    ASSERT_FALSE(gameversion.isVersion());
}

TEST(GameVersion, isVersionEqualsFalseIfEmptyVersionStringAndSourceNotNONE)
{
    lanty::GameVersion gameversion;

    gameversion.setVersion("");

    gameversion.setSource(lanty::GameVersion::Source::EXECUTABLE);
    ASSERT_FALSE(gameversion.isVersion());

    gameversion.setSource(lanty::GameVersion::Source::FILE);
    ASSERT_FALSE(gameversion.isVersion());
}

TEST(GameVersion, isVersionEqualsTrueIfAnyVersionStringAndSourceNotNONE)
{
    lanty::GameVersion gameversion;

    gameversion.setVersion("12.14.0");

    gameversion.setSource(lanty::GameVersion::Source::EXECUTABLE);
    ASSERT_TRUE(gameversion.isVersion());

    gameversion.setSource(lanty::GameVersion::Source::FILE);
    ASSERT_TRUE(gameversion.isVersion());
}

TEST(GameVersion, SourceStringDeSerialization)
{
    ASSERT_EQ(lanty::GameVersion::QStringToSource("EXECUTABLE"), lanty::GameVersion::Source::EXECUTABLE);
    ASSERT_EQ(lanty::GameVersion::SourceToQString(lanty::GameVersion::Source::EXECUTABLE), QString("EXECUTABLE"));
}

TEST(GameVersion, SerializeToJSON)
{
    QVector<QString> arguments = { "2.13.9", "FILE", "version.txt", "Ext=" };

    lanty::GameVersion gameversion;
    gameversion.setVersion(arguments.at(0));
    gameversion.setSource(lanty::GameVersion::QStringToSource(arguments.at(1)));
    gameversion.setFilePath(arguments.at(2));
    gameversion.setFileQuery(arguments.at(3));

    nlohmann::json json = gameversion.toJSON();

    ASSERT_EQ(json.size(), arguments.size());
    ASSERT_TRUE(json.contains("info"));
    ASSERT_TRUE(json.contains("format"));
    ASSERT_TRUE(json.contains("file"));
    ASSERT_TRUE(json.contains("query"));

    ASSERT_EQ(json[lanty::GameVersion::VERSION_SERIALIZER_KEY], arguments.at(0).toStdString());
    ASSERT_EQ(json[lanty::GameVersion::SOURCE_SERIALIZER_KEY], arguments.at(1).toStdString());
    ASSERT_EQ(json[lanty::GameVersion::FILEPATH_SERIALIZER_KEY], arguments.at(2).toStdString());
    ASSERT_EQ(json[lanty::GameVersion::FILEQUERY_SERIALIZER_KEY], arguments.at(3).toStdString());
}

TEST(GameVersion, DoNotShowEmptyFieldsAtJSON)
{
    lanty::GameVersion gameversion;

    nlohmann::json json = gameversion.toJSON();

    EXPECT_EQ(json.size(), 0);
    EXPECT_TRUE(json.empty());
    ASSERT_FALSE(json.contains("info"));
    ASSERT_FALSE(json.contains("format"));
    ASSERT_FALSE(json.contains("file"));
    ASSERT_FALSE(json.contains("query"));
}

TEST(GameVersion, SerializeToYAML)
{
    QVector<QString> arguments = { "2.13.9", "FILE", "version.txt", "Ext=" };

    lanty::GameVersion gameversion;
    gameversion.setVersion(arguments.at(0));
    gameversion.setSource(lanty::GameVersion::QStringToSource(arguments.at(1)));
    gameversion.setFilePath(arguments.at(2));
    gameversion.setFileQuery(arguments.at(3));

    YAML::Node yaml = gameversion.toYAML();

    ASSERT_EQ(yaml.size(), arguments.size());
    ASSERT_TRUE(yaml["info"]);
    ASSERT_TRUE(yaml["format"]);
    ASSERT_TRUE(yaml["file"]);
    ASSERT_TRUE(yaml["query"]);

    ASSERT_EQ(yaml[lanty::GameVersion::VERSION_SERIALIZER_KEY].as<std::string>(), arguments.at(0).toStdString());
    ASSERT_EQ(yaml[lanty::GameVersion::SOURCE_SERIALIZER_KEY].as<std::string>(), arguments.at(1).toStdString());
    ASSERT_EQ(yaml[lanty::GameVersion::FILEPATH_SERIALIZER_KEY].as<std::string>(), arguments.at(2).toStdString());
    ASSERT_EQ(yaml[lanty::GameVersion::FILEQUERY_SERIALIZER_KEY].as<std::string>(), arguments.at(3).toStdString());
}

TEST(GameVersion, DoNotShowEmptyFieldsAtYAML)
{
    lanty::GameVersion gameversion;

    YAML::Node yaml = gameversion.toYAML();

    EXPECT_EQ(yaml.size(), 0);
    EXPECT_TRUE(yaml.IsNull());
    ASSERT_FALSE(yaml["info"]);
    ASSERT_FALSE(yaml["format"]);
    ASSERT_FALSE(yaml["file"]);
    ASSERT_FALSE(yaml["query"]);
}
