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

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "mock/MockUser.hpp"
#include "user/Userlist.hpp"

using ::testing::Return;

TEST(UserlistTest, AppendAndOperatorAccess)
{
    lanty::Userlist list;

    MockUser* user = new MockUser();

    list.append(user);

    ASSERT_EQ(&list[0], user);
}

TEST(UserlistTest, Access)
{
    lanty::Userlist list;
    MockUser* user = new MockUser();

    list.append(user);

    ASSERT_EQ(&list.at(0), user);
}

TEST(UserlistTest, RemoveAndSize)
{
    lanty::Userlist list;
    MockUser* user = new MockUser();

    list.append(user);

    ASSERT_EQ(list.size(), 1);

    list.remove(user);

    ASSERT_EQ(list.size(), 0);
}

TEST(UserlistTest, RowCount)
{
    lanty::Userlist list;

    MockUser* user1 = new MockUser();
    MockUser* user2 = new MockUser();
    MockUser* user3 = new MockUser();

    list.append(user1);
    list.append(user2);
    list.append(user3);

    ASSERT_EQ(list.rowCount(QModelIndex()), 3);
}

TEST(UserlistTest, Data)
{
    lanty::Userlist list;

    QString username("asdasd");
    MockUser* user = new MockUser();
    EXPECT_CALL(*user, getUsername()).WillRepeatedly(Return(username));

    list.append(user);

    ASSERT_EQ(list.data(list.index(0), Qt::DisplayRole).toString(), username);
}
