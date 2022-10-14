/* Copyright <2022> <Levin Jeck>
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

#include <map>
#include <string>

#include "core/ltycore_global.hpp"

namespace lanty
{

class LTYCORE_EXPORT MessageType
{
public:
    enum class Type : quint64
    {
        UNKNOWN = 0x00,
        ADDRESS = 0x01,
        USER = 0x02,
        GAMELIST = 0x03,
        GAMEDOWNLOAD_REQUEST = 0x04,
        GAMEDOWNLOAD_REPLY = 0x05
    };

    static std::string typeToString(MessageType::Type type) noexcept;
    static MessageType::Type stringToType(const std::string& type) noexcept;

    MessageType(void) = default;
    MessageType(MessageType::Type type) noexcept;
    explicit MessageType(const std::string& type) noexcept;
    MessageType(const MessageType& type) noexcept;
    MessageType(MessageType&& type) noexcept;
    virtual ~MessageType(void) = default;    // GCOVR_EXCL_LINE

    MessageType& operator=(const MessageType& type) noexcept;
    MessageType& operator=(MessageType&& type) noexcept;
    bool operator==(MessageType type) const noexcept;
    bool operator!=(MessageType type) const noexcept;
    explicit operator std::string(void) const noexcept;
    operator MessageType::Type(void) const noexcept;

    void setType(const std::string& type) noexcept;
    void setType(MessageType::Type type) noexcept;

    [[nodiscard]] std::string toStdString(void) const noexcept;
    [[nodiscard]] MessageType::Type toType(void) const noexcept;

private:
    static const std::map<std::string, MessageType::Type> STRING_TYPE_MAP;

    MessageType::Type type = MessageType::Type::UNKNOWN;
};

} /* namespace lanty */
