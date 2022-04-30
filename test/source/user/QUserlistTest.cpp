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

#include "helper/QStringPrintHelper.hpp"
#include "user/QUser.hpp"
#include "user/QUserlist.hpp"

#include <QDebug>
#include <QSignalSpy>

TEST(QUserlistTest, DefaultConstructorCreatesEmptyList)
{
    lanty::QUserlist userlist;

    ASSERT_EQ(userlist.size(), 0);
}

TEST(QUserlistTest, ComparisonOperatorIfBothObjectsAreEqual)
{
    lanty::QUserlist userlistOne;
    lanty::QUserlist userlistTwo;

    lanty::QUser* userOne = new lanty::QUser();
    lanty::QUser* userTwo = new lanty::QUser();
    lanty::QUser* userThree = new lanty::QUser();
    lanty::QUser* userFour = new lanty::QUser();
    userOne->setUsername("unique1");
    userTwo->setUsername("unique2");
    userThree->setUsername("unique1");
    userFour->setUsername("unique2");

    userlistOne.append(userOne);
    userlistOne.append(userTwo);
    userlistTwo.append(userThree);
    userlistTwo.append(userFour);

    ASSERT_EQ(userlistOne, userlistTwo);
}

TEST(QUserlistTest, ComparisonOperatorIfBothObjectsAreUnEqual)
{
    lanty::QUserlist userlistOne;
    lanty::QUserlist userlistTwo;

    lanty::QUser* userOne = new lanty::QUser();
    lanty::QUser* userTwo = new lanty::QUser();
    lanty::QUser* userThree = new lanty::QUser();
    lanty::QUser* userFour = new lanty::QUser();
    userOne->setUsername("unique1");
    userTwo->setUsername("unique2");
    userThree->setUsername("unique3");
    userFour->setUsername("unique4");

    userlistOne.append(userOne);
    userlistOne.append(userTwo);
    userlistTwo.append(userThree);
    userlistTwo.append(userFour);

    ASSERT_NE(userlistOne, userlistTwo);
}

TEST(QUserlistTest, AccessOperator)
{
    lanty::QUserlist userlist;
    const lanty::QUserlist* userlistPtr = &userlist;

    lanty::QUser* user = new lanty::QUser();
    user->setUsername("user");

    userlist.append(user);

    ASSERT_EQ(userlist[0], *user);
    ASSERT_EQ((*userlistPtr)[0], *user);
}

TEST(QUserlistTest, AppendUniqueUsersToList)
{
    lanty::QUserlist userlist;
    QSignalSpy spyRowsAboutToBeInserted(&userlist, SIGNAL(rowsAboutToBeInserted(const QModelIndex&, int, int)));
    QSignalSpy spyRowsInserted(&userlist, SIGNAL(rowsInserted(const QModelIndex&, int, int)));

    lanty::QUser* userOne = new lanty::QUser();
    lanty::QUser* userTwo = new lanty::QUser();
    userOne->setUsername("unique1");
    userTwo->setUsername("unique2");

    ASSERT_TRUE(userlist.append(userOne));
    ASSERT_TRUE(userlist.append(userTwo));

    ASSERT_EQ(userlist.size(), 2);
    ASSERT_EQ(&userlist.at(0), userOne);
    ASSERT_EQ(&userlist.at(1), userTwo);

    ASSERT_EQ(spyRowsAboutToBeInserted.count(), 2);
    ASSERT_EQ(spyRowsInserted.count(), 2);
}

TEST(QUserlistTest, AppendNonUniqueUsersToList)
{
    lanty::QUserlist userlist;
    QSignalSpy spyRowsAboutToBeInserted(&userlist, SIGNAL(rowsAboutToBeInserted(const QModelIndex&, int, int)));
    QSignalSpy spyRowsInserted(&userlist, SIGNAL(rowsInserted(const QModelIndex&, int, int)));

    lanty::QUser* userOne = new lanty::QUser();
    lanty::QUser* userTwo = new lanty::QUser();
    userOne->setUsername("non-unique");
    userTwo->setUsername("non-unique");

    ASSERT_TRUE(userlist.append(userOne));
    ASSERT_FALSE(userlist.append(userTwo));

    ASSERT_EQ(userlist.size(), 1);
    ASSERT_EQ(&userlist.at(0), userOne);

    ASSERT_EQ(spyRowsAboutToBeInserted.count(), 1);
    ASSERT_EQ(spyRowsInserted.count(), 1);

    delete userTwo;
}

