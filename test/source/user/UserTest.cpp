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
#include "user/User.hpp"

TEST(UserTest, GetterUsername)
{
    QString username("seternate");
    lanty::User user("asd");
    QSignalSpy spy(&user, SIGNAL(usernameChanged(QString)));
    QSignalSpy spyChange(&user, SIGNAL(changed()));

    user.setUsername(username);

    ASSERT_EQ(user.getUsername(), username);
    ASSERT_EQ(1, spy.count());
    ASSERT_EQ(1, spyChange.count());
}

TEST(UserTest, GetterGamepath)
{
    QString gamepath("C:/Users/dummy test");
    lanty::User user("asd");
    QSignalSpy spy(&user, SIGNAL(gamepathChanged(QString)));
    QSignalSpy spyChange(&user, SIGNAL(changed()));

    user.setGamepath(gamepath);

    ASSERT_EQ(user.getGamepath(), gamepath);
    ASSERT_EQ(1, spy.count());
    ASSERT_EQ(1, spyChange.count());
}

TEST(UserTest, GetterResolution)
{
    quint32 resolutionX1 = 1920;
    quint32 resolutionY1 = 1080;
    quint32 resolutionX2 = 1280;
    quint32 resolutionY2 = 720;
    lanty::User user("asd");
    QSignalSpy spy(&user, SIGNAL(resolutionChanged(quint32, quint32)));
    QSignalSpy spyChange(&user, SIGNAL(changed()));

    user.setResolution(resolutionX1, resolutionY1);
    ASSERT_EQ(user.getResolutionX(), resolutionX1);
    ASSERT_EQ(user.getResolutionY(), resolutionY1);

    user.setResolutionX(resolutionX2);
    ASSERT_EQ(user.getResolutionX(), resolutionX2);
    ASSERT_EQ(user.getResolutionY(), resolutionY1);

    user.setResolutionY(resolutionY2);
    ASSERT_EQ(user.getResolutionX(), resolutionX2);
    ASSERT_EQ(user.getResolutionY(), resolutionY2);

    ASSERT_EQ(3, spy.count());
    ASSERT_EQ(3, spyChange.count());
}

TEST(UserTest, GetterIPAddress)
{
    QString ipAddress("127.0.0.1");
    lanty::User user("asd");
    QSignalSpy spy(&user, SIGNAL(ipAddressChanged(QString)));
    QSignalSpy spyChange(&user, SIGNAL(changed()));

    user.setIPAddress(ipAddress);

    ASSERT_EQ(user.getIPAddress(), ipAddress);
    ASSERT_EQ(1, spy.count());
    ASSERT_EQ(1, spyChange.count());
}
