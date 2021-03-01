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

#ifndef MOCK_MOCKUSER_HPP
#define MOCK_MOCKUSER_HPP

#include <gmock/gmock.h>

#include "user/User.hpp"

class MockUser : public lanty::User
{
public:
    MOCK_METHOD(QString, getUsername, (), (const, override));
    MOCK_METHOD(QString, getGamepath, (), (const, override));
    MOCK_METHOD(quint32, getResolutionX, (), (const, override));
    MOCK_METHOD(quint32, getResolutionY, (), (const, override));
    MOCK_METHOD(QString, getIPAddress, (), (const, override));
    MOCK_METHOD(void, setUsername, (const QString& username), (override));
    MOCK_METHOD(void, setGamepath, (const QString& gamepath), (override));
    MOCK_METHOD(void, setResolution, (const quint32 x, const quint32 y), (override));
    MOCK_METHOD(void, setResolutionX, (const quint32 x), (override));
    MOCK_METHOD(void, setResolutionY, (const quint32 y), (override));
    MOCK_METHOD(void, setIPAddress, (const QString& ipAddress), (override));
};

#endif /* MOCK_MOCKUSER_HPP */
