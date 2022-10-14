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

#include <qhostaddress.h>
#include <QTcpSocket>

#include "core/ltycore_global.hpp"

#include "user/User.hpp"
#include "network/message/Message.hpp"
#include "game/QGamelist.hpp"

namespace lanty
{

class LTYCORE_EXPORT Connection : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(Connection)

public:
    Connection(void);
    Connection(qintptr socket, QObject* parent = nullptr);
    virtual ~Connection(void);

    User getUser(void);
    void connectToHost(const QHostAddress& address, quint16 port, QIODevice::OpenMode mode = QIODevice::ReadWrite);
    void sendMessage(Message message);

public slots:
    void handleIncomingMessage(void) noexcept;
    void handleDisconnect(void);

signals:
    void userUpdate(User user);
    void gamelistUpdate(QGamelist* gamelist);
    void gamedownloadRequest(User user, Game game);
    void disconnected(User user);

private:
    QTcpSocket socket;
    User user;
};

} /* namespace lanty::server */
