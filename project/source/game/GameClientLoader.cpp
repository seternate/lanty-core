/* Copyright <2021> <Levin Jeck>
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

#include "game/GameClientLoader.hpp"

namespace lanty
{

GameClient GameClientLoader::load(const YAML::Node& yaml) const
{
    GameClient gameclient;

    gameclient.setExecutableFilePath(YAMLLoadable::loadFieldAsQString(yaml, GameClient::EXECUTABLE_FILE_PATH_SERIALIZER_KEY));
    gameclient.setArgument(YAMLLoadable::loadFieldAsQString(yaml, GameClient::ARGUMENT_SERIALIZER_KEY));
    gameclient.setConnectArgument(YAMLLoadable::loadFieldAsQString(yaml, GameClient::CONNECT_ARGUMENT_SERIALIZER_KEY));

    return gameclient;
}

GameClient GameClientLoader::load(const nlohmann::json& json) const
{
    GameClient gameclient;

    gameclient.setExecutableFilePath(JSONLoadable::loadFieldAsQString(json, GameClient::EXECUTABLE_FILE_PATH_SERIALIZER_KEY));
    gameclient.setArgument(JSONLoadable::loadFieldAsQString(json, GameClient::ARGUMENT_SERIALIZER_KEY));
    gameclient.setConnectArgument(JSONLoadable::loadFieldAsQString(json, GameClient::CONNECT_ARGUMENT_SERIALIZER_KEY));

    return gameclient;
}

} /* namespace lanty */
