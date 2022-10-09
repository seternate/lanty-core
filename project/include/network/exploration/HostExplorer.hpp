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

#include <chrono>
#include <QObject>
#include <QTimer>
#include <QUdpSocket>

#include "core/ltycore_global.hpp"

namespace lanty
{

class LTYCORE_EXPORT HostExplorer : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(HostExplorer)

public:
    HostExplorer(std::chrono::milliseconds interval = std::chrono::milliseconds(250));
    virtual ~HostExplorer(void) = default;

    void explore(void) const noexcept;
    void explore(std::chrono::milliseconds interval) noexcept;
    void stopExploring(void) const noexcept;

signals:
    void hostDiscovered(QHostAddress host, qint16 port);

private slots:
    void scan(void) const noexcept;
    void processReply(void) noexcept;

private:
    mutable QUdpSocket socket;
    mutable QTimer timer;
};

} /* namespace lanty */
