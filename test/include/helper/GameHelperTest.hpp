/* Copyright <2020> <Levin Jeck>
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

#ifndef HELPER_GAMEHELPERTEST_HPP
#define HELPER_GAMEHELPERTEST_HPP

#include <gtest/gtest.h>

#include "helper/GameHelper.hpp"
#include "mock/MockGame.hpp"
#include "mock/MockQDir.hpp"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

class GameHelperTest : public ::testing::Test
{
public:
    GameHelperTest(void) : gamehelper(),
                           cod2(),
                           wc3(),
                           cs16(),
                           cod4(),
                           qdir(),
                           entrylist(),
                           absoluteDirPath("C:/Users/Program/lanty/")
    {
        entrylist.append("call_of_duty_2.png");
        entrylist.append("call_of_duty_2_icon.png");
        entrylist.append("warcraft_3_frozen_throne.jpg");
        entrylist.append("warcraft_3_frozen_throne_icon.jpg");
        entrylist.append("counter_strike_1_6.jpeg");
        entrylist.append("counter_strike_1_6_icon.jpeg");
        entrylist.append("call_of_duty_4.bmp");
        entrylist.append("call_of_duty_4_icon.bmp");
        entrylist.append("dummy.png");
        entrylist.append("dummy_icon.jpg");
        entrylist.append("asdsbdgb.jpg");
    };

protected:
    lanty::GameHelper gamehelper;
    MockGame cod2;
    MockGame wc3;
    MockGame cs16;
    MockGame cod4;
    MockQDir qdir;
    QStringList entrylist;
    QString absoluteDirPath;
};

#endif /* HELPER_GAMEHELPERTEST_HPP */
