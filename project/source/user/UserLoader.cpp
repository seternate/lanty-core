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

#include "user/UserLoader.hpp"

namespace lanty
{

User UserLoader::load(const YAML::Node& yaml) const
{
    User user;

    user.setUsername(YAMLLoadable::loadFieldAsQString(yaml, User::USERNAME_SERIALIZER_KEY));
    user.setGamepath(YAMLLoadable::loadFieldAsQString(yaml, User::GAMEPATH_SERIALIZER_KEY));
    YAML::Node yamlResolution = YAMLLoadable::loadFieldAsYAML(yaml, User::RESOLUTION_SERIALIZER_KEY);
    if (yamlResolution.IsNull() == false)
    {
        qint64 X = YAMLLoadable::loadFieldAsInteger(yamlResolution, User::RESOLUTION_X_SERIALIZER_KEY);
        qint64 Y = YAMLLoadable::loadFieldAsInteger(yamlResolution, User::RESOLUTION_Y_SERIALIZER_KEY);
        user.setResolution(X, Y);
    }
    user.setIPAddress(YAMLLoadable::loadFieldAsQString(yaml, User::IPADDRESS_SERIALIZER_KEY));

    return user;
}

User UserLoader::load(const nlohmann::json& json) const
{
    User user;

    user.setUsername(JSONLoadable::loadFieldAsQString(json, User::USERNAME_SERIALIZER_KEY));
    user.setGamepath(JSONLoadable::loadFieldAsQString(json, User::GAMEPATH_SERIALIZER_KEY));
    nlohmann::json jsonResolution = JSONLoadable::loadFieldAsJSON(json, User::RESOLUTION_SERIALIZER_KEY);
    if (jsonResolution.is_null() == false)
    {
        qint64 X = JSONLoadable::loadFieldAsInteger(jsonResolution, User::RESOLUTION_X_SERIALIZER_KEY);
        qint64 Y = JSONLoadable::loadFieldAsInteger(jsonResolution, User::RESOLUTION_Y_SERIALIZER_KEY);
        user.setResolution(X, Y);
    }
    user.setIPAddress(JSONLoadable::loadFieldAsQString(json, User::IPADDRESS_SERIALIZER_KEY));

    return user;
}

} /* namespace lanty */
