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

#ifndef SERIALIZER_SERIALIZABLE_HPP
#define SERIALIZER_SERIALIZABLE_HPP

#include <QString>
#include <nlohmann/json.hpp>

#include "core/ltycore_global.hpp"
#include "yaml/YamlNode.hpp"

namespace lanty
{

class LTYCORE_EXPORT Serializable
{
public:
    Serializable(void) = default;
    virtual ~Serializable(void) = default;

    virtual nlohmann::json* toJSON(void) const;
    virtual QString toJSONString(void) const;
    virtual YamlNode* toYAML(void) const;
    virtual QString toYAMLString(void) const;

    virtual bool fromJSON(const nlohmann::json& json);
    virtual bool fromJSONString(const QString& json);
    virtual bool fromYAML(const YamlNode& yaml);
    virtual bool fromYAMLString(const QString& yaml);
};

} /* namespace lanty */

#endif /* SERIALIZER_SERIALIZABLE_HPP */
