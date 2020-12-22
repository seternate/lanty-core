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

#include "yaml/YamlNode.hpp"

#include <QFile>
#include <QFileInfo>
#include <string>

namespace lanty
{

template<>
QString YamlNode::getValue<QString>(const YAML::Node &yamlNodeToReturn) const
{
    QString result("");

    if(yamlNodeToReturn.IsDefined())
    {
        std::string value = yamlNodeToReturn.as<std::string>();
        result = QString::fromStdString(value);
    }

    return result;
}

template<>
double YamlNode::getValue<double>(const YAML::Node &yamlNodeToReturn) const
{
    double result = 0.0;

    if(yamlNodeToReturn.IsDefined())
    {
        double value = yamlNodeToReturn.as<double>();
        result = value;
    }

    return result;
}


YamlNode::YamlNode(const QString &absoluteFilePath) : node(), absoluteFilePath(absoluteFilePath), childNodes()
{
    this->node = YAML::LoadFile(absoluteFilePath.toStdString());
}


QString YamlNode::getFileName() const
{
    QFile file(this->absoluteFilePath);
    QFileInfo fileInfo(file);

    return fileInfo.fileName();
}

std::shared_ptr<const YamlNode> YamlNode::getNode(const QString &key) const
{
    YAML::Node yamlNodeToReturn = this->node[key.toStdString()];
    return this->getNode(yamlNodeToReturn);
}

std::shared_ptr<const YamlNode> YamlNode::getNode(const int index) const
{
    YAML::Node yamlNodeToReturn = this->node[index];
    return this->getNode(yamlNodeToReturn);
}

std::shared_ptr<YamlNode> YamlNode::getNode(const QString &key)
{
    YAML::Node yamlNodeToReturn = this->node[key.toStdString()];
    return this->getNode(yamlNodeToReturn);
}

std::shared_ptr<YamlNode> YamlNode::getNode(const int index)
{
    YAML::Node yamlNodeToReturn = this->node[index];
    return this->getNode(yamlNodeToReturn);
}

QString YamlNode::getQStringFromMap(const QString &key) const
{
    YAML::Node yamlNodeToReturn = this->node[key.toStdString()];
    return this->getValue<QString>(yamlNodeToReturn);
}

QString YamlNode::getQStringFromSequence(const int index) const
{
    YAML::Node yamlNodeToReturn = this->node[index];
    return this->getValue<QString>(yamlNodeToReturn);
}

QString YamlNode::getQString() const
{
    return this->getValue<QString>(this->node);
}

double YamlNode::getDoubleFromMap(const QString &key) const
{
    YAML::Node yamlNodeToReturn = this->node[key.toStdString()];
    return this->getValue<double>(yamlNodeToReturn);
}

double YamlNode::getDoubleFromSequence(const int index) const
{
    YAML::Node yamlNodeToReturn = this->node[index];
    return this->getValue<double>(yamlNodeToReturn);
}

double YamlNode::getDouble(void) const
{
    return this->getValue<double>(this->node);
}

int YamlNode::getSize() const
{
    return this->node.size();
}

bool YamlNode::isDefined(const QString &key) const
{
    return this->node[key.toStdString()].IsDefined();
}

bool YamlNode::isNull(const QString &key) const
{
    return this->node[key.toStdString()].IsNull();
}

bool YamlNode::isValue(const QString &key) const
{
    return this->node[key.toStdString()].IsScalar();
}

bool YamlNode::isSequence(const QString &key) const
{
    return this->node[key.toStdString()].IsSequence();
}

bool YamlNode::isMap(const QString &key) const
{
    return this->node[key.toStdString()].IsMap();
}

bool YamlNode::isNull() const
{
    return this->node.IsNull();
}

bool YamlNode::isValue() const
{
    return this->node.IsScalar();
}

bool YamlNode::isSequence() const
{
    return this->node.IsSequence();
}

bool YamlNode::isMap() const
{
    return this->node.IsMap();
}


bool YamlNode::loadFromFile(const QString &absoluteFilePath)
{
    this->absoluteFilePath = absoluteFilePath;
    this->node = YAML::LoadFile(absoluteFilePath.toStdString());
    this->childNodes = std::vector<std::shared_ptr<YamlNode>>();
    return true;
}


std::shared_ptr<YamlNode> YamlNode::getNode(YAML::Node &yamlNodeToReturn) const
{
    std::shared_ptr<YamlNode> result(nullptr);

    if(yamlNodeToReturn.IsDefined() && !yamlNodeToReturn.IsNull())
    {
        for(std::shared_ptr<YamlNode> childNode : this->childNodes)
        {
            if(childNode->node == yamlNodeToReturn)
            {
                result = childNode;
                break;
            }
        }

        if(result == nullptr)
        {
            std::shared_ptr<YamlNode> yamlChildNode(new YamlNode());
            yamlChildNode->node = yamlNodeToReturn;
            yamlChildNode->absoluteFilePath = this->absoluteFilePath;
            childNodes.push_back(yamlChildNode);
            result = yamlChildNode;
        }
    }

    return result;
}

template<typename T>
T YamlNode::getValue(const YAML::Node &yamlNodeToReturn) const
{
    T value = yamlNodeToReturn.as<T>();
    return value;
}

} /* namespace lanty */
