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

User::User(QObject* parent) : QObject(parent) { }

User::User(const QString& username, QObject* parent) :
    QObject(parent),
    username(username),
    gamepath(""),
    resolutionX(0),
    resolutionY(0),
    ipAddress()
{ }


bool User::operator==(const lanty::User& game) const
{
    return this->username == game.username && this->gamepath == game.gamepath && this->resolutionX == game.resolutionX
           && this->resolutionY == game.resolutionY && this->ipAddress == game.ipAddress;
}

bool User::operator!=(const lanty::User& game) const
{
    return !(*this == game);
}


QString User::getUsername(void) const
{
    return this->username;
}

QString User::getGamepath(void) const
{
    return this->gamepath;
}

quint32 User::getResolutionX(void) const
{
    return this->resolutionX;
}

quint32 User::getResolutionY(void) const
{
    return this->resolutionY;
}

QString User::getIPAddress(void) const
{
    return this->ipAddress.toString();
}


void User::setUsername(const QString& username)
{
    this->username = username;

    emit this->usernameChanged(this->username);
    emit this->changed();
}

void User::setGamepath(const QString& gamepath)
{
    this->gamepath = gamepath;

    emit this->gamepathChanged(this->gamepath);
    emit this->changed();
}

void User::setResolution(const quint32 x, const quint32 y)
{
    this->resolutionX = x;
    this->resolutionY = y;

    emit this->resolutionChanged(this->resolutionX, this->resolutionY);
    emit this->changed();
}

void User::setResolutionX(const quint32 x)
{
    this->setResolution(x, this->resolutionY);
}

void User::setResolutionY(const quint32 y)
{
    this->setResolution(this->resolutionX, y);
}

void User::setIPAddress(const QString& ipAddress)
{
    this->ipAddress = QHostAddress(ipAddress);

    emit this->ipAddressChanged(this->getIPAddress());
    emit this->changed();
}


nlohmann::json* User::toJSON(void) const
{
    nlohmann::json* json = new nlohmann::json({});
    nlohmann::json userjson({});

    userjson["username"] = this->getUsername().toStdString();
    userjson["gamepath"] = this->getGamepath().toStdString();
    userjson["resolution"]["x"] = this->getResolutionX();
    userjson["resolution"]["y"] = this->getResolutionY();
    userjson["ip-address"] = this->getIPAddress().toStdString();

    (*json)["user"] = userjson;

    return json;
}

bool User::fromJSON(const nlohmann::json& json)
{
    nlohmann::json userjson = json["user"];

    this->setUsername(QString::fromStdString(userjson["username"]));
    this->setGamepath(QString::fromStdString(userjson["gamepath"]));
    this->setResolutionX(userjson["resolution"]["x"]);
    this->setResolutionY(userjson["resolution"]["y"]);
    this->setIPAddress(QString::fromStdString(userjson["ip-address"]));

    return true;
}

} /* namespace lanty */
