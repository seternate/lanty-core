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

#include "network/message/Message.hpp"

namespace lanty
{

const std::string Message::HEADER_SERIALIZER_KEY = "header";
const std::string Message::TYPE_SERIALIZER_KEY = "type";
const std::string Message::PAYLOAD_SERIALIZER_KEY = "payload";


Message::Message(MessageType type, const nlohmann::json& payload) noexcept :
    type(type),
    payload(payload)
{ }

Message::Message(const Message& message) noexcept :
    type(message.getType()),
    payload(message.getPayloadAsJSON())
{ }

Message::Message(Message&& message) noexcept :
    type(std::move(message.type)),
    payload(std::move(message.payload))
{ }


Message& Message::operator=(const Message& message) noexcept
{
    this->type = message.getType();
    this->payload = message.getPayloadAsJSON();

    return *this;
}

Message& Message::operator=(Message&& message) noexcept
{
    this->type = std::move(message.type);
    this->payload = std::move(message.payload);

    return *this;
}

bool Message::operator==(const Message& message) const noexcept
{
    return (this->type == message.getType()) && (this->payload == message.getPayloadAsJSON());
}

bool Message::operator!=(const Message& message) const noexcept
{
    return !(*this == message);
}


MessageType Message::getType(void) const noexcept
{
    return this->type;
}


[[nodiscard]] nlohmann::json Message::getHeaderAsJSON(void) const noexcept
{
    nlohmann::json header = nlohmann::json::object();

    header[Message::TYPE_SERIALIZER_KEY] = this->type.toStdString();

    return header;
}

[[nodiscard]] nlohmann::json Message::getPayloadAsJSON(void) const noexcept
{
    return this->payload;
}

[[nodiscard]] nlohmann::json Message::toJSON(void) const
{
    nlohmann::json message = nlohmann::json::object();

    message[Message::HEADER_SERIALIZER_KEY] = this->getHeaderAsJSON();
    message[Message::PAYLOAD_SERIALIZER_KEY] = this->getPayloadAsJSON();

    return message;
}


void Message::setPayload(const nlohmann::json& payload) noexcept
{
    this->payload = payload;
}

} /* namespace lanty */
