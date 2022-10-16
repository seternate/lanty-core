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

#include "core/JSONLoadable.hpp"
#include "network/message/MessageLoader.hpp"

namespace lanty
{

Message MessageLoader::load(const nlohmann::json& json) const
{
    Message message;
    MessageType type;

    if(json.size() == 2)
    {
        nlohmann::json jsonHeader = JSONLoadable::loadFieldAsJSON(json, Message::HEADER_SERIALIZER_KEY);
        if(jsonHeader.is_null() == false)
        {
            type.setType(JSONLoadable::loadFieldAsQString(jsonHeader, Message::TYPE_SERIALIZER_KEY).toStdString());
        }
        message = Message(type);
        message.setPayload(JSONLoadable::loadFieldAsJSON(json, Message::PAYLOAD_SERIALIZER_KEY));
    }

    return message;
}

} /* namespace lanty */
