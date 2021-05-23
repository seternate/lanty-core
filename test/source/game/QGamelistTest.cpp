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
#include "game/QGame.hpp"
#include "game/QGamelist.hpp"
#include "helper/QStringPrintHelper.hpp"

#include <QDebug>
#include <QSignalSpy>
#include <fstream>

TEST(QGamelistTest, DefaultConstructorCreatesEmptyList)
{
    lanty::QGamelist gamelist;

    ASSERT_EQ(gamelist.size(), 0);
}

TEST(QGamelistTest, ComparisonOperatorIfBothObjectsAreEqual)
{
    lanty::QGamelist gamelistOne;
    lanty::QGamelist gamelistTwo;

    lanty::Game* gameOne = new lanty::QGame();
    lanty::Game* gameTwo = new lanty::QGame();
    lanty::Game* gameThree = new lanty::QGame();
    lanty::Game* gameFour = new lanty::QGame();
    gameOne->setName("unique1");
    gameTwo->setName("unique2");
    gameThree->setName("unique1");
    gameFour->setName("unique2");

    gamelistOne.append(gameOne);
    gamelistOne.append(gameTwo);
    gamelistTwo.append(gameThree);
    gamelistTwo.append(gameFour);

    ASSERT_EQ(gamelistOne, gamelistTwo);
}

TEST(QGamelistTest, ComparisonOperatorIfBothObjectsAreUnEqual)
{
    lanty::QGamelist gamelistOne;
    lanty::QGamelist gamelistTwo;

    lanty::Game* gameOne = new lanty::QGame();
    lanty::Game* gameTwo = new lanty::QGame();
    lanty::Game* gameThree = new lanty::QGame();
    lanty::Game* gameFour = new lanty::QGame();
    gameOne->setName("unique1");
    gameTwo->setName("unique2");
    gameThree->setName("unique3");
    gameFour->setName("unique4");

    gamelistOne.append(gameOne);
    gamelistOne.append(gameTwo);
    gamelistTwo.append(gameThree);
    gamelistTwo.append(gameFour);

    ASSERT_NE(gamelistOne, gamelistTwo);
}

TEST(QGamelistTest, AccessOperator)
{
    lanty::QGamelist gamelist;
    const lanty::QGamelist* gamelistPtr = &gamelist;

    lanty::Game* game = new lanty::QGame();
    game->setName("game");

    gamelist.append(game);

    ASSERT_EQ(gamelist[0], *game);
    ASSERT_EQ((*gamelistPtr)[0], *game);
}

TEST(QGamelistTest, AppendUniqueGamesToList)
{
    lanty::QGamelist gamelist;
    QSignalSpy spyRowsAboutToBeInserted(&gamelist, SIGNAL(rowsAboutToBeInserted(const QModelIndex&, int, int)));
    QSignalSpy spyRowsInserted(&gamelist, SIGNAL(rowsInserted(const QModelIndex&, int, int)));

    lanty::Game* gameOne = new lanty::QGame();
    lanty::Game* gameTwo = new lanty::QGame();
    gameOne->setName("unique1");
    gameTwo->setName("unique2");

    ASSERT_TRUE(gamelist.append(gameOne));
    ASSERT_TRUE(gamelist.append(gameTwo));

    ASSERT_EQ(gamelist.size(), 2);
    ASSERT_EQ(&gamelist.at(0), gameOne);
    ASSERT_EQ(&gamelist.at(1), gameTwo);

    ASSERT_EQ(spyRowsAboutToBeInserted.count(), 2);
    ASSERT_EQ(spyRowsInserted.count(), 2);
}

TEST(QGamelistTest, AppendNonUniqueGamesToList)
{
    lanty::QGamelist gamelist;
    QSignalSpy spyRowsAboutToBeInserted(&gamelist, SIGNAL(rowsAboutToBeInserted(const QModelIndex&, int, int)));
    QSignalSpy spyRowsInserted(&gamelist, SIGNAL(rowsInserted(const QModelIndex&, int, int)));

    lanty::Game* gameOne = new lanty::QGame();
    lanty::Game* gameTwo = new lanty::QGame();
    gameOne->setName("non-unique");
    gameTwo->setName("non-unique");

    ASSERT_TRUE(gamelist.append(gameOne));
    ASSERT_FALSE(gamelist.append(gameTwo));

    ASSERT_EQ(gamelist.size(), 1);
    ASSERT_EQ(&gamelist.at(0), gameOne);

    ASSERT_EQ(spyRowsAboutToBeInserted.count(), 1);
    ASSERT_EQ(spyRowsInserted.count(), 1);

    delete gameTwo;
}

