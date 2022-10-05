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

#include <QHostAddress>

#include "network/exploration/HostExploration.hpp"
#include "network/exploration/HostExplorer.hpp"
#include "network/message/AddressMessage.hpp"
#include "network/message/MessageLoader.hpp"

namespace lanty
{

HostExplorer::HostExplorer(std::chrono::milliseconds interval) :
    QObject(nullptr),
    socket(this),
    timer(this)
{
    QObject::connect(&(this->timer), SIGNAL(timeout(void)), this, SLOT(scan(void)));
    QObject::connect(&(this->socket), SIGNAL(readyRead(void)), this, SLOT(processReply(void)));

    timer.setInterval(interval);
}


void HostExplorer::explore(void) const noexcept
{
    this->timer.start();
}

void HostExplorer::explore(std::chrono::milliseconds interval) noexcept
{
    this->timer.setInterval(interval);
    this->explore();
}

void HostExplorer::stopExploring(void) const noexcept
{
    this->timer.stop();
}


void HostExplorer::scan(void) const noexcept
{
    Message message = AddressMessage(QHostAddress(), 0);

    for(quint16 port : HostExploration::HOST_DISCOVER_PORTS)
    {
        this->socket.writeDatagram(message.toJSON().dump().data(), QHostAddress::Broadcast, port);
    }
}

void HostExplorer::processReply(void) noexcept
{
    QByteArray datagram;
    QHostAddress host;
    quint16 port;

    while (this->socket.hasPendingDatagrams() == true) {
        datagram.resize(this->socket.pendingDatagramSize());
        this->socket.readDatagram(datagram.data(), datagram.size(), &host, &port);

        nlohmann::json replyJSON = nlohmann::json::parse(datagram.toStdString());
        AddressMessage replyMessage = MessageLoader().load(replyJSON);

        if(replyMessage.getType() == MessageType(MessageType::Type::ADDRESS)){
            this->stopExploring();
            qDebug() << replyMessage.getHostAsString() << replyMessage.getPort();
            emit this->hostDiscovered(replyMessage.getHost(), replyMessage.getPort());
        }
    }
}

} /* namespace lanty */
