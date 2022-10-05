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
#include <nlohmann/json.hpp>
#include <string>

#include "core/JSONSerializable.hpp"
#include "core/YAMLSerializable.hpp"
#include "core/ltycore_global.hpp"

namespace lanty
{

class LTYCORE_EXPORT GameClient : public JSONSerializable, public YAMLSerializable
{
public:
    static const std::string EXECUTABLE_FILE_PATH_SERIALIZER_KEY;
    static const std::string CONNECT_ARGUMENT_SERIALIZER_KEY;
    static const std::string ARGUMENT_SERIALIZER_KEY;

    GameClient(const QString& filePath = QString(""),
               const QString& connectArgument = QString(""),
               const QString& argument = QString("")) noexcept;
    GameClient(const GameClient& gameclient) noexcept;
    GameClient(GameClient&& gameclient) noexcept;
    virtual ~GameClient(void) = default;

    GameClient& operator=(const GameClient& gameclient) noexcept;
    GameClient& operator=(GameClient&& gameclient) noexcept;
    bool operator==(const GameClient& gameclient) const noexcept;
    bool operator!=(const GameClient& gameclient) const noexcept;

    const QString& getExecutableFilePath(void) const noexcept;
    const QString& getConnectArgument(void) const noexcept;
    const QString& getArgument(void) const noexcept;

    void setExecutableFilePath(const QString& filePath) noexcept;
    void setConnectArgument(const QString& connectArgument) noexcept;
    void setArgument(const QString& argument) noexcept;

    bool canJoinServerWithCLI(void) const noexcept;

    nlohmann::json toJSON(void) const override;
    YAML::Node toYAML(void) const override;

private:
    QString executableFilePath;
    QString connectArgument;
    QString argument;
};

} /* namespace lanty */
