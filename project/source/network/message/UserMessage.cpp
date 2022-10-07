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

#include "network/message/UserMessage.hpp"
#include "user/UserLoader.hpp"

namespace lanty
{

const std::string UserMessage::USER_SERIALIZER_KEY("host");

UserMessage::UserMessage(UserMessage& message) noexcept : Message(message) { }

UserMessage::UserMessage(UserMessage&& message) noexcept : Message(std::move(message)) { }

UserMessage::UserMessage(Message& message) noexcept : Message(message) { }

UserMessage::UserMessage(Message&& message) noexcept : Message(std::move(message)) { }

UserMessage::UserMessage(const User& user) noexcept :
    Message(MessageType::Type::USER)
{
    nlohmann::json payload = nlohmann::json::object();

    payload[UserMessage::USER_SERIALIZER_KEY] = user.toJSON();

    this->setPayload(payload);
}


UserMessage& UserMessage::operator=(const UserMessage& message) noexcept
{
    static_cast<Message>(*this) = message;
    return *this;
}

UserMessage& UserMessage::operator=(UserMessage&& message) noexcept
{
    static_cast<Message>(*this) = std::move(message);
    return *this;
}

UserMessage& UserMessage::operator=(const Message& message) noexcept
{
    static_cast<Message>(*this) = message;
    return *this;
}

UserMessage& UserMessage::operator=(Message&& message) noexcept
{
    static_cast<Message>(*this) = std::move(message);
    return *this;
}

bool UserMessage::operator==(const UserMessage& message) const noexcept
{
    return (static_cast<Message>(*this) == message);
}

bool UserMessage::operator!=(const UserMessage& message) const noexcept
{
    return (static_cast<Message>(*this) != message);
}


User UserMessage::getUser(void) const noexcept
{
    User user = UserLoader().load(this->getPayloadAsJSON()[UserMessage::USER_SERIALIZER_KEY]);

    return user;
}

} /* namespace lanty */