TEST(QGamelistTest, GamelistContainsGameAlready)
{
    lanty::QGamelist gamelist;

    lanty::Game* gameOne = new lanty::QGame();
    lanty::Game* gameTwo = new lanty::QGame();
    gameOne->setName("non-unique");
    gameTwo->setName("non-unique");

    gamelist.append(gameOne);

    ASSERT_TRUE(gamelist.contains(gameTwo));
}

TEST(QGamelistTest, GamelistContainsGameNot)
{
    lanty::QGamelist gamelist;

    lanty::Game* gameOne = new lanty::QGame();
    lanty::Game* gameTwo = new lanty::QGame();
    gameOne->setName("unique1");
    gameTwo->setName("unique2");

    gamelist.append(gameOne);

    ASSERT_FALSE(gamelist.contains(gameTwo));
}

TEST(QGamelistTest, SortGamesForGameNames)
{
    lanty::QGamelist gamelist;
    QSignalSpy spyModelAboutToBeReset(&gamelist, SIGNAL(modelAboutToBeReset(void)));
    QSignalSpy spyModelReset(&gamelist, SIGNAL(modelReset(void)));

    lanty::Game* game1 = new lanty::QGame();
    lanty::Game* game2 = new lanty::QGame();
    game1->setName("aaaaa");
    game2->setName("hh");

    gamelist.append(game2);
    gamelist.append(game1);

    ASSERT_EQ(&gamelist.at(0), game2);
    ASSERT_EQ(&gamelist.at(1), game1);

    gamelist.sortGames();

    ASSERT_EQ(&gamelist.at(0), game1);
    ASSERT_EQ(&gamelist.at(1), game2);

    ASSERT_EQ(spyModelAboutToBeReset.count(), 1);
    ASSERT_EQ(spyModelReset.count(), 1);
}

TEST(QGamelistTest, UpdateWithAnotherList)
{
    lanty::QGamelist gamelistToUpdate;
    QSignalSpy spyRowsAboutToBeInserted(&gamelistToUpdate, SIGNAL(rowsAboutToBeInserted(const QModelIndex&, int, int)));
    QSignalSpy spyRowsInserted(&gamelistToUpdate, SIGNAL(rowsInserted(const QModelIndex&, int, int)));
    QSignalSpy spyRowsAboutToBeRemoved(&gamelistToUpdate, SIGNAL(rowsAboutToBeRemoved(const QModelIndex&, int, int)));
    QSignalSpy spyRowsRemoved(&gamelistToUpdate, SIGNAL(rowsRemoved(const QModelIndex&, int, int)));

    {
        lanty::Game* gameOne = new lanty::QGame();
        gameOne->setName("game1");
        lanty::Game* gameUnique = new lanty::QGame();
        gameUnique->setName("unique");
        gamelistToUpdate.append(gameOne);
        gamelistToUpdate.append(gameUnique);

        lanty::Game* gameTwo = new lanty::QGame();
        gameTwo->setName("game2");
        lanty::Game* gameThree = new lanty::QGame();
        gameThree->setName("game3");
        lanty::Game* gameOneAsFour = new lanty::QGame();
        gameOneAsFour->operator=(*gameOne);
        lanty::QGamelist gamelist;
        gamelist.append(gameThree);
        gamelist.append(gameTwo);
        gamelist.append(gameOneAsFour);

        ASSERT_TRUE(gamelistToUpdate.update(gamelist));
    }

    ASSERT_EQ(gamelistToUpdate.size(), 3);
    ASSERT_EQ(gamelistToUpdate.at(0).getName(), QString("game1"));
    ASSERT_EQ(gamelistToUpdate.at(1).getName(), QString("game3"));
    ASSERT_EQ(gamelistToUpdate.at(2).getName(), QString("game2"));

    ASSERT_EQ(spyRowsAboutToBeInserted.count(), 4);
    ASSERT_EQ(spyRowsInserted.count(), 4);
    ASSERT_EQ(spyRowsAboutToBeRemoved.count(), 1);
    ASSERT_EQ(spyRowsRemoved.count(), 1);
}