TEST(QUserlistTest, GamelistContainsUserAlready)
{
    lanty::QUserlist userlist;

    lanty::QUser* userOne = new lanty::QUser();
    lanty::QUser* userTwo = new lanty::QUser();
    userOne->setUsername("non-unique");
    userTwo->setUsername("non-unique");

    userlist.append(userOne);

    ASSERT_TRUE(userlist.contains(userTwo));
}

TEST(QUserlistTest, GamelistContainsUserNot)
{
    lanty::QUserlist userlist;

    lanty::QUser* userOne = new lanty::QUser();
    lanty::QUser* userTwo = new lanty::QUser();
    userOne->setUsername("unique1");
    userTwo->setUsername("unique2");

    userlist.append(userOne);

    ASSERT_FALSE(userlist.contains(userTwo));
}

TEST(QUserlistTest, SortUsersForUsernames)
{
    lanty::QUserlist userlist;
    QSignalSpy spyModelAboutToBeReset(&userlist, SIGNAL(modelAboutToBeReset(void)));
    QSignalSpy spyModelReset(&userlist, SIGNAL(modelReset(void)));

    lanty::QUser* user1 = new lanty::QUser();
    lanty::QUser* user2 = new lanty::QUser();
    user1->setUsername("aaaaa");
    user2->setUsername("hh");

    userlist.append(user2);
    userlist.append(user1);

    ASSERT_EQ(&userlist.at(0), user2);
    ASSERT_EQ(&userlist.at(1), user1);

    userlist.sortUsers();

    ASSERT_EQ(&userlist.at(0), user1);
    ASSERT_EQ(&userlist.at(1), user2);

    ASSERT_EQ(spyModelAboutToBeReset.count(), 1);
    ASSERT_EQ(spyModelReset.count(), 1);
}

TEST(QUserlistTest, UpdateWithAnotherList)
{
    lanty::QUserlist userlistToUpdate;
    QSignalSpy spyRowsAboutToBeInserted(&userlistToUpdate, SIGNAL(rowsAboutToBeInserted(const QModelIndex&, int, int)));
    QSignalSpy spyRowsInserted(&userlistToUpdate, SIGNAL(rowsInserted(const QModelIndex&, int, int)));
    QSignalSpy spyRowsAboutToBeRemoved(&userlistToUpdate, SIGNAL(rowsAboutToBeRemoved(const QModelIndex&, int, int)));
    QSignalSpy spyRowsRemoved(&userlistToUpdate, SIGNAL(rowsRemoved(const QModelIndex&, int, int)));

    {
        lanty::QUser* userOne = new lanty::QUser();
        userOne->setUsername("user1");
        lanty::QUser* userUnique = new lanty::QUser();
        userUnique->setUsername("unique");
        userlistToUpdate.append(userOne);
        userlistToUpdate.append(userUnique);

        lanty::QUser* userTwo = new lanty::QUser();
        userTwo->setUsername("user2");
        lanty::QUser* userThree = new lanty::QUser();
        userThree->setUsername("user3");
        lanty::QUser* userOneAsFour = new lanty::QUser();
        userOneAsFour->operator=(static_cast<lanty::User>(*userOne));
        lanty::QUserlist userlist;
        userlist.append(userThree);
        userlist.append(userTwo);
        userlist.append(userOneAsFour);

        ASSERT_TRUE(userlistToUpdate.update(userlist));
    }

    ASSERT_EQ(userlistToUpdate.size(), 3);
    ASSERT_EQ(userlistToUpdate.at(0).getUsername(), QString("user1"));
    ASSERT_EQ(userlistToUpdate.at(1).getUsername(), QString("user3"));
    ASSERT_EQ(userlistToUpdate.at(2).getUsername(), QString("user2"));

    ASSERT_EQ(spyRowsAboutToBeInserted.count(), 4);
    ASSERT_EQ(spyRowsInserted.count(), 4);
    ASSERT_EQ(spyRowsAboutToBeRemoved.count(), 1);
    ASSERT_EQ(spyRowsRemoved.count(), 1);
}

