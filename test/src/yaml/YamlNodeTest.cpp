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

#include <yaml/YamlNodeTest.hpp>

#include <helper/QStringPrintHelper.hpp>
#include <yaml/IYamlNode.hpp>

TEST_F(YamlNodeTest, GetNodeWithKeyValue)
{
    std::shared_ptr<const IYamlNode> keyRoot = this->getNode("key");

    ASSERT_EQ(keyRoot->getQString(), QString("value"));
}

TEST_F(YamlNodeTest, GetNodeWithMap)
{
    std::shared_ptr<const IYamlNode> mapRoot = this->getNode("map");
    std::shared_ptr<const IYamlNode> keyMap = mapRoot->getNode("keymap");

    ASSERT_EQ(keyMap->getQString(), QString("valuemap"));
}

TEST_F(YamlNodeTest, GetNodeWithMapInMap)
{
    std::shared_ptr<const IYamlNode> mapRoot = this->getNode("map");
    std::shared_ptr<const IYamlNode> mapMap = mapRoot->getNode("mapmap");
    std::shared_ptr<const IYamlNode> keyMapMap = mapMap->getNode("keymapmap");

    ASSERT_EQ(keyMapMap->getQString(), QString("valuemapmap"));
}

TEST_F(YamlNodeTest, GetNodeWithSequence)
{
    std::shared_ptr<const IYamlNode> seqRoot = this->getNode("sequence");

    ASSERT_EQ(seqRoot->getQStringFromSequence(0), QString("valueseq1"));
    ASSERT_EQ(seqRoot->getQStringFromSequence(2), QString("valueseq2"));
}

TEST_F(YamlNodeTest, GetNodeWithMapInSequence)
{
    std::shared_ptr<const IYamlNode> seqRoot = this->getNode("sequence");
    std::shared_ptr<const IYamlNode> keySeq = seqRoot->getNode(1);

    ASSERT_EQ(keySeq->getQStringFromMap("keyseq"), QString("valuekeyseq"));
}

TEST_F(YamlNodeTest, GetNodeWithSequenceInSequence)
{
    std::shared_ptr<const IYamlNode> seqRoot = this->getNode("sequence");
    std::shared_ptr<const IYamlNode> seqSeq = seqRoot->getNode(3)->getNode("seqseq");

    ASSERT_EQ(seqSeq->getQStringFromSequence(0), QString("valueseqseq1"));
    ASSERT_EQ(seqSeq->getQStringFromSequence(1), QString("valueseqseq2"));
}
