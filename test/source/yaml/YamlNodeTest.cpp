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

#include "yaml/YamlNodeTest.hpp"

#include "helper/QStringPrintHelper.hpp"
#include "yaml/YamlNode.hpp"

TEST_F(YamlNodeTest, GetNodeWithKeyValue)
{
    YamlNode* keyRoot = this->getNode("key");

    ASSERT_EQ(keyRoot->getQString(), QString("value"));
}

TEST_F(YamlNodeTest, GetNodeWithMap)
{
    YamlNode* mapRoot = this->getNode("map");
    YamlNode* keyMap = mapRoot->getNode("keymap");

    ASSERT_EQ(keyMap->getQString(), QString("valuemap"));
}

TEST_F(YamlNodeTest, GetNodeWithMapInMap)
{
    YamlNode* mapRoot = this->getNode("map");
    YamlNode* mapMap = mapRoot->getNode("mapmap");
    YamlNode* keyMapMap = mapMap->getNode("keymapmap");

    ASSERT_EQ(keyMapMap->getQString(), QString("valuemapmap"));
}

TEST_F(YamlNodeTest, GetNodeWithSequence)
{
    YamlNode* seqRoot = this->getNode("sequence");

    ASSERT_EQ(seqRoot->getQStringFromSequence(0), QString("valueseq1"));
    ASSERT_EQ(seqRoot->getQStringFromSequence(2), QString("valueseq2"));
}

TEST_F(YamlNodeTest, GetNodeWithMapInSequence)
{
    YamlNode* seqRoot = this->getNode("sequence");
    YamlNode* keySeq = seqRoot->getNode(1);

    ASSERT_EQ(keySeq->getQStringFromMap("keyseq"), QString("valuekeyseq"));
}

TEST_F(YamlNodeTest, GetNodeWithSequenceInSequence)
{
    YamlNode* seqRoot = this->getNode("sequence");
    YamlNode* seqSeq = seqRoot->getNode(3)->getNode("seqseq");

    ASSERT_EQ(seqSeq->getQStringFromSequence(0), QString("valueseqseq1"));
    ASSERT_EQ(seqSeq->getQStringFromSequence(1), QString("valueseqseq2"));
}

TEST_F(YamlNodeTest, GetNotExistingNode)
{
    YamlNode* keyRoot = this->getNode("notexisting");

    ASSERT_EQ(keyRoot, nullptr);
}

TEST_F(YamlNodeTest, GetNotExistingQString)
{
    QString notExistingMap = this->getQStringFromMap("notexisting");
    QString notExistingSeq = this->getQStringFromSequence(3);

    ASSERT_EQ(notExistingMap, QString(""));
    ASSERT_EQ(notExistingSeq, QString(""));
}

TEST_F(YamlNodeTest, GetNotExistingDouble)
{
    double notExistinMap = this->getDoubleFromMap("notexisting");
    double notExistinSeq = this->getDoubleFromSequence(4);

    ASSERT_EQ(notExistinMap, 0.0);
    ASSERT_EQ(notExistinSeq, 0.0);
}

TEST_F(YamlNodeTest, SetKeyValueString)
{
    YamlNode* keyRoot = this->getNode("key");
    this->setString("key", "test");
    ASSERT_EQ(keyRoot->getQString(), QString("test"));
    keyRoot->setString("anothertest");
    ASSERT_EQ(keyRoot->getQString(), QString("anothertest"));

    YamlNode* map = this->getNode("map");
    YamlNode* mapKeyMap = map->getNode("keymap");
    map->setString("keymap", "test");
    ASSERT_EQ(mapKeyMap->getQString(), QString("test"));
    mapKeyMap->setString("anothertest");
    ASSERT_EQ(mapKeyMap->getQString(), QString("anothertest"));

    YamlNode* sequence = this->getNode("sequence");
    YamlNode* keyseq = sequence->getNode(1);
    YamlNode* seqseq = sequence->getNode(3);
    sequence->setString(0, "test");
    ASSERT_EQ(sequence->getQStringFromSequence(0), QString("test"));
    keyseq->setString("keyseq", "test");
    ASSERT_EQ(keyseq->getQStringFromMap("keyseq"), QString("test"));
    seqseq->setString(0, "test");
    ASSERT_EQ(seqseq->getQStringFromSequence(0), QString("test"));
}

TEST_F(YamlNodeTest, SetKeyValueDouble)
{
    YamlNode* keyRoot = this->getNode("key");
    this->setDouble("key", 0);
    ASSERT_EQ(keyRoot->getDouble(), 0);
    keyRoot->setDouble(1);
    ASSERT_EQ(keyRoot->getDouble(), 1);

    YamlNode* map = this->getNode("map");
    YamlNode* mapKeyMap = map->getNode("keymap");
    map->setDouble("keymap", 0);
    ASSERT_EQ(mapKeyMap->getDouble(), 0);
    mapKeyMap->setDouble(1);
    ASSERT_EQ(mapKeyMap->getDouble(), 1);

    YamlNode* sequence = this->getNode("sequence");
    YamlNode* keyseq = sequence->getNode(1);
    YamlNode* seqseq = sequence->getNode(3);
    sequence->setDouble(0, 0);
    ASSERT_EQ(sequence->getDoubleFromSequence(0), 0);
    keyseq->setDouble("keyseq", 0);
    ASSERT_EQ(keyseq->getDoubleFromMap("keyseq"), 0);
    seqseq->setDouble(0, 0);
    ASSERT_EQ(seqseq->getDoubleFromSequence(0), 0);
}