TEST(QUserlistTest, RowCountSameAsSize)
{
    lanty::QUserlist userlist;

    lanty::QUser* userOne = new lanty::QUser();
    lanty::QUser* userTwo = new lanty::QUser();
    userOne->setUsername("unique1");
    userTwo->setUsername("unique2");

    userlist.append(userOne);
    userlist.append(userTwo);

    ASSERT_EQ(userlist.rowCount(QModelIndex()), userlist.size());
}

TEST(QUserlistTest, ReturnNoDataIfIndexOutOfBound)
{
    lanty::QUserlist userlist;

    lanty::QUser* userOne = new lanty::QUser();
    lanty::QUser* userTwo = new lanty::QUser();
    userOne->setUsername("unique1");
    userTwo->setUsername("unique2");

    userlist.append(userOne);
    userlist.append(userTwo);

    QModelIndex index = userlist.index(2);

    QVariant result = userlist.data(index, Qt::DisplayRole);

    ASSERT_TRUE(result.isNull());
}

TEST(QUserlistTest, ReturnNoDataIfIndexIsInvalid)
{
    lanty::QUserlist userlist;

    lanty::QUser* userOne = new lanty::QUser();
    lanty::QUser* userTwo = new lanty::QUser();
    userOne->setUsername("unique1");
    userTwo->setUsername("unique2");

    userlist.append(userOne);
    userlist.append(userTwo);

    QModelIndex index;

    QVariant result = userlist.data(index, 0);

    ASSERT_TRUE(result.isNull());
}

TEST(QUserlistTest, ReturnNoDataIfRoleNotDisplayRole)
{
    lanty::QUserlist userlist;

    lanty::QUser* userOne = new lanty::QUser();
    lanty::QUser* userTwo = new lanty::QUser();
    userOne->setUsername("unique1");
    userTwo->setUsername("unique2");

    userlist.append(userOne);
    userlist.append(userTwo);

    QModelIndex index = userlist.index(0);

    QVariant result = userlist.data(index, Qt::DisplayRole + 1);

    ASSERT_TRUE(result.isNull());
}

TEST(QUserlistTest, ReturnData)
{
    lanty::QUserlist userlist;

    lanty::QUser* userOne = new lanty::QUser();
    lanty::QUser* userTwo = new lanty::QUser();
    userOne->setUsername("unique1");
    userTwo->setUsername("unique2");

    userlist.append(userOne);
    userlist.append(userTwo);

    QModelIndex index = userlist.index(0);

    QVariant result = userlist.data(index, Qt::DisplayRole);

    ASSERT_EQ(result.toString(), QString("unique1"));
}

TEST(QUserlistTest, SerializeToJSON)
{
    lanty::QUserlist userlist;
    lanty::QUser* user1 = new lanty::QUser();
    lanty::QUser* user2 = new lanty::QUser();

    user1->setUsername("test");
    user1->setGamepath("C:/test/games");
    user1->setResolution(1920, 1080);
    user1->setIPAddress("192.168.0.87");
    user2->setUsername("test2");
    user2->setGamepath("C:/test2/games");
    user2->setIPAddress("192.168.1.87");


    userlist.append(user1);
    userlist.append(user2);

    nlohmann::json json = userlist.toJSON();

    ASSERT_EQ(json.size(), 2);
    ASSERT_TRUE(json.is_array());
    ASSERT_TRUE(json[0].is_object());
    ASSERT_TRUE(json[1].is_object());

    ASSERT_EQ(json[0], user1->toJSON());
    ASSERT_EQ(json[1], user2->toJSON());
}

TEST(QUserlistTest, SerializeToYAML)
{
    lanty::QUserlist userlist;

    lanty::QUser* user1 = new lanty::QUser();
    lanty::QUser* user2 = new lanty::QUser();

    user1->setUsername("test");
    user1->setGamepath("C:/test/games");
    user1->setResolution(1920, 1080);
    user1->setIPAddress("192.168.0.87");
    user2->setUsername("test2");
    user2->setGamepath("C:/test2/games");
    user2->setIPAddress("192.168.1.87");

    userlist.append(user1);
    userlist.append(user2);

    YAML::Node yaml = userlist.toYAML();

    ASSERT_EQ(yaml.size(), 2);
    ASSERT_TRUE(yaml.IsSequence());
    ASSERT_TRUE(yaml[0].IsMap());
    ASSERT_TRUE(yaml[1].IsMap());
}
