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

#include <QHostAddress>

#include "core/ltycore_global.hpp"
#include "network/message/Message.hpp"
#include "game/Game.hpp"

namespace lanty
{

class LTYCORE_EXPORT GameDownloadReply : public Message
{
public:
    static const std::string GAME_SERIALIZER_KEY;
    static const std::string GAMESIZE_SERIALIZER_KEY;

    GameDownloadReply(void) = delete;
    GameDownloadReply(GameDownloadReply& message) noexcept;
    GameDownloadReply(GameDownloadReply&& message) noexcept;
    GameDownloadReply(Message& message) noexcept;
    GameDownloadReply(Message&& message) noexcept;
    GameDownloadReply(const Game& game, quint64 gamesize) noexcept;
    virtual ~GameDownloadReply(void) = default;    // GCOVR_EXCL_LINE

    GameDownloadReply& operator=(const GameDownloadReply& message) noexcept;
    GameDownloadReply& operator=(GameDownloadReply&& message) noexcept;
    GameDownloadReply& operator=(const Message& message) noexcept;
    GameDownloadReply& operator=(Message&& message) noexcept;
    bool operator==(const GameDownloadReply& message) const noexcept;
    bool operator!=(const GameDownloadReply& message) const noexcept;

    Game getGame(void) const noexcept;
    quint64 getGameSize() const noexcept;
};

} /* namespace lanty */
