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

#include "game/GameImage.hpp"
#include "helper/QStringPrintHelper.hpp"

TEST(GameImageTest, CoverFilenameWithDotInsideGamename)
{
    lanty::Game game("Counter Strike 1.6");
    lanty::GameImage image(game);

    ASSERT_EQ(image.coverFilename(), QString("counter_strike_1_6"));
}

TEST(GameImageTest, CoverFilenameWithDashInsideGamename)
{
    lanty::Game game("Warcraft 3 - Frozen Throne");
    lanty::GameImage image(game);

    ASSERT_EQ(image.coverFilename(), QString("warcraft_3_frozen_throne"));
}

TEST(GameImageTest, IconFilenameWithDotInsideGamename)
{
    lanty::Game game("Counter Strike 1.6");
    lanty::GameImage image(game);

    ASSERT_EQ(image.iconFilename(), QString("counter_strike_1_6_icon"));
}

TEST(GameImageTest, iconFilenameWithDashInsideGamename)
{
    lanty::Game game("Warcraft 3 - Frozen Throne");
    lanty::GameImage image(game);

    ASSERT_EQ(image.iconFilename(), QString("warcraft_3_frozen_throne_icon"));
}
