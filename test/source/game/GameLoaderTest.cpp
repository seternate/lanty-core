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

#include "game/GameLoaderTest.hpp"

#include <gtest/gtest.h>

#include "game/GameLoader.hpp"
#include "helper/QStringPrintHelper.hpp"

TEST_F(GameLoaderTest, LoadYAMLWithAllFields)
{
    lanty::GameLoader loader;
    lanty::Game game;

    game = loader.load(gameWithAllFields);

    ASSERT_EQ(game.getName(), name);
    ASSERT_EQ(game.getArchiveFileName(), archive);
    ASSERT_EQ(game.getClient(), client);
    ASSERT_EQ(game.getServer(), server);
    ASSERT_EQ(game.getVersion(), version);
}

TEST_F(GameLoaderTest, LoadYAMLWithMissingFields)
{
    lanty::GameLoader loader;
    lanty::Game game;
    lanty::GameServer emptyServer;

    game = loader.load(gameWithMissingFields);

    ASSERT_EQ(game.getName(), name);
    ASSERT_EQ(game.getArchiveFileName(), archive);
    ASSERT_EQ(game.getClient(), client);
    ASSERT_EQ(game.getVersion(), version);
}

TEST_F(GameLoaderTest, LoadYAMLWithNoFields)
{
    lanty::GameLoader loader;
    lanty::Game game;
    lanty::Game emptyGame;

    game = loader.load(gameWithNoFields);

    ASSERT_EQ(game, emptyGame);
}
