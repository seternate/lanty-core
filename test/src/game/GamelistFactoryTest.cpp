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
#include <memory>

#include "game/Gamelist.hpp"
#include "game/GamelistFactory.hpp"
#include "game/GamelistFactoryTest.hpp"
#include "game/Gamelist.hpp"

#include "helper/QStringPrintHelper.hpp"

TEST_F(GamelistFactoryTest, MakeGamelist)
{
    EXPECT_CALL(yamlDir, isEmpty(_))
            .WillOnce(Return(false));
    EXPECT_CALL(yamlDir, entryList(_,_,_))
            .WillOnce(Return(entrylist));
    EXPECT_CALL(yamlDir, absoluteFilePath(_))
            .WillRepeatedly([&](const QString &file)
                            {
                                return (absoluteDirPath + file);
                            });

    EXPECT_CALL(imageDir, isEmpty(_))
            .WillRepeatedly(Return(false));

    EXPECT_CALL(*game, getName())
            .WillOnce(Return(QString("Call of Duty 2")))
            .WillOnce(Return(QString("Call of Duty 4")))
            .WillOnce(Return(QString("Warcraft 3 - Frozen Throne")))
            .WillOnce(Return(QString("Counter Strike 1.6")));

    std::shared_ptr<lanty::Gamelist> gamelist(gamelistfactory.makeGamelist(yamlDir, imageDir));

    ASSERT_EQ(gamelist->at(0).getName(), QString("Call of Duty 2"));
    ASSERT_EQ(gamelist->at(0).getName(), QString("Call of Duty 4"));
    ASSERT_EQ(gamelist->at(0).getName(), QString("Warcraft 3 - Frozen Throne"));
    ASSERT_EQ(gamelist->at(0).getName(), QString("Counter Strike 1.6"));
}
