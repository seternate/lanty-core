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
