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

#ifndef USER_USER_HPP
#define USER_USER_HPP

#include <QHostAddress>
#include <QObject>
#include <QString>

#include "core/ltycore_global.hpp"

namespace lanty
{

class LTYCORE_EXPORT User : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(User)

public:
    User(void) = default;
    User(const QString& username);
    virtual ~User(void) = default;

    bool operator==(const User& game) const;
    bool operator!=(const User& game) const;

    virtual QString getUsername(void) const;
    virtual QString getGamepath(void) const;
    virtual quint32 getResolutionX(void) const;
    virtual quint32 getResolutionY(void) const;
    virtual QString getIPAddress(void) const;

    virtual void setUsername(const QString& username);
    virtual void setGamepath(const QString& gamepath);
    virtual void setResolution(const quint32 x, const quint32 y);
    virtual void setResolutionX(const quint32 x);
    virtual void setResolutionY(const quint32 y);
    virtual void setIPAddress(const QString& ipAddress);

signals:
    void changed(void);
    void usernameChanged(QString newUsername);
    void gamepathChanged(QString newGamepath);
    void resolutionChanged(quint32 newResolutionX, const quint32 newResolutionY);
    void ipAddressChanged(QString newIPAddress);

private:
    QString username;
    QString gamepath;
    quint32 resolutionX;
    quint32 resolutionY;
    QHostAddress ipAddress;
};

} /* namespace lanty */

#endif /* USER_USER_HPP */
