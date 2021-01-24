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

#include <fstream>
#include <QFile>
#include <QFileInfo>
#include <string>

#include <logging/Logger.hpp>
#include <logging/LogLevel.hpp>

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


YamlNode::YamlNode(const QString &absoluteFilePath, const bool load) : node(),
                                                                       absoluteFilePath(absoluteFilePath),
                                                                       childNodes()
{
    QFile file(this->absoluteFilePath);
    if(file.exists() == true && load == true)
    {
        Logger(LogLevel::TRACE) << "Loading YAML-file '" << this->getFileName() << "'.";
        this->node = YAML::LoadFile(absoluteFilePath.toStdString());
        Logger() << "Loaded YAML-file '" << this->getFileName() << "'.";
    }
    else if(file.exists() == false)
    {
        Logger(LogLevel::ERROR) << "Can not load the YAML-file '"
                                << this->getFileName()
                                << "'. The file does not exist.";
    }
}


QString YamlNode::getFileName(void) const
{
    QString result;

    QFileInfo fileInfo(this->absoluteFilePath);
    result = fileInfo.fileName();

    return result;
}

QString YamlNode::getFilePath(void) const
{
    return QFileInfo(this->absoluteFilePath).absoluteFilePath();
}

const YamlNode* YamlNode::getNode(const QString &key) const
{
    YAML::Node yamlNodeToReturn = this->node[key.toStdString()];
    if(yamlNodeToReturn.IsDefined() == false)
    {
        Logger() << "No YAML-Node with key '" << key << "' in file '" << this->getFileName() << "'.";
    }
    return this->getNode(yamlNodeToReturn);
}

const YamlNode* YamlNode::getNode(const int index) const
{
    YAML::Node yamlNodeToReturn = this->node[index];
    if(yamlNodeToReturn.IsDefined() == false)
    {
        Logger() << "No YAML-Node at index '"
                 << QString::number(index)
                 << "' in file '" << this->getFileName() << "'.";
    }
    return this->getNode(yamlNodeToReturn);
}

YamlNode* YamlNode::getNode(const QString &key)
{
    YAML::Node yamlNodeToReturn = this->node[key.toStdString()];
    if(yamlNodeToReturn.IsDefined() == false)
    {
        Logger() << "No YAML-Node with key '" << key << "' in file '" << this->getFileName() << "'.";
    }
    return this->getNode(yamlNodeToReturn);
}

YamlNode* YamlNode::getNode(const int index)
{
    YAML::Node yamlNodeToReturn = this->node[index];
    if(yamlNodeToReturn.IsDefined() == false)
    {
        Logger() << "No YAML-Node at index '"
                 << QString::number(index) << "' in file '"
                 << this->getFileName() << "'.";
    }
    return this->getNode(yamlNodeToReturn);
}

QString YamlNode::getQStringFromMap(const QString &key) const
{
    YAML::Node yamlNodeToReturn = this->node[key.toStdString()];
    if(yamlNodeToReturn.IsDefined() == false)
    {
        Logger() << "No map with key '" << key << "' at YAML-file '" << this->getFileName() << "'.";
    }
    return this->getValue<QString>(yamlNodeToReturn);
}

QString YamlNode::getQStringFromSequence(const int index) const
{
    YAML::Node yamlNodeToReturn = this->node[index];
    if(yamlNodeToReturn.IsDefined() == false)
    {
        Logger() << "No item at sequence with index '"
                 << QString::number(index)
                 << "' at YAML-file '"
                 << this->getFileName() << "'.";
    }
    return this->getValue<QString>(yamlNodeToReturn);
}

QString YamlNode::getQString(void) const
{
    return this->getValue<QString>(this->node);
}

double YamlNode::getDoubleFromMap(const QString &key) const
{
    YAML::Node yamlNodeToReturn = this->node[key.toStdString()];
    if(yamlNodeToReturn.IsDefined() == false)
    {
        Logger() << "No map with key '" << key << "' at YAML-file '" << this->getFileName() << "'.";
    }
    return this->getValue<double>(yamlNodeToReturn);
}

double YamlNode::getDoubleFromSequence(const int index) const
{
    YAML::Node yamlNodeToReturn = this->node[index];
    if(yamlNodeToReturn.IsDefined() == false)
    {
        Logger() << "No item at sequence with index '"
                 << QString::number(index)
                 << "' at YAML-file '"
                 << this->getFileName() << "'.";
    }
    return this->getValue<double>(yamlNodeToReturn);
}

