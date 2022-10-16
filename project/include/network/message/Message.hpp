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

#include <nlohmann/json.hpp>
#include <string>

#include "core/JSONSerializable.hpp"
#include "core/ltycore_global.hpp"
#include "network/message/MessageType.hpp"

namespace lanty
{

class LTYCORE_EXPORT Message : public JSONSerializable
{
public:
    static const std::string HEADER_SERIALIZER_KEY;
    static const std::string TYPE_SERIALIZER_KEY;
    static const std::string PAYLOAD_SERIALIZER_KEY;

    Message(MessageType type = MessageType::Type::UNKNOWN) noexcept;
    Message(const Message& message) noexcept;
    Message(Message&& message) noexcept;
    virtual ~Message(void) = default;    // GCOVR_EXCL_LINE

    Message& operator=(const Message& message) noexcept;
    Message& operator=(Message&& message) noexcept;
    bool operator==(const Message& message) const noexcept;
    bool operator!=(const Message& message) const noexcept;

    [[nodiscard]] MessageType getType(void) const noexcept;
    [[nodiscard]] nlohmann::json getHeaderAsJSON(void) const noexcept;
    [[nodiscard]] nlohmann::json getPayloadAsJSON(void) const noexcept;

    [[nodiscard]] nlohmann::json toJSON(void) const override;

    void setPayload(const nlohmann::json& payload) noexcept;

protected:
    MessageType type;
    nlohmann::json payload;
};

} /* namespace lanty */
