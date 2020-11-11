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

#include <core/ltycore_global.hpp>

#include <memory>
#include <QObject>
#include <QString>
#include <vector>
#include <yaml-cpp/yaml.h>

#include <yaml/IYamlNode.hpp>

namespace lanty
{

class LTYCORE_EXPORT YamlNode : public IYamlNode
{

    Q_OBJECT

private:
    std::shared_ptr<IYamlNode> getNode(YAML::Node &yamlNodeToReturn) const;
    template<typename T>
    T getValue(const YAML::Node &yamlNodeToReturn) const;

public:
    YamlNode(void);
    YamlNode(const QString &absoluteFilePath);
    virtual ~YamlNode(void);

    QString getFileName() const override;
    std::shared_ptr<const IYamlNode> getNode(const QString &key) const override;
    std::shared_ptr<const IYamlNode> getNode(const int index) const override;
    std::shared_ptr<IYamlNode> getNode(const QString &key) override;
    std::shared_ptr<IYamlNode> getNode(const int index) override;
    QString getQStringFromMap(const QString &key) const override;
    QString getQStringFromSequence(const int index) const override;
    QString getQString(void) const override;
    double getDoubleFromMap(const QString &key) const override;
    double getDoubleFromSequence(const int index) const override;
    double getDouble(void) const override;
    int getSize(void) const override;

    bool isDefined(const QString &key) const override;
    bool isNull(const QString &key) const override;
    bool isValue(const QString &key) const override;
    bool isSequence(const QString &key) const override;
    bool isMap(const QString &key) const override;
    bool isNull(void) const override;
    bool isValue(void) const override;
    bool isSequence(void) const override;
    bool isMap(void) const override;

protected:
    YAML::Node node;
    QString absoluteFilePath;
private:
    mutable std::vector<std::shared_ptr<YamlNode>> childNodes;

};

} /* namespace lanty */

#endif /* YAML_YAMLNODE_HPP */
