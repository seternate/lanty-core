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

#include "game/GameClientLoaderTest.hpp"

#include <gtest/gtest.h>

#include "game/GameClientLoader.hpp"
#include "helper/QStringPrintHelper.hpp"

TEST_F(GameClientLoaderTest, LoadYAMLWithAllFields)
{
    lanty::GameClientLoader loader;
    lanty::GameClient client;

    client = loader.load(gameclientYAMLWithAllFields);

    ASSERT_EQ(client.getExecutableFilePath(), executableFilePath);
    ASSERT_EQ(client.getArgument(), argument);
    ASSERT_EQ(client.getConnectArgument(), connectArgument);
}

TEST_F(GameClientLoaderTest, LoadYAMLWithEmptyExecutableField)
{
    lanty::GameClientLoader loader;
    lanty::GameClient client;

    client = loader.load(gameclientYAMLWithMissingExecutable);

    ASSERT_TRUE(client.getExecutableFilePath().isEmpty());
    ASSERT_EQ(client.getArgument(), argument);
    ASSERT_EQ(client.getConnectArgument(), connectArgument);
}

TEST_F(GameClientLoaderTest, LoadYAMLWithOnlyExecutableField)
{
    lanty::GameClientLoader loader;
    lanty::GameClient client;

    client = loader.load(gameclientYAMLWithOnlyExecutable);

    ASSERT_EQ(client.getExecutableFilePath(), executableFilePath);
    ASSERT_TRUE(client.getArgument().isEmpty());
    ASSERT_TRUE(client.getConnectArgument().isEmpty());
}
