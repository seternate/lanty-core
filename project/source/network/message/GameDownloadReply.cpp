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

#include "network/message/GameDownloadReply.hpp"

#include <string>

namespace lanty
{

const std::string GameDownloadReply::GAMEID_SERIALIZER_KEY("gameid");
const std::string GameDownloadReply::GAMESIZE_SERIALIZER_KEY("gamesize");

GameDownloadReply::GameDownloadReply(GameDownloadReply& message) noexcept : Message(message) { }

GameDownloadReply::GameDownloadReply(GameDownloadReply&& message) noexcept : Message(std::move(message)) { }

GameDownloadReply::GameDownloadReply(Message& message) noexcept : Message(message) { }

GameDownloadReply::GameDownloadReply(Message&& message) noexcept : Message(std::move(message)) { }

GameDownloadReply::GameDownloadReply(const Game& game, quint64 gamesize) noexcept :
    Message(MessageType::Type::GAMEDOWNLOAD_REPLY)
{
    this->payload[GameDownloadReply::GAMEID_SERIALIZER_KEY] = game.getID();
    this->payload[GameDownloadReply::GAMESIZE_SERIALIZER_KEY] = gamesize;
}


GameDownloadReply& GameDownloadReply::operator=(const GameDownloadReply& message) noexcept
{
    static_cast<Message>(*this) = message;
    return *this;
}

GameDownloadReply& GameDownloadReply::operator=(GameDownloadReply&& message) noexcept
{
    static_cast<Message>(*this) = std::move(message);
    return *this;
}

GameDownloadReply& GameDownloadReply::operator=(const Message& message) noexcept
{
    static_cast<Message>(*this) = message;
    return *this;
}

GameDownloadReply& GameDownloadReply::operator=(Message&& message) noexcept
{
    static_cast<Message>(*this) = std::move(message);
    return *this;
}

bool GameDownloadReply::operator==(const GameDownloadReply& message) const noexcept
{
    return (static_cast<Message>(*this) == message);
}

bool GameDownloadReply::operator!=(const GameDownloadReply& message) const noexcept
{
    return (static_cast<Message>(*this) != message);
}


qint64 GameDownloadReply::getGameID(void) const noexcept
{
    return this->getPayloadAsJSON()[GameDownloadReply::GAMEID_SERIALIZER_KEY].get<qint64>();
}

quint64 GameDownloadReply::getGameSize(void) const noexcept
{
    return this->getPayloadAsJSON()[GameDownloadReply::GAMESIZE_SERIALIZER_KEY].get<quint64>();
}

} /* namespace lanty */
