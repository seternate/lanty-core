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

#include <QString>
#include <nlohmann/json.hpp>

namespace lanty
{

template<typename T>
class JSONLoadable
{
public:
    virtual T load(const nlohmann::json& json) const = 0;

protected:
    QString loadFieldAsQString(const nlohmann::json& json, const std::string& key) const
    {
        QString field;

        if (json.contains(key) == true)
        {
            std::string fieldFromJSON = json[key].get<std::string>();
            field = QString::fromStdString(fieldFromJSON);
        }

        return field;
    }

    qint64 loadFieldAsInteger(const nlohmann::json& json, const std::string& key) const
    {
        qint64 field = 0;

        if (json.contains(key) == true)
        {
            field = json[key].get<qint64>();
        }

        return field;
    }

    nlohmann::json loadFieldAsJSON(const nlohmann::json& json, const std::string& key) const
    {
        if (json.contains(key) == false)
        {
            return nlohmann::json();
        }

        return json[key];
    }
};

} /* namespace lanty */
