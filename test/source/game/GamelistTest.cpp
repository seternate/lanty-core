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
#include <nlohmann/json.hpp>

#include "game/Game.hpp"
#include "game/Gamelist.hpp"
#include "helper/QStringPrintHelper.hpp"

TEST(GamelistTest, SerializeJSON)
{
    lanty::Game* game1 = new lanty::Game();
    lanty::Game* game2 = new lanty::Game();
    lanty::Gamelist gamelist;

    game1->setName("test1");
    game1->setArchiveFileName("test1.zip");
    game1->setClientExecutableRelativeFilePath("test1.exe");

    game2->setName("test2");
    game2->setArchiveFileName("test2.zip");
    game2->setClientExecutableRelativeFilePath("test2.exe");

    gamelist.append(game1);
    gamelist.append(game2);

    nlohmann::json* json;
    json = gamelist.toJSON();

    QString jsonExpected(
        "{\"gamelist\":[{\"game\":{\"archive\":\"test1.zip\",\"client\":{\"executable\":\"test1.exe\"},\"name\":\"test1\"}},{\"game\":{\"archive\":\"test2.zip\",\"client\":{\"executable\":\"test2.exe\"},\"name\":\"test2\"}}]}");

    std::string s = json->dump();

    ASSERT_EQ(s, jsonExpected.toStdString());

    delete json;
}

TEST(GamelistTest, DeserializeJSON)
{
    nlohmann::json json
        = "{\"gamelist\":[{\"game\":{\"archive\":\"test1.zip\",\"client\":{\"executable\":\"test1.exe\"},\"name\":\"test1\"}},{\"game\":{\"archive\":\"test2.zip\",\"client\":{\"executable\":\"test2.exe\"},\"name\":\"test2\"}}]}"_json;

    lanty::Gamelist gamelist;
    gamelist.fromJSON(json);

    lanty::Game game1;
    lanty::Game game2;

    game1.setName("test1");
    game1.setArchiveFileName("test1.zip");
    game1.setClientExecutableRelativeFilePath("test1.exe");

    game2.setName("test2");
    game2.setArchiveFileName("test2.zip");
    game2.setClientExecutableRelativeFilePath("test2.exe");

    ASSERT_EQ(game1, gamelist.at(0));
    ASSERT_EQ(game2, gamelist.at(1));
}
