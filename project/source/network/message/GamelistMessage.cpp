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

#include "network/message/GamelistMessage.hpp"
#include "game/QGamelistLoader.hpp"

namespace lanty
{

const std::string GamelistMessage::GAMELIST_SERIALIZER_KEY("gamelist");

GamelistMessage::GamelistMessage(GamelistMessage& message) noexcept : Message(message) { }

GamelistMessage::GamelistMessage(GamelistMessage&& message) noexcept : Message(std::move(message)) { }

GamelistMessage::GamelistMessage(Message& message) noexcept : Message(message) { }

GamelistMessage::GamelistMessage(Message&& message) noexcept : Message(std::move(message)) { }

GamelistMessage::GamelistMessage(const QGamelist& gamelist) noexcept :
    Message(MessageType::Type::ADDRESS)
{
    nlohmann::json payload = nlohmann::json::object();

    payload[GamelistMessage::GAMELIST_SERIALIZER_KEY] = gamelist.toJSON();

    this->setPayload(payload);
}


GamelistMessage& GamelistMessage::operator=(const GamelistMessage& message) noexcept
{
    static_cast<Message>(*this) = message;
    return *this;
}

GamelistMessage& GamelistMessage::operator=(GamelistMessage&& message) noexcept
{
    static_cast<Message>(*this) = std::move(message);
    return *this;
}

GamelistMessage& GamelistMessage::operator=(const Message& message) noexcept
{
    static_cast<Message>(*this) = message;
    return *this;
}

GamelistMessage& GamelistMessage::operator=(Message&& message) noexcept
{
    static_cast<Message>(*this) = std::move(message);
    return *this;
}

bool GamelistMessage::operator==(const GamelistMessage& message) const noexcept
{
    return (static_cast<Message>(*this) == message);
}

bool GamelistMessage::operator!=(const GamelistMessage& message) const noexcept
{
    return (static_cast<Message>(*this) != message);
}


QGamelist* GamelistMessage::getGamelist(void) const noexcept
{
    return QGamelistLoader().load(this->getPayloadAsJSON());
}

} /* namespace lanty */
