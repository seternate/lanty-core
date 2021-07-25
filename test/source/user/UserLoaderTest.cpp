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

#include "user/UserLoaderTest.hpp"

#include <gtest/gtest.h>

#include "helper/QStringPrintHelper.hpp"
#include "user/UserLoader.hpp"

TEST_F(UserLoaderTest, LoadYAMLWithAllFields)
{
    lanty::UserLoader loader;
    lanty::User user;

    user = loader.load(userYAMLWithAllFields);

    ASSERT_EQ(user.getUsername(), username);
    ASSERT_EQ(user.getGamepath(), gamepath);
    ASSERT_EQ(user.getResolutionX(), resolutionX);
    ASSERT_EQ(user.getResolutionY(), resolutionY);
    ASSERT_EQ(user.getIPAddress().toString(), ipAddress);
}

TEST_F(UserLoaderTest, LoadYAMLWithMissingIPAddress)
{
    lanty::UserLoader loader;
    lanty::User user;

    user = loader.load(userYAMLWithMissingIPAddress);

    ASSERT_EQ(user.getUsername(), username);
    ASSERT_EQ(user.getGamepath(), gamepath);
    ASSERT_EQ(user.getResolutionX(), resolutionX);
    ASSERT_EQ(user.getResolutionY(), resolutionY);
    ASSERT_TRUE(user.getIPAddress().isNull());
}

TEST_F(UserLoaderTest, LoadYAMLWithOnlyUsername)
{
    lanty::UserLoader loader;
    lanty::User user;

    user = loader.load(userYAMLWithOnlyUsername);

    ASSERT_EQ(user.getUsername(), username);
    ASSERT_TRUE(user.getGamepath().isEmpty());
    ASSERT_EQ(user.getResolutionX(), 0);
    ASSERT_EQ(user.getResolutionY(), 0);
    ASSERT_TRUE(user.getIPAddress().isNull());
}

TEST_F(UserLoaderTest, LoadJSONWithAllFields)
{
    lanty::UserLoader loader;
    lanty::User user;

    user = loader.load(userJSONWithAllFields);

    ASSERT_EQ(user.getUsername(), username);
    ASSERT_EQ(user.getGamepath(), gamepath);
    ASSERT_EQ(user.getResolutionX(), resolutionX);
    ASSERT_EQ(user.getResolutionY(), resolutionY);
    ASSERT_EQ(user.getIPAddress().toString(), ipAddress);
}

TEST_F(UserLoaderTest, LoadJSONWithMissingIPAddress)
{
    lanty::UserLoader loader;
    lanty::User user;

    user = loader.load(userJSONWithMissingIPAddress);

    ASSERT_EQ(user.getUsername(), username);
    ASSERT_EQ(user.getGamepath(), gamepath);
    ASSERT_EQ(user.getResolutionX(), resolutionX);
    ASSERT_EQ(user.getResolutionY(), resolutionY);
    ASSERT_TRUE(user.getIPAddress().isNull());
}

TEST_F(UserLoaderTest, LoadJSONWithOnlyUsername)
{
    lanty::UserLoader loader;
    lanty::User user;

    user = loader.load(userJSONWithOnlyUsername);

    ASSERT_EQ(user.getUsername(), username);
    ASSERT_TRUE(user.getGamepath().isEmpty());
    ASSERT_EQ(user.getResolutionX(), 0);
    ASSERT_EQ(user.getResolutionY(), 0);
    ASSERT_TRUE(user.getIPAddress().isNull());
}