double YamlNode::getDouble(void) const
{
    return this->getValue<double>(this->node);
}

int YamlNode::getSize(void) const
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

bool YamlNode::isNull(void) const
{
    return this->node.IsNull();
}

bool YamlNode::isValue(void) const
{
    return this->node.IsScalar();
}

bool YamlNode::isSequence(void) const
{
    return this->node.IsSequence();
}

bool YamlNode::isMap(void) const
{
    return this->node.IsMap();
}

YamlNode* YamlNode::setNode(const QString &key)
{
    YamlNode *result = nullptr;

    YAML::Node newNode = this->node[key.toStdString()];
    std::shared_ptr<YamlNode> newChildNode(new YamlNode());
    newChildNode->node = newNode;
    newChildNode->absoluteFilePath = this->absoluteFilePath;
    this->childNodes.push_back(newChildNode);
    result = newChildNode.get();

    return result;
}

void YamlNode::setString(const QString &value)
{
    this->node = value.toStdString();
}

void YamlNode::setString(const QString &key, const QString &value)
{
    this->node[key.toStdString()] = value.toStdString();
}

void YamlNode::setString(const int index, const QString &value)
{
    this->node[index] = value.toStdString();
}

void YamlNode::setDouble(const double value)
{
    this->node = value;
}

void YamlNode::setDouble(const QString &key, const double value)
{
    this->node[key.toStdString()] = value;
}

void YamlNode::setDouble(const int index, const double value)
{
    this->node[index] = value;
}

bool YamlNode::loadFromFile(void)
{
    return this->loadFromFile(this->absoluteFilePath);
}


bool YamlNode::loadFromFile(const QString &absoluteFilePath)
{
    bool result = false;
    this->absoluteFilePath = absoluteFilePath;

    QFile file(this->absoluteFilePath);
    if(file.exists() == true)
    {
        Logger(LogLevel::TRACE) << "Loading YAML-file '" << absoluteFilePath << "'.";
        this->node = YAML::LoadFile(absoluteFilePath.toStdString());
        Logger() << "Loaded YAML-file '" << absoluteFilePath << "'.";
        this->childNodes = std::vector<std::shared_ptr<YamlNode>>();
        Logger(LogLevel::TRACE) << "Reseted child YAML-Nodes for YAML-file '" << absoluteFilePath << "'.";
        result = true;
    }
    else
    {
        Logger(LogLevel::ERROR) << "Can not load the YAML-file '"
                                << this->getFileName()
                                << "'. The file does not exist.";
    }

    return result;
}

bool YamlNode::saveToFile(void)
{
    return this->saveToFile(this->absoluteFilePath);
}

bool YamlNode::saveToFile(const QString &absoluteFilePath)
{
    std::ofstream fileOutStream(absoluteFilePath.toStdString());
    fileOutStream << this->node;
    return fileOutStream.good();
}


YamlNode* YamlNode::getNode(YAML::Node &yamlNodeToReturn) const
{
    YamlNode* result = nullptr;

    if(yamlNodeToReturn.IsDefined() == true && yamlNodeToReturn.IsNull() == false)
    {
        for(std::shared_ptr<YamlNode> childNode : this->childNodes)
        {
            if(childNode->node == yamlNodeToReturn)
            {
                result = childNode.get();
                Logger(LogLevel::TRACE) << "Return Node exists as child node already for YAML-file '"
                                        << this->getFileName()
                                        << "'.";
                break;
            }
        }

        if(result == nullptr)
        {
            Logger(LogLevel::TRACE) << "No child node exists to return for YAML-file '"
                                    << this->getFileName()
                                    << "'. Creating child node.";
            std::shared_ptr<YamlNode> yamlChildNode(new YamlNode());
            yamlChildNode->node = yamlNodeToReturn;
            yamlChildNode->absoluteFilePath = this->absoluteFilePath;
            this->childNodes.push_back(yamlChildNode);
            Logger(LogLevel::TRACE) << "Created child node for YAML-file '"
                                    << this->getFileName()
                                    << "'.";
            result = yamlChildNode.get();
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
