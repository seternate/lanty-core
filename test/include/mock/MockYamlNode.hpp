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

#ifndef MOCK_MOCKYAMLNODE_HPP
#define MOCK_MOCKYAMLNODE_HPP

#include <gmock/gmock.h>

#include "yaml/YamlNode.hpp"

class MockYamlNode : public lanty::YamlNode
{
public:
    MOCK_METHOD(QString, getFileName, (), (const, override));
    MOCK_METHOD(const lanty::YamlNode*, getNode, (const QString &key), (const, override));
    MOCK_METHOD(const lanty::YamlNode*, getNode, (const int index), (const, override));
    MOCK_METHOD(lanty::YamlNode*, getNode, (const QString &key), (override));
    MOCK_METHOD(lanty::YamlNode*, getNode, (const int index), (override));
    MOCK_METHOD(QString, getQStringFromMap, (const QString &key), (const, override));
    MOCK_METHOD(QString, getQStringFromSequence, (const int index), (const, override));
    MOCK_METHOD(QString, getQString,(), (const, override));
    MOCK_METHOD(double, getDoubleFromMap, (const QString &key), (const, override));
    MOCK_METHOD(double, getDoubleFromSequence, (const int index), (const, override));
    MOCK_METHOD(double, getDouble, (), (const, override));
    MOCK_METHOD(int, getSize, (), (const, override));
    MOCK_METHOD(bool, isDefined, (const QString &key), (const, override));
    MOCK_METHOD(bool, isNull, (const QString &key), (const, override));
    MOCK_METHOD(bool, isValue, (const QString &key), (const, override));
    MOCK_METHOD(bool, isSequence, (const QString &key), (const, override));
    MOCK_METHOD(bool, isMap, (const QString &key), (const, override));
    MOCK_METHOD(bool, isNull, (), (const, override));
    MOCK_METHOD(bool, isValue, (), (const, override));
    MOCK_METHOD(bool, isSequence, (), (const, override));
    MOCK_METHOD(bool, isMap, (), (const, override));
    MOCK_METHOD(bool, loadFromFile, (const QString &absoluteFilePath), (override));
};

#endif /* MOCK_MOCKYAMLNODE_HPP */
