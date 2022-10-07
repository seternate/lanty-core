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
#include "user/User.hpp"

namespace lanty
{

class LTYCORE_EXPORT UserMessage : public Message
{
public:
    static const std::string USER_SERIALIZER_KEY;

    UserMessage(void) = delete;
    UserMessage(UserMessage& message) noexcept;
    UserMessage(UserMessage&& message) noexcept;
    UserMessage(Message& message) noexcept;
    UserMessage(Message&& message) noexcept;
    UserMessage(const User& user) noexcept;
    virtual ~UserMessage(void) = default;    // GCOVR_EXCL_LINE

    UserMessage& operator=(const UserMessage& message) noexcept;
    UserMessage& operator=(UserMessage&& message) noexcept;
    UserMessage& operator=(const Message& message) noexcept;
    UserMessage& operator=(Message&& message) noexcept;
    bool operator==(const UserMessage& message) const noexcept;
    bool operator!=(const UserMessage& message) const noexcept;

    User getUser(void) const noexcept;
};

} /* namespace lanty */
