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
}

Connection::~Connection(void)
{
    this->socket.close();
}


User Connection::getUser(void)
{
    return this->user;
}

void Connection::handleIncomingMessage(void) noexcept
{
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

    QStringList messageList = QString::fromStdString(rawMessage.toStdString()).split("\n\r\n\r");

    //Remove empty items in messageList
    messageList.removeAll("");

    for(QString messageString : messageList)
    {
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
                qDebug() << "GAMELIST" << gamelist->toJSON().dump().c_str();
                emit gamelistUpdate(gamelist);
                break;
            default: break;
            }
        }
        catch(std::exception& exception){
            qDebug() << "Can not parse message: " << messageString;
        }
    }

    //QByteArray jsonData;
    //QDataStream socketStream(this->socket);
    //socketStream.setVersion(QDataStream::Qt_5_14);
    //for (;;)
    //{
    //    socketStream.startTransaction();
    //    socketStream >> jsonData;
    //    if (socketStream.commitTransaction())
    //    {
    //        nlohmann::json json = nlohmann::json::object();
    //        Message* message = nullptr;
    //        try
    //        {
    //            json = nlohmann::json::parse(jsonData.toStdString());
    //            message = MessageFactory::createMessage(json);
//
    //            message->handle();
//
    //            /*
    //            lanty::UserLoader userloader;
//
    //            switch (message->getType())
    //            {
    //                case Message::Type::LOGIN:
    //                    this->user->operator=(userloader.load(message->getData()["user"]));
    //                    emit this->login();
    //                    break;
    //                case Message::Type::LOGOUT:
    //                    this->socket->close();
    //                    break;
    //                case Message::Type::USERLIST:
    //                    qDebug() << "USERLIST";
    //                    break;
    //                case Message::Type::UNKNOWN:
    //                default:
    //                    break;
    //            }
    //            */
    //        }
    //        catch (nlohmann::json::parse_error& e)
    //        {
    //            qDebug() << "Invalid message: " + QString::fromUtf8(jsonData);
    //            qDebug() << "Exception: " + QString::fromStdString(e.what());
    //        }
//
    //        if (message != nullptr)
    //        {
    //            qDebug() << message->getData().dump().c_str();
    //        }
    //    }
    //    else
    //    {
    //        break;
    //    }
    //}
}

void Connection::connectToHost(const QHostAddress& address, quint16 port, QIODevice::OpenMode mode)
{
    this->socket.connectToHost(address, port, mode);
}

void Connection::sendMessage(Message message)
{
    qDebug() << "Address" << this->socket.peerAddress().toString() << this->socket.peerPort();
    this->socket.write(message.toJSON().dump().data());
    this->socket.write("\n\r\n\r");
}

void Connection::handleDisconnect(void)
{
    emit this->disconnected(this->getUser());
}

}    // namespace lanty::server
