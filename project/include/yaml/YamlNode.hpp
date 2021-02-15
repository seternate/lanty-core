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

#ifndef YAML_YAMLNODE_HPP
#define YAML_YAMLNODE_HPP

#include <yaml-cpp/yaml.h>
#include <QString>
#include <memory>
#include <vector>

#include "core/ltycore_global.hpp"

namespace lanty
{

class LTYCORE_EXPORT YamlNode
{
    Q_DISABLE_COPY_MOVE(YamlNode);

public:
    YamlNode(void) = default;
    YamlNode(const QString& absoluteFilePath, const bool load = true);
    virtual ~YamlNode(void) = default;

    virtual QString getFileName(void) const;
    virtual QString getFilePath(void) const;
    virtual const YamlNode* getNode(const QString& key) const;
    virtual const YamlNode* getNode(const int index) const;
    virtual YamlNode* getNode(const QString& key);
    virtual YamlNode* getNode(const int index);
    virtual QString getQStringFromMap(const QString& key) const;
    virtual QString getQStringFromSequence(const int index) const;
    virtual QString getQString(void) const;
    virtual double getDoubleFromMap(const QString& key) const;
    virtual double getDoubleFromSequence(const int index) const;
    virtual double getDouble(void) const;
    virtual int getSize(void) const;
    virtual bool isDefined(const QString& key) const;
    virtual bool isNull(const QString& key) const;
    virtual bool isValue(const QString& key) const;
    virtual bool isSequence(const QString& key) const;
    virtual bool isMap(const QString& key) const;
    virtual bool isNull(void) const;
    virtual bool isValue(void) const;
    virtual bool isSequence(void) const;
    virtual bool isMap(void) const;

    virtual YamlNode* setNode(const QString& key);
    virtual void setString(const QString& value);
    virtual void setString(const QString& key, const QString& value);
    virtual void setString(const int index, const QString& value);
    virtual void setDouble(const double value);
    virtual void setDouble(const QString& key, const double value);
    virtual void setDouble(const int index, const double value);

    virtual bool loadFromFile(void);
    virtual bool loadFromFile(const QString& absoluteFilePath);
    virtual bool saveToFile(void);
    virtual bool saveToFile(const QString& absoluteFilePath);

protected:
    YAML::Node node;
    QString absoluteFilePath;

private:
    YamlNode* getNode(YAML::Node& yamlNodeToReturn) const;
    template<typename T>
    T getValue(const YAML::Node& yamlNodeToReturn) const;

    mutable std::vector<std::shared_ptr<YamlNode>> childNodes;
};

} /* namespace lanty */

#endif /* YAML_YAMLNODE_HPP */
