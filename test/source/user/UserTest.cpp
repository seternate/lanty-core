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
#include "user/User.hpp"

TEST(UserTest, FieldsShouldBeEmptyAfterCallingDefaultConstructor)
{
    lanty::User user;

    ASSERT_TRUE(user.getUsername().isEmpty());
    ASSERT_TRUE(user.getGamepath().isEmpty());
    ASSERT_EQ(user.getResolutionX(), 0);
    ASSERT_EQ(user.getResolutionY(), 0);
    ASSERT_TRUE(user.getIPAddress().isNull());
}

TEST(UserTest, GetterSetterTest)
{
    lanty::User user;

    QString username("seternate");
    user.setUsername(username);
    ASSERT_EQ(user.getUsername(), username);

    QString gamepath("C:/Users/dummy test");
    user.setGamepath(gamepath);
    ASSERT_EQ(user.getGamepath(), gamepath);

    quint32 resolutionX1 = 1920;
    quint32 resolutionY1 = 1080;
    quint32 resolutionX2 = 1280;
    quint32 resolutionY2 = 720;
    user.setResolution(resolutionX1, resolutionY1);
    ASSERT_EQ(user.getResolutionX(), resolutionX1);
    ASSERT_EQ(user.getResolutionY(), resolutionY1);
    user.setResolutionX(resolutionX2);
    ASSERT_EQ(user.getResolutionX(), resolutionX2);
    ASSERT_EQ(user.getResolutionY(), resolutionY1);
    user.setResolutionY(resolutionY2);
    ASSERT_EQ(user.getResolutionX(), resolutionX2);
    ASSERT_EQ(user.getResolutionY(), resolutionY2);

    QString ipAddress("192.168.0.14");
    user.setIPAddress(ipAddress);

    ASSERT_EQ(user.getIPAddress().toString(), ipAddress);
}

TEST(UserTest, ComparisonOperatorIfBothObjectsAreEqual)
{
    lanty::User userOne("seternate", "C:\\games");
    lanty::User userTwo("seternate", "C:\\games");

    ASSERT_EQ(userOne, userTwo);
}

TEST(UserTest, ComparisonOperatorIfBothObjectsAreUnEqual)
{
    lanty::User userOne("seternate", "C:\\games");
    lanty::User userTwo("poisness", "C:\\lan");

    ASSERT_NE(userOne, userTwo);
}

TEST(UserTest, CopyConstructorAndOperator)
{
    lanty::User user("seternate", "C:\\games");

    lanty::User constructor(user);
    ASSERT_EQ(user, constructor);

    lanty::User copyOperator;
    copyOperator = user;
    ASSERT_EQ(user, copyOperator);
}

TEST(UserTest, SerializeToJSON)
{
    lanty::User user("seternate", "C:\\games", "192.168.0.15");
    user.setResolution(1920, 1080);

    nlohmann::json json = user.toJSON();

    EXPECT_EQ(json.size(), 4);
    ASSERT_TRUE(json.contains("username"));
    ASSERT_TRUE(json.contains("gamepath"));
    ASSERT_TRUE(json.contains("resolution"));
    ASSERT_TRUE(json["resolution"].contains("x"));
    ASSERT_TRUE(json["resolution"].contains("y"));
    ASSERT_TRUE(json.contains("ip-address"));

    ASSERT_EQ(json[lanty::User::USERNAME_SERIALIZER_KEY], "seternate");
    ASSERT_EQ(json[lanty::User::GAMEPATH_SERIALIZER_KEY], "C:\\games");
    ASSERT_EQ(json[lanty::User::RESOLUTION_SERIALIZER_KEY][lanty::User::RESOLUTION_X_SERIALIZER_KEY], 1920);
    ASSERT_EQ(json[lanty::User::RESOLUTION_SERIALIZER_KEY][lanty::User::RESOLUTION_Y_SERIALIZER_KEY], 1080);
    ASSERT_EQ(json[lanty::User::IPADDRESS_SERIALIZER_KEY], "192.168.0.15");
}

TEST(UserTest, DoNotShowEmptyFieldsAtJSON)
{
    lanty::User user;

    nlohmann::json json = user.toJSON();

    ASSERT_TRUE(json.empty());
    ASSERT_FALSE(json.contains("username"));
    ASSERT_FALSE(json.contains("gamepath"));
    ASSERT_FALSE(json.contains("resolution"));
    ASSERT_FALSE(json["resolution"].contains("x"));
    ASSERT_FALSE(json["resolution"].contains("y"));
    ASSERT_FALSE(json.contains("ip-address"));
}
