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

#ifndef YAML_IYAMLNODE_HPP
#define YAML_IYAMLNODE_HPP

#include <core/ltycore_global.hpp>

#include <memory>
#include <QObject>
#include <QString>

namespace lanty
{

class LTYCORE_EXPORT IYamlNode : public QObject
{

    Q_OBJECT

public:
    virtual QString getFileName(void) const = 0;
    virtual std::shared_ptr<const IYamlNode> getNode(const QString &key) const = 0;
    virtual std::shared_ptr<const IYamlNode> getNode(const int index) const = 0;
    virtual std::shared_ptr<IYamlNode> getNode(const QString &key) = 0;
    virtual std::shared_ptr<IYamlNode> getNode(const int index) = 0;
    virtual QString getQStringFromMap(const QString &key) const = 0;
    virtual QString getQStringFromSequence(const int index) const = 0;
    virtual QString getQString(void) const = 0;
    virtual double getDoubleFromMap(const QString &key) const = 0;
    virtual double getDoubleFromSequence(const int index) const = 0;
    virtual double getDouble(void) const = 0;
    virtual int getSize(void) const = 0;

    virtual bool isDefined(const QString &key) const = 0;
    virtual bool isNull(const QString &key) const = 0;
    virtual bool isValue(const QString &key) const = 0;
    virtual bool isSequence(const QString &key) const = 0;
    virtual bool isMap(const QString &key) const = 0;
    virtual bool isNull(void) const = 0;
    virtual bool isValue(void) const = 0;
    virtual bool isSequence(void) const = 0;
    virtual bool isMap(void) const = 0;

};

} /* namespace lanty */

#endif /* YAML_IYAMLNODE_HPP */
