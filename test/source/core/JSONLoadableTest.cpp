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

#include "core/JSONLoadableTest.hpp"

#include <gtest/gtest.h>

TEST_F(JSONLoadableTest, loadFieldAsQStringKeyDoesNotExistReturnEmptyQString)
{
    QString emptyValue = this->loadFieldAsQString(emptyJSON, "not_existing_key");

    ASSERT_TRUE(emptyValue.isEmpty() == true);
}

TEST_F(JSONLoadableTest, loadFieldAsQStringKeyDoesExistReturnValue)
{
    QString value = this->loadFieldAsQString(json, "existing_key_string");

    ASSERT_EQ(value, "value");
}

TEST_F(JSONLoadableTest, loadFieldAsIntegerKeyDoesNotExistsReturnZero)
{
    qint64 zeroValue = this->loadFieldAsInteger(emptyJSON, "not_existing_key");

    ASSERT_EQ(zeroValue, 0);
}

TEST_F(JSONLoadableTest, loadFieldAsIntegerKeyDoesExistReturnValue)
{
    qint64 value = this->loadFieldAsInteger(json, "existing_key_integer");

    ASSERT_EQ(value, 99);
}
