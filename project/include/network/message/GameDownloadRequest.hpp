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

class LTYCORE_EXPORT GameDownloadRequest : public Message
{
public:
    static const std::string GAMEID_SERIALIZER_KEY;

    GameDownloadRequest(void) = delete;
    GameDownloadRequest(GameDownloadRequest& message) noexcept;
    GameDownloadRequest(GameDownloadRequest&& message) noexcept;
    GameDownloadRequest(Message& message) noexcept;
    GameDownloadRequest(Message&& message) noexcept;
    GameDownloadRequest(const Game& user) noexcept;
    virtual ~GameDownloadRequest(void) = default;    // GCOVR_EXCL_LINE

    GameDownloadRequest& operator=(const GameDownloadRequest& message) noexcept;
    GameDownloadRequest& operator=(GameDownloadRequest&& message) noexcept;
    GameDownloadRequest& operator=(const Message& message) noexcept;
    GameDownloadRequest& operator=(Message&& message) noexcept;
    bool operator==(const GameDownloadRequest& message) const noexcept;
    bool operator!=(const GameDownloadRequest& message) const noexcept;

    qint64 getGameID(void) const noexcept;
};

} /* namespace lanty */
