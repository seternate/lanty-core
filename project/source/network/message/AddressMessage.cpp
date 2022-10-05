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

#include "network/message/AddressMessage.hpp"

namespace lanty
{

const std::string AddressMessage::HOST_SERIALIZER_KEY("host");
const std::string AddressMessage::PORT_SERIALIZER_KEY("port");

AddressMessage::AddressMessage(AddressMessage& message) noexcept : Message(message) { }

AddressMessage::AddressMessage(AddressMessage&& message) noexcept : Message(std::move(message)) { }

AddressMessage::AddressMessage(Message& message) noexcept : Message(message) { }

AddressMessage::AddressMessage(Message&& message) noexcept : Message(std::move(message)) { }

AddressMessage::AddressMessage(const QHostAddress& host, quint16 port) noexcept :
    Message(MessageType::Type::ADDRESS)
{
    nlohmann::json payload = nlohmann::json::object();

    payload[AddressMessage::HOST_SERIALIZER_KEY] = host.toString().toStdString();
    payload[AddressMessage::PORT_SERIALIZER_KEY] = port;

    this->setPayload(payload);
}


AddressMessage& AddressMessage::operator=(const AddressMessage& message) noexcept
{
    static_cast<Message>(*this) = message;
    return *this;
}

AddressMessage& AddressMessage::operator=(AddressMessage&& message) noexcept
{
    static_cast<Message>(*this) = std::move(message);
    return *this;
}

AddressMessage& AddressMessage::operator=(const Message& message) noexcept
{
    static_cast<Message>(*this) = message;
    return *this;
}

AddressMessage& AddressMessage::operator=(Message&& message) noexcept
{
    static_cast<Message>(*this) = std::move(message);
    return *this;
}

bool AddressMessage::operator==(const AddressMessage& message) const noexcept
{
    return (static_cast<Message>(*this) == message);
}

bool AddressMessage::operator!=(const AddressMessage& message) const noexcept
{
    return (static_cast<Message>(*this) != message);
}


QHostAddress AddressMessage::getHost(void) const noexcept
{
    std::string rawHostString = this->getPayloadAsJSON()[AddressMessage::HOST_SERIALIZER_KEY].get<std::string>();
    QString hostString = QString::fromStdString(rawHostString);

    return QHostAddress(hostString);
}

QString AddressMessage::getHostAsString(void) const noexcept
{
    return this->getHost().toString();
}

quint16 AddressMessage::getPort(void) const noexcept
{
    quint16 port = this->getPayloadAsJSON()[AddressMessage::PORT_SERIALIZER_KEY].get<quint16>();

    return port;
}

} /* namespace lanty */
