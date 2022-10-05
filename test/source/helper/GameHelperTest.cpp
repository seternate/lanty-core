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

#include <gtest/gtest.h>

#include "helper/GameHelper.hpp"
#include "helper/GameHelperTest.hpp"
#include "helper/QStringPrintHelper.hpp"
#include "mock/MockGame.hpp"
#include "mock/MockQDir.hpp"

using ::testing::_;
using ::testing::Exactly;
using ::testing::Return;

TEST_F(GameHelperTest, ConvertNameToCoverImageName)
{
    EXPECT_CALL(cod2, getName()).WillOnce(Return(QString("Call of Duty 2")));
    EXPECT_CALL(wc3, getName()).WillOnce(Return(QString("Warcraft 3 - Frozen Throne")));
    EXPECT_CALL(cs16, getName()).WillOnce(Return(QString("Counter Strike 1.6")));
    EXPECT_CALL(cod4, getName()).WillOnce(Return(QString("Call of Duty 4")));

    QString cod2CoverName = gamehelper.formatNameToCoverImageFileName(cod2);
    ASSERT_EQ(cod2CoverName, QString("call_of_duty_2"));

    QString wc3CoverName = gamehelper.formatNameToCoverImageFileName(wc3);
    ASSERT_EQ(wc3CoverName, QString("warcraft_3_frozen_throne"));

    QString cs16CoverName = gamehelper.formatNameToCoverImageFileName(cs16);
    ASSERT_EQ(cs16CoverName, QString("counter_strike_1_6"));

    QString cod4CoverName = gamehelper.formatNameToCoverImageFileName(cod4);
    ASSERT_EQ(cod4CoverName, QString("call_of_duty_4"));
}

TEST_F(GameHelperTest, ConvertNameToIconImageName)
{
    EXPECT_CALL(cod2, getName()).WillOnce(Return(QString("Call of Duty 2")));
    EXPECT_CALL(wc3, getName()).WillOnce(Return(QString("Warcraft 3 - Frozen Throne")));
    EXPECT_CALL(cs16, getName()).WillOnce(Return(QString("Counter Strike 1.6")));
    EXPECT_CALL(cod4, getName()).WillOnce(Return(QString("Call of Duty 4")));

    QString cod2IconName = gamehelper.formatNameToIconImageFileName(cod2);
    ASSERT_EQ(cod2IconName, QString("call_of_duty_2_icon"));

    QString wc3IconName = gamehelper.formatNameToIconImageFileName(wc3);
    ASSERT_EQ(wc3IconName, QString("warcraft_3_frozen_throne_icon"));

    QString cs16IconName = gamehelper.formatNameToIconImageFileName(cs16);
    ASSERT_EQ(cs16IconName, QString("counter_strike_1_6_icon"));

    QString cod4IconName = gamehelper.formatNameToIconImageFileName(cod4);
    ASSERT_EQ(cod4IconName, QString("call_of_duty_4_icon"));
}

TEST_F(GameHelperTest, GetIconPathFromDirectory)
{
    EXPECT_CALL(qdir, entryList(_, _, _)).Times(Exactly(4)).WillRepeatedly(Return(entrylist));
    EXPECT_CALL(qdir, absoluteFilePath(_)).Times(4).WillRepeatedly([&](const QString& file) {
        return (absoluteDirPath + file);
    });

    EXPECT_CALL(cod2, getName()).WillRepeatedly(Return(QString("Call of Duty 2")));
    EXPECT_CALL(wc3, getName()).WillRepeatedly(Return(QString("Warcraft 3 - Frozen Throne")));
    EXPECT_CALL(cs16, getName()).WillRepeatedly(Return(QString("Counter Strike 1.6")));
    EXPECT_CALL(cod4, getName()).WillRepeatedly(Return(QString("Call of Duty 4")));

    ASSERT_EQ(gamehelper.getIconImagePathFromDirectory(cod2, qdir), absoluteDirPath + "call_of_duty_2_icon.png");
    ASSERT_EQ(gamehelper.getIconImagePathFromDirectory(wc3, qdir), absoluteDirPath + "warcraft_3_frozen_throne_icon.jpg");
    ASSERT_EQ(gamehelper.getIconImagePathFromDirectory(cs16, qdir), absoluteDirPath + "counter_strike_1_6_icon.jpeg");
    ASSERT_EQ(gamehelper.getIconImagePathFromDirectory(cod4, qdir), absoluteDirPath + "call_of_duty_4_icon.bmp");
}

TEST_F(GameHelperTest, GetCoverPathFromDirectory)
{
    EXPECT_CALL(qdir, entryList(_, _, _)).Times(Exactly(4)).WillRepeatedly(Return(entrylist));
    EXPECT_CALL(qdir, absoluteFilePath(_)).Times(4).WillRepeatedly([&](const QString& file) {
        return (absoluteDirPath + file);
    });

    EXPECT_CALL(cod2, getName()).WillRepeatedly(Return(QString("Call of Duty 2")));
    EXPECT_CALL(wc3, getName()).WillRepeatedly(Return(QString("Warcraft 3 - Frozen Throne")));
    EXPECT_CALL(cs16, getName()).WillRepeatedly(Return(QString("Counter Strike 1.6")));
    EXPECT_CALL(cod4, getName()).WillRepeatedly(Return(QString("Call of Duty 4")));

    ASSERT_EQ(gamehelper.getCoverImagePathFromDirectory(cod2, qdir), absoluteDirPath + "call_of_duty_2.png");
    ASSERT_EQ(gamehelper.getCoverImagePathFromDirectory(wc3, qdir), absoluteDirPath + "warcraft_3_frozen_throne.jpg");
    ASSERT_EQ(gamehelper.getCoverImagePathFromDirectory(cs16, qdir), absoluteDirPath + "counter_strike_1_6.jpeg");
    ASSERT_EQ(gamehelper.getCoverImagePathFromDirectory(cod4, qdir), absoluteDirPath + "call_of_duty_4.bmp");
}
