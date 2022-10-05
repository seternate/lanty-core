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

#pragma once

#include <QObject>
#include <QString>

#include "core/ltycore_global.hpp"
#include "user/User.hpp"

namespace lanty
{

class LTYCORE_EXPORT QUser : public QObject, public User
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(QUser)

public:
    QUser(const QString& username = QString(""),
          const QString& gamepath = QString(""),
          const QString& ipAddress = QString(""),
          QObject* parent = nullptr) noexcept;
    QUser(const User& user, QObject* parent = nullptr) noexcept;
    virtual ~QUser(void) = default;

    QUser& operator=(const User& user) noexcept;
    bool operator==(const QUser& user) const noexcept;
    bool operator!=(const QUser& user) const noexcept;

public slots:
    void setUsername(const QString& username) noexcept;
    void setGamepath(const QString& gamepath) noexcept;
    void setResolution(const quint64 x, const quint64 y) noexcept;
    void setResolutionX(const quint64 x) noexcept;
    void setResolutionY(const quint64 y) noexcept;
    void setIPAddress(const QString& ipAddress) noexcept;

signals:
    void usernameChanged(const QString& newUsername);
    void gamepathChanged(const QString& newGamepath);
    void resolutionChanged(const quint64 newX, const quint64 newY);
    void ipaddressChanged(const QString& newIpAddress);
    void changed(void);

private:
    void connectSignals(void) noexcept;
};

} /* namespace lanty */
