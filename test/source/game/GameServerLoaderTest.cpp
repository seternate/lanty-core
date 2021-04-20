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

#include "game/GameServerLoaderTest.hpp"

#include <gtest/gtest.h>

#include "game/GameServerLoader.hpp"
#include "helper/QStringPrintHelper.hpp"

TEST_F(GameServerLoaderTest, LoadYAMLWithAllFields)
{
    lanty::GameServerLoader loader;
    lanty::GameServer server;

    server = loader.load(gameserverYAMLWithAllFields);

    ASSERT_EQ(server.getExecutableFilePath(), executableFilePath);
    ASSERT_EQ(server.getArgument(), argument);
}

TEST_F(GameServerLoaderTest, LoadYAMLWithEmptyExecutableField)
{
    lanty::GameServerLoader loader;
    lanty::GameServer server;

    server = loader.load(gameserverYAMLWithMissingExecutable);

    ASSERT_TRUE(server.getExecutableFilePath().isEmpty());
    ASSERT_EQ(server.getArgument(), argument);
}

TEST_F(GameServerLoaderTest, LoadYAMLWithOnlyExecutableField)
{
    lanty::GameServerLoader loader;
    lanty::GameServer server;

    server = loader.load(gameserverYAMLWithOnlyExecutable);

    ASSERT_EQ(server.getExecutableFilePath(), executableFilePath);
    ASSERT_TRUE(server.getArgument().isEmpty());
}
