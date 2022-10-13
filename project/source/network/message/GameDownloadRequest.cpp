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

#include "network/message/GameDownloadRequest.hpp"
#include "game/GameLoader.hpp"

namespace lanty
{

const std::string GameDownloadRequest::GAME_SERIALIZER_KEY("game");

GameDownloadRequest::GameDownloadRequest(GameDownloadRequest& message) noexcept : Message(message) { }

GameDownloadRequest::GameDownloadRequest(GameDownloadRequest&& message) noexcept : Message(std::move(message)) { }

GameDownloadRequest::GameDownloadRequest(Message& message) noexcept : Message(message) { }

GameDownloadRequest::GameDownloadRequest(Message&& message) noexcept : Message(std::move(message)) { }

GameDownloadRequest::GameDownloadRequest(const Game& game) noexcept :
    Message(MessageType::Type::GAMEDOWNLOAD_REQUEST)
{
    nlohmann::json payload = nlohmann::json::object();

    payload[GameDownloadRequest::GAME_SERIALIZER_KEY] = game.toJSON();

    this->setPayload(payload);
}


GameDownloadRequest& GameDownloadRequest::operator=(const GameDownloadRequest& message) noexcept
{
    static_cast<Message>(*this) = message;
    return *this;
}

GameDownloadRequest& GameDownloadRequest::operator=(GameDownloadRequest&& message) noexcept
{
    static_cast<Message>(*this) = std::move(message);
    return *this;
}

GameDownloadRequest& GameDownloadRequest::operator=(const Message& message) noexcept
{
    static_cast<Message>(*this) = message;
    return *this;
}

GameDownloadRequest& GameDownloadRequest::operator=(Message&& message) noexcept
{
    static_cast<Message>(*this) = std::move(message);
    return *this;
}

bool GameDownloadRequest::operator==(const GameDownloadRequest& message) const noexcept
{
    return (static_cast<Message>(*this) == message);
}

bool GameDownloadRequest::operator!=(const GameDownloadRequest& message) const noexcept
{
    return (static_cast<Message>(*this) != message);
}


Game GameDownloadRequest::getGame(void) const noexcept
{
    return GameLoader().load(this->getPayloadAsJSON()[GameDownloadRequest::GAME_SERIALIZER_KEY]);
}

} /* namespace lanty */
