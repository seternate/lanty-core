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

#pragma once

#include <yaml-cpp/yaml.h>
#include <QString>
#include <string>

namespace lanty
{

template<typename T>
class YAMLLoadable
{
public:
    virtual T load(const YAML::Node& yaml) const = 0;

protected:
    QString loadFieldAsQString(const YAML::Node& yaml, const std::string& key) const
    {
        QString field("");

        YAML::Node yamlField = yaml[key];
        if (yamlField.IsDefined() == true)
        {
            std::string fieldFromYaml = yamlField.as<std::string>();
            field = QString::fromStdString(fieldFromYaml);
        }

        return field;
    }

    qint64 loadFieldAsInteger(const YAML::Node& yaml, const std::string& key) const
    {
        qint64 field = 0;

        YAML::Node yamlField = yaml[key];
        if (yamlField.IsDefined() == true)
        {
            field = yamlField.as<qint64>();
        }

        return field;
    }

    YAML::Node loadFieldAsYAML(const YAML::Node& yaml, const std::string& key) const
    {
        YAML::Node yamlField = yaml[key];
        if (yamlField.IsDefined() == false)
        {
            return YAML::Node();
        }

        return yamlField;
    }
};

} /* namespace lanty */
