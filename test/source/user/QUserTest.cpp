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
#include <QSignalSpy>

#include "helper/QStringPrintHelper.hpp"
#include "user/QUser.hpp"

TEST(QUserTest, ComparisonOperatorIfBothObjectsAreEqual)
{
    lanty::QUser userOne;
    userOne.setUsername("seternate");
    lanty::QUser userTwo;
    userTwo.setUsername("seternate");

    ASSERT_EQ(userOne, userTwo);
}

TEST(QUserTest, ComparisonOperatorIfBothObjectsAreUnEqual)
{
    lanty::QUser userOne;
    userOne.setUsername("seternate");
    lanty::QUser userTwo;

    ASSERT_NE(userOne, userTwo);
}

TEST(QUserTest, LessThanOperator)
{
    lanty::QUser userOne("seternate");
    lanty::QUser userTwo("Awes0me");

    ASSERT_LT(userTwo, userOne);
}

TEST(QUserTest, CopyConstructorAndOperatorForGames)
{
    lanty::User user;
    user.setUsername("seternate");

    lanty::QUser constructor(user);
    ASSERT_EQ(constructor, user);

    lanty::QUser copyOperator;
    copyOperator = user;
    ASSERT_EQ(copyOperator, user);
}

TEST(QUserTest, ChangedSignal)
{
    lanty::QUser user;
    QSignalSpy spy(&user, SIGNAL(changed(void)));

    user.setUsername("seternate");
    ASSERT_EQ(spy.count(), 1);
    user.setGamepath("C:/games");
    ASSERT_EQ(spy.count(), 2);
    user.setResolution(1920, 1080);
    ASSERT_EQ(spy.count(), 3);
    user.setResolutionX(100);
    ASSERT_EQ(spy.count(), 4);
    user.setResolutionY(100);
    ASSERT_EQ(spy.count(), 5);
    user.setIPAddress("192.168.0.87");
    ASSERT_EQ(spy.count(), 6);
}

TEST(QUserTest, UsernameChangedSignal)
{
    lanty::QUser user;
    QSignalSpy spy(&user, SIGNAL(usernameChanged(const QString&)));

    user.setUsername("seternate");

    ASSERT_EQ(spy.count(), 1);
}

TEST(QUserTest, GamepathChangedSignal)
{
    lanty::QUser user;
    QSignalSpy spy(&user, SIGNAL(gamepathChanged(const QString&)));

    user.setGamepath("C:/games");

    ASSERT_EQ(spy.count(), 1);
}

TEST(QUserTest, ResolutionChangedSignal)
{
    lanty::QUser user;
    QSignalSpy spy(&user, SIGNAL(resolutionChanged(const quint64, const quint64)));

    user.setResolution(1920, 1080);
    user.setResolutionX(100);
    user.setResolutionY(100);

    ASSERT_EQ(spy.count(), 3);
}

TEST(QUserTest, IPAddressChangedSignal)
{
    lanty::QUser user;
    QSignalSpy spy(&user, SIGNAL(ipaddressChanged(const QString&)));

    user.setIPAddress("192.168.0.87");

    ASSERT_EQ(spy.count(), 1);
}
