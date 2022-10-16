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

#include <nlohmann/json.hpp>

#include "network/Connection.hpp"
#include "network/message/GameDownloadReply.hpp"
#include "network/message/GameDownloadRequest.hpp"
#include "network/message/MessageLoader.hpp"
#include "network/message/MessageType.hpp"
#include "network/message/UserMessage.hpp"
#include "network/message/GamelistMessage.hpp"

namespace lanty
{

Connection::Connection(void) :
    QObject(nullptr),
    socket(this),
    user()
{
    QObject::connect(&(this->socket), SIGNAL(readyRead(void)), this, SLOT(handleIncomingMessage(void)));
    QObject::connect(&(this->socket), SIGNAL(disconnected(void)), this, SLOT(handleDisconnect(void)));
    QObject::connect(&(this->socket), SIGNAL(disconnected()), this, SIGNAL(disconnected()));

}

Connection::Connection(qintptr socket, QObject* parent) :
    QObject(parent),
    socket(this),
    user()
{
    bool successfullySetSocket = this->socket.setSocketDescriptor(socket);
    if (!successfullySetSocket)
    {
        throw std::runtime_error("SocketDescriptor can not be set. (SocketDescriptor: " + std::to_string(socket));
    }

    QObject::connect(&(this->socket), SIGNAL(readyRead(void)), this, SLOT(handleIncomingMessage(void)));
    QObject::connect(&(this->socket), SIGNAL(disconnected(void)), this, SLOT(handleDisconnect(void)));
    QObject::connect(&(this->socket), SIGNAL(disconnected()), this, SIGNAL(disconnected()));
}

Connection::~Connection(void)
{
    qDebug() << "Destructor Connection";
    QObject::disconnect(&(this->socket), SIGNAL(readyRead(void)), this, SLOT(handleIncomingMessage(void)));
    QObject::disconnect(&(this->socket), SIGNAL(disconnected(void)), this, SLOT(handleDisconnect(void)));
    QObject::disconnect(&(this->socket), SIGNAL(disconnected()), this, SIGNAL(disconnected()));
    //this->socket.close();
}

void Connection::sendData(QString gamepath)
{
    qDebug() << "Send data";
    QFile gamefile(gamepath);
    gamefile.open(QIODevice::ReadOnly);
    qint64 gamesize = gamefile.size();

    qDebug() << gamesize;
    qDebug() << gamepath;
    qDebug() << this->socket.socketDescriptor();

    int buffersize = 1024;
    char* buffer = new char[buffersize];

    qint64 totalread = 0;

    while(totalread < gamesize)
    {
        int read = gamefile.read(buffer, buffersize);
        totalread += read;

        this->socket.write(buffer, read);
        this->socket.flush();
    }

    qDebug() << "data send";

    delete[] buffer;
    gamefile.close();
}


User Connection::getUser(void)
{
    return this->user;
}

void Connection::handleIncomingMessage(void) noexcept
{
    static QStringList messageOverFlow;
    QByteArray buffer;
    QByteArray rawMessage;

    while(this->socket.bytesAvailable() > 0)
    {
        buffer.resize(this->socket.bytesAvailable());
        qint64 byteRead = this->socket.read(buffer.data(), buffer.size());
        if(byteRead > 0)
        {
            rawMessage.append(buffer.constData(), byteRead);
        }
    }

    if(this->gamedownloadMode == true)
    {
        this->gamedownloadSize -= rawMessage.size();
        emit this->gamedownloadReply(this->gameid, this->gamedownloadSize, rawMessage);
        return;
    }

    QStringList messageList = QString::fromStdString(rawMessage.toStdString()).split("\n\r\n\r");

    //Remove empty items in messageList
    messageList.removeAll("");

    for(quint64 i = 0; i < messageList.size(); i ++)
    {
        QString messageString = messageList.at(i);

        try
        {
            nlohmann::json jsonMessage = nlohmann::json::parse(messageString.toStdString());

            Message message = MessageLoader().load(jsonMessage);

            if(message.getType() == MessageType(MessageType::Type::UNKNOWN))
            {
                qDebug() << "UNKNOWN message: " << messageString;
            }

            QGamelist* gamelist = nullptr;

            switch(message.getType())
            {
            case MessageType::Type::USER:
                this->user = static_cast<UserMessage>(message).getUser();
                emit userUpdate(this->getUser());
                break;
            case MessageType::Type::GAMELIST:
                gamelist = static_cast<GamelistMessage>(message).getGamelist();
                emit gamelistUpdate(gamelist);
                break;
            case MessageType::Type::GAMEDOWNLOAD_REQUEST:
                emit gamedownloadRequest(this->user, static_cast<GameDownloadRequest>(message).getGameID());
                break;
            case MessageType::Type::GAMEDOWNLOAD_REPLY:
                this->gamedownloadMode = true;
                this->gamedownloadSize = static_cast<GameDownloadReply>(message).getGameSize();
                this->gameid = static_cast<GameDownloadReply>(message).getGameID();
                //emit this->gamedownloadReply(static_cast<GameDownloadReply>(message).getGameID(), static_cast<GameDownloadReply>(message).getGameSize());
            default: break;
            }
        }
        catch(std::exception& exception){
            //qDebug().nospace() << "Can not parse message: \n"<< i << " : " << messageString << "\n\n";

            if(messageList.indexOf(messageString) == 0)
            {
                messageOverFlow.append(messageString);
                messageList.removeOne(messageString);
                messageList.push_front(messageOverFlow.at(0) + messageOverFlow.at(1));
                i--;
            }
            else if(messageList.indexOf(messageString) == messageList.size() - 1)
            {
                messageOverFlow = QStringList();
                messageOverFlow.append(messageString);
            }
        }
    }
}

void Connection::connectToHost(const QHostAddress& address, quint16 port, QIODevice::OpenMode mode)
{
    this->socket.connectToHost(address, port, mode);
    this->socket.waitForConnected();
}

QHostAddress Connection::peerAddress(void) const
{
    return this->socket.peerAddress();
}

qint16 Connection::peerPort(void) const
{
    return this->socket.peerPort();
}

void Connection::sendMessage(const Message& message)
{
    this->socket.write(message.toJSON().dump().c_str());
    this->socket.write("\n\r\n\r");
    this->socket.flush();

}

void Connection::handleDisconnect(void)
{
    emit this->disconnected(this->getUser());
}

void Connection::close()
{
    this->socket.close();
}

}    // namespace lanty::server
