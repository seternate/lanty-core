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

#ifndef GAME_GAMELISTFACTORYTEST_HPP
#define GAME_GAMELISTFACTORYTEST_HPP

#include <gmock/gmock-nice-strict.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

#include "game/GamelistFactory.hpp"
#include "game/Game.hpp"
#include "mock/MockGame.hpp"
#include "mock/MockGameHelper.hpp"
#include "mock/MockQDir.hpp"
#include "mock/MockYamlNode.hpp"

using ::testing::_;
using ::testing::Return;
using ::testing::NiceMock;

class GamelistFactoryTest : public ::testing::Test
{
public:
    GamelistFactoryTest(void) : yamlDir(),
                                imageDir(),
                                game(new NiceMock<MockGame>()),
                                yamlNode(new NiceMock<MockYamlNode>()),
                                gameHelper(new NiceMock<MockGameHelper>()),
                                entrylist(),
                                absoluteDirPath("C:/Users/Program/lanty/")
    {
        entrylist.append("cod2.yaml");
        entrylist.append("cod4.yml");
        entrylist.append("wc3.yaml");
        entrylist.append("cs16.yml");
        entrylist.append("template.yaml");

        gamelistfactory.setGameDependency(game);
        gamelistfactory.setYamlNodeDependency(yamlNode);
        gamelistfactory.setGameHelperDependency(gameHelper);
    };

protected:
    MockQDir yamlDir;
    MockQDir imageDir;
    NiceMock<MockGame> *game;
    NiceMock<MockYamlNode> *yamlNode;
    NiceMock<MockGameHelper> *gameHelper;
    QStringList entrylist;
    QString absoluteDirPath;
    lanty::GamelistFactory gamelistfactory;
};

#endif /* GAME_GAMELISTFACTORYTEST_HPP */
