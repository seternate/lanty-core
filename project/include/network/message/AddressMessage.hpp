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

namespace lanty
{

class LTYCORE_EXPORT AddressMessage : public Message
{
public:
    static const std::string HOST_SERIALIZER_KEY;
    static const std::string PORT_SERIALIZER_KEY;

    AddressMessage(void) = delete;
    AddressMessage(AddressMessage& message) noexcept;
    AddressMessage(AddressMessage&& message) noexcept;
    AddressMessage(Message& message) noexcept;
    AddressMessage(Message&& message) noexcept;
    AddressMessage(const QHostAddress& host, quint16 port) noexcept;
    virtual ~AddressMessage(void) = default;    // GCOVR_EXCL_LINE

    AddressMessage& operator=(const AddressMessage& message) noexcept;
    AddressMessage& operator=(AddressMessage&& message) noexcept;
    AddressMessage& operator=(const Message& message) noexcept;
    AddressMessage& operator=(Message&& message) noexcept;
    bool operator==(const AddressMessage& message) const noexcept;
    bool operator!=(const AddressMessage& message) const noexcept;

    QHostAddress getHost(void) const noexcept;
    QString getHostAsString(void) const noexcept;
    quint16 getPort(void) const noexcept;
};

} /* namespace lanty */
