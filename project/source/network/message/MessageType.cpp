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

#include "network/message/MessageType.hpp"

namespace lanty
{

const std::map<std::string, MessageType::Type> MessageType::STRING_TYPE_MAP = { { "unknown", MessageType::Type::UNKNOWN },
                                                                                { "address", MessageType::Type::ADDRESS },
                                                                                { "user", MessageType::Type::USER},
                                                                                { "gamelist", MessageType::Type::GAMELIST } };


std::string MessageType::typeToString(MessageType::Type type) noexcept
{
    std::string result;

    for (auto& [key, value] : MessageType::STRING_TYPE_MAP)
    {
        if (value == type)
        {
            result = key;
        }
    }

    return result;
}

MessageType::Type MessageType::stringToType(const std::string& type) noexcept
{
    MessageType::Type result = MessageType::Type::UNKNOWN;

    if (MessageType::STRING_TYPE_MAP.count(type) == 1)
    {
        result = MessageType::STRING_TYPE_MAP.at(type);
    }
    return result;
}


MessageType::MessageType(MessageType::Type type) noexcept
{
    this->type = type;
}

MessageType::MessageType(const std::string& type) noexcept
{
    this->type = MessageType::stringToType(type);
}

MessageType::MessageType(const MessageType& type) noexcept
{
    this->type = type.toType();
}

MessageType::MessageType(MessageType&& type) noexcept : type(std::move(type.type)) { }


MessageType& MessageType::operator=(const MessageType& type) noexcept
{
    this->type = type.toType();
    return *this;
}

MessageType& MessageType::operator=(MessageType&& type) noexcept
{
    this->type = std::move(type.type);

    return *this;
}

bool MessageType::operator==(MessageType type) const noexcept
{
    return (this->type == type.toType());
}

bool MessageType::operator!=(MessageType type) const noexcept
{
    return !(*this == type);
}

MessageType::operator std::string(void) const noexcept
{
    return this->toStdString();
}

MessageType::operator MessageType::Type(void) const noexcept
{
    return this->toType();
}


void MessageType::setType(const std::string& type) noexcept
{
    this->type = MessageType::stringToType(type);
}

void MessageType::setType(MessageType::Type type) noexcept
{
    this->type = type;
}


std::string MessageType::toStdString(void) const noexcept
{
    return MessageType::typeToString(this->type);
}

MessageType::Type MessageType::toType(void) const noexcept
{
    return this->type;
}

} /* namespace lanty */
