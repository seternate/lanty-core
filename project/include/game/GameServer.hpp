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
#include <string>

#include "core/Serializable.hpp"
#include "core/ltycore_global.hpp"

namespace lanty
{

class LTYCORE_EXPORT GameServer : public Serializable
{
public:
    static const std::string EXECUTABLE_FILE_PATH_SERIALIZER_KEY;
    static const std::string ARGUMENT_SERIALIZER_KEY;

    GameServer(const QString& filePath = QString(""), const QString& argument = QString("")) noexcept;
    GameServer(const GameServer& gameserver) noexcept;
    GameServer(GameServer&& gameserver) noexcept = delete;
    virtual ~GameServer(void) = default;    // GCOVR_EXCL_LINE

    GameServer& operator=(const GameServer& gameserver) noexcept;
    GameServer& operator=(GameServer&& gameserver) = delete;
    bool operator==(const GameServer& gameserver) const noexcept;
    bool operator!=(const GameServer& gameserver) const noexcept;

    const QString& getExecutableFilePath(void) const noexcept;
    const QString& getArgument(void) const noexcept;

    void setExecutableFilePath(const QString& filePath) noexcept;
    void setArgument(const QString& argument) noexcept;

    bool canOpenDedicatedServer(void) const noexcept;
    bool canOpenServer(void) const noexcept;

    nlohmann::json toJSON(void) const override;

private:
    QString executableFilePath;
    QString argument;
};

} /* namespace lanty */
