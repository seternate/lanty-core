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

#include <yaml-cpp/yaml.h>
#include <QHostAddress>
#include <QString>
#include <nlohmann/json.hpp>
#include <string>

#include "core/Serializable.hpp"
#include "core/ltycore_global.hpp"

namespace lanty
{

class LTYCORE_EXPORT User : public Serializable
{
public:
    static const std::string USERNAME_SERIALIZER_KEY;
    static const std::string GAMEPATH_SERIALIZER_KEY;
    static const std::string RESOLUTION_SERIALIZER_KEY;
    static const std::string RESOLUTION_X_SERIALIZER_KEY;
    static const std::string RESOLUTION_Y_SERIALIZER_KEY;
    static const std::string IPADDRESS_SERIALIZER_KEY;

    User(const QString& username = QString(""),
         const QString& gamepath = QString(""),
         const QString& ipAddress = QString("")) noexcept;
    User(const User& user) noexcept;
    User(User&& user) noexcept;
    virtual ~User(void) = default;    // GCOVR_EXCL_LINE

    User& operator=(const User& user) noexcept;
    User& operator=(User&& user) noexcept;
    bool operator==(const User& user) const noexcept;
    bool operator!=(const User& user) const noexcept;
    bool operator<(const User& user) const noexcept;

    const QString& getUsername(void) const noexcept;
    const QString& getGamepath(void) const noexcept;
    quint64 getResolutionX(void) const noexcept;
    quint64 getResolutionY(void) const noexcept;
    const QHostAddress& getIPAddress(void) const noexcept;

    virtual void setUsername(const QString& username) noexcept;
    virtual void setGamepath(const QString& gamepath) noexcept;
    virtual void setResolution(const quint64 x, const quint64 y) noexcept;
    virtual void setResolutionX(const quint64 x) noexcept;
    virtual void setResolutionY(const quint64 y) noexcept;
    virtual void setIPAddress(const QString& ipAddress) noexcept;

    nlohmann::json toJSON(void) const override;
    YAML::Node toYAML(void) const override;

private:
    QString username;
    QString gamepath;
    quint64 resolutionX;
    quint64 resolutionY;
    QHostAddress ipAddress;
};

} /* namespace lanty */
