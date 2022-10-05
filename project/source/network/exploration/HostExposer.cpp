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

#include <QAbstractSocket>

#include <nlohmann/json.hpp>

#include "network/message/AddressMessage.hpp"
#include "network/message/MessageLoader.hpp"
#include "network/exploration/HostExploration.hpp"
#include "network/exploration/HostExposer.hpp"

namespace lanty
{

HostExposer::HostExposer(void) :
    QObject(nullptr),
    socket(this),
    message()
{
    QObject::connect(&socket, SIGNAL(readyRead(void)), this, SLOT(processRequest(void)));
}

void HostExposer::expose(const QHostAddress &address, quint16 port) noexcept
{
    this->message = AddressMessage(address, port);

    for(quint16 port : HostExploration::HOST_DISCOVER_PORTS)
    {
        if(socket.bind(QHostAddress::AnyIPv4, port, QAbstractSocket::DefaultForPlatform) == true)
        {
            break;
        }
    }
}

void HostExposer::stopExposing(void) const noexcept
{
    this->socket.close();
}

void HostExposer::processRequest(void)
{
    QByteArray datagram;
    QHostAddress host;
    quint16 port;

    while(this->socket.hasPendingDatagrams() == true) {
        datagram.resize(this->socket.pendingDatagramSize());
        this->socket.readDatagram(datagram.data(), datagram.size(), &host, &port);

        nlohmann::json requestJSON = nlohmann::json::parse(datagram.toStdString());
        Message requestMessage = MessageLoader().load(requestJSON);

        if(requestMessage.getType() == MessageType(MessageType::Type::ADDRESS))
        {
            socket.writeDatagram(this->message.toJSON().dump().data(), host, port);
        }
    }
}

} /* namespace lanty */
