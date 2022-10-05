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

#include "user/QUser.hpp"

namespace lanty
{

QUser::QUser(const QString& username, const QString& gamepath, const QString& ipAddress, QObject* parent) noexcept :
    QObject(parent),
    User(username, gamepath, ipAddress)
{
    this->connectSignals();
}

QUser::QUser(const User& user, QObject* parent) noexcept : QObject(parent), User(user)
{
    this->connectSignals();
}


QUser& QUser::operator=(const User& user) noexcept
{
    User::operator=(user);
    return *this;
}

bool QUser::operator==(const QUser& user) const noexcept
{
    return User::operator==(user);
}

bool QUser::operator!=(const QUser& user) const noexcept
{
    return User::operator!=(user);
}


void QUser::setUsername(const QString& username) noexcept
{
    User::setUsername(username);
    emit this->usernameChanged(this->getUsername());
}

void QUser::setGamepath(const QString& gamepath) noexcept
{
    User::setGamepath(gamepath);
    emit this->gamepathChanged(this->getGamepath());
}

void QUser::setResolution(const quint64 x, const quint64 y) noexcept
{
    User::setResolution(x, y);
    emit this->resolutionChanged(this->getResolutionX(), this->getResolutionY());
}

void QUser::setResolutionX(const quint64 x) noexcept
{
    User::setResolutionX(x);
    emit this->resolutionChanged(this->getResolutionX(), this->getResolutionY());
}

void QUser::setResolutionY(const quint64 y) noexcept
{
    User::setResolutionY(y);
    emit this->resolutionChanged(this->getResolutionX(), this->getResolutionY());
}

void QUser::setIPAddress(const QString& ipAddress) noexcept
{
    User::setIPAddress(ipAddress);
    emit this->ipaddressChanged(this->getIPAddress().toString());
}


void QUser::connectSignals(void) noexcept
{
    QObject::connect(this, SIGNAL(usernameChanged(const QString&)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(gamepathChanged(const QString&)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(resolutionChanged(const quint64, const quint64)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(ipaddressChanged(const QString&)), this, SIGNAL(changed(void)));
}

} /* namespace lanty */