TEST(QGamelistTest, RowCountSameAsSize)
{
    lanty::QGamelist gamelist;

    lanty::Game* gameOne = new lanty::QGame();
    lanty::Game* gameTwo = new lanty::QGame();
    gameOne->setName("unique1");
    gameTwo->setName("unique2");

    gamelist.append(gameOne);
    gamelist.append(gameTwo);

    ASSERT_EQ(gamelist.rowCount(QModelIndex()), gamelist.size());
}

TEST(QGamelistTest, ReturnNoDataIfIndexOutOfBound)
{
    lanty::QGamelist gamelist;

    lanty::Game* gameOne = new lanty::QGame();
    lanty::Game* gameTwo = new lanty::QGame();
    gameOne->setName("unique1");
    gameTwo->setName("unique2");

    gamelist.append(gameOne);
    gamelist.append(gameTwo);

    QModelIndex index = gamelist.index(2);

    QVariant result = gamelist.data(index, Qt::DisplayRole);

    ASSERT_TRUE(result.isNull());
}

TEST(QGamelistTest, ReturnNoDataIfIndexIsInvalid)
{
    lanty::QGamelist gamelist;

    lanty::Game* gameOne = new lanty::QGame();
    lanty::Game* gameTwo = new lanty::QGame();
    gameOne->setName("unique1");
    gameTwo->setName("unique2");

    gamelist.append(gameOne);
    gamelist.append(gameTwo);

    QModelIndex index;

    QVariant result = gamelist.data(index, 0);

    ASSERT_TRUE(result.isNull());
}

TEST(QGamelistTest, ReturnNoDataIfRoleNotDisplayRole)
{
    lanty::QGamelist gamelist;

    lanty::Game* gameOne = new lanty::QGame();
    lanty::Game* gameTwo = new lanty::QGame();
    gameOne->setName("unique1");
    gameTwo->setName("unique2");

    gamelist.append(gameOne);
    gamelist.append(gameTwo);

    QModelIndex index = gamelist.index(0);

    QVariant result = gamelist.data(index, Qt::DisplayRole + 1);

    ASSERT_TRUE(result.isNull());
}

TEST(QGamelistTest, ReturnData)
{
    lanty::QGamelist gamelist;

    lanty::Game* gameOne = new lanty::QGame();
    lanty::Game* gameTwo = new lanty::QGame();
    gameOne->setName("unique1");
    gameTwo->setName("unique2");

    gamelist.append(gameOne);
    gamelist.append(gameTwo);

    QModelIndex index = gamelist.index(0);

    QVariant result = gamelist.data(index, Qt::DisplayRole);

    ASSERT_EQ(result.toString(), QString("unique1"));
}

TEST(QGamelistTest, SerializeToJSON)
{
    lanty::QGamelist gamelist;
    lanty::Game* game1 = new lanty::QGame();
    lanty::Game* game2 = new lanty::QGame();

    game1->setName("test");
    game1->setClientExecutableFilePath("wow.exe");
    game2->setName("test2");

    gamelist.append(game1);
    gamelist.append(game2);

    nlohmann::json json = gamelist.toJSON();

    ASSERT_EQ(json.size(), 2);
    ASSERT_TRUE(json.is_array());
    ASSERT_TRUE(json[0].is_object());
    ASSERT_TRUE(json[1].is_object());

    ASSERT_EQ(json[0], game1->toJSON());
    ASSERT_EQ(json[1], game2->toJSON());
}

TEST(QGamelistTest, SerializeToYAML)
{
    lanty::QGamelist gamelist;

    lanty::Game* game1 = new lanty::QGame();
    lanty::Game* game2 = new lanty::QGame();
    game1->setName("test");
    game1->setClientExecutableFilePath("wow.exe");
    game2->setName("test2");

    gamelist.append(game1);
    gamelist.append(game2);

    YAML::Node yaml = gamelist.toYAML();

    ASSERT_EQ(yaml.size(), 2);
    ASSERT_TRUE(yaml.IsSequence());
    ASSERT_TRUE(yaml[0].IsMap());
    ASSERT_TRUE(yaml[1].IsMap());
}
