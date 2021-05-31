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

#include "user/User.hpp"

namespace lanty
{

const std::string User::USERNAME_SERIALIZER_KEY = "username";
const std::string User::GAMEPATH_SERIALIZER_KEY = "gamepath";
const std::string User::RESOLUTION_SERIALIZER_KEY = "resolution";
const std::string User::RESOLUTION_X_SERIALIZER_KEY = "x";
const std::string User::RESOLUTION_Y_SERIALIZER_KEY = "y";
const std::string User::IPADDRESS_SERIALIZER_KEY = "ip-address";

User::User(const QString& username, const QString& gamepath, const QString& ipAddress) noexcept :
    Serializable(),
    username(username),
    gamepath(gamepath),
    resolutionX(0),
    resolutionY(0),
    ipAddress(ipAddress)
{ }

User::User(const User& user) noexcept :
    Serializable(),
    username(user.getUsername()),
    gamepath(user.getGamepath()),
    resolutionX(user.getResolutionX()),
    resolutionY(user.getResolutionY()),
    ipAddress(user.getIPAddress())
{ }

User::User(User&& user) noexcept :
    Serializable(),
    username(std::move(user.username)),
    gamepath(std::move(user.gamepath)),
    resolutionX(std::move(user.resolutionX)),
    resolutionY(std::move(user.resolutionY)),
    ipAddress(std::move(user.ipAddress))
{ }


User& User::operator=(const User& user) noexcept
{
    this->setUsername(user.getUsername());
    this->setGamepath(user.getGamepath());
    this->setResolution(user.getResolutionX(), user.getResolutionY());
    this->setIPAddress(user.getIPAddress().toString());
    return *this;
}

User& User::operator=(User&& user) noexcept
{
    this->username = std::move(user.username);
    this->gamepath = std::move(user.gamepath);
    this->resolutionX = std::move(user.resolutionX);
    this->resolutionY = std::move(user.resolutionY);
    this->ipAddress = std::move(user.ipAddress);

    return *this;
}

bool User::operator==(const User& user) const noexcept
{
    return this->username == user.username && this->gamepath == user.gamepath && this->resolutionX == user.resolutionX
           && this->resolutionY == user.resolutionY && this->ipAddress.isEqual(user.ipAddress);
}

bool User::operator!=(const User& user) const noexcept
{
    return !(*this == user);
}

bool User::operator<(const User& user) const noexcept
{
    return this->getUsername().compare(user.getUsername(), Qt::CaseSensitivity::CaseInsensitive);
}


const QString& User::getUsername(void) const noexcept
{
    return this->username;
}

const QString& User::getGamepath(void) const noexcept
{
    return this->gamepath;
}

quint64 User::getResolutionX(void) const noexcept
{
    return this->resolutionX;
}

quint64 User::getResolutionY(void) const noexcept
{
    return this->resolutionY;
}

const QHostAddress& User::getIPAddress(void) const noexcept
{
    return this->ipAddress;
}


void User::setUsername(const QString& username) noexcept
{
    this->username = username;
}

void User::setGamepath(const QString& gamepath) noexcept
{
    this->gamepath = gamepath;
}

void User::setResolution(const quint64 x, const quint64 y) noexcept
{
    this->resolutionX = x;
    this->resolutionY = y;
}

void User::setResolutionX(const quint64 x) noexcept
{
    this->resolutionX = x;
}

void User::setResolutionY(const quint64 y) noexcept
{
    this->resolutionY = y;
}

void User::setIPAddress(const QString& ipAddress) noexcept
{
    this->ipAddress.setAddress(ipAddress);
}


nlohmann::json User::toJSON(void) const
{
    nlohmann::json json = nlohmann::json::object();

    if (this->getUsername().isEmpty() == false)
    {
        json[User::USERNAME_SERIALIZER_KEY] = this->getUsername().toStdString();
    }
    if (this->getGamepath().isEmpty() == false)
    {
        json[User::GAMEPATH_SERIALIZER_KEY] = this->getGamepath().toStdString();
    }
    if (this->getResolutionX() != 0)
    {
        json[User::RESOLUTION_SERIALIZER_KEY][User::RESOLUTION_X_SERIALIZER_KEY] = this->getResolutionX();
    }
    if (this->getResolutionY() != 0)
    {
        json[User::RESOLUTION_SERIALIZER_KEY][User::RESOLUTION_Y_SERIALIZER_KEY] = this->getResolutionY();
    }
    if (this->getIPAddress().isNull() == false)
    {
        json[User::IPADDRESS_SERIALIZER_KEY] = this->getIPAddress().toString().toStdString();
    }

    return json;
}

YAML::Node User::toYAML(void) const
{
    YAML::Node yaml;

    if (this->getUsername().isEmpty() == false)
    {
        yaml[User::USERNAME_SERIALIZER_KEY] = this->getUsername().toStdString();
    }
    if (this->getGamepath().isEmpty() == false)
    {
        yaml[User::GAMEPATH_SERIALIZER_KEY] = this->getGamepath().toStdString();
    }
    if (this->getResolutionX() != 0)
    {
        yaml[User::RESOLUTION_SERIALIZER_KEY][User::RESOLUTION_X_SERIALIZER_KEY] = this->getResolutionX();
    }
    if (this->getResolutionY() != 0)
    {
        yaml[User::RESOLUTION_SERIALIZER_KEY][User::RESOLUTION_Y_SERIALIZER_KEY] = this->getResolutionY();
    }
    if (this->getIPAddress().isNull() == false)
    {
        yaml[User::IPADDRESS_SERIALIZER_KEY] = this->getIPAddress().toString().toStdString();
    }

    return yaml;
}

} /* namespace lanty */
