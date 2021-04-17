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
#include <QPixmap>
#include <QString>
#include <nlohmann/json.hpp>
#include <string>

#include "core/ltycore_global.hpp"
#include "game/GameClient.hpp"
#include "game/GameServer.hpp"
#include "game/GameVersion.hpp"

namespace lanty
{

class LTYCORE_EXPORT Game : public Serializable
{
public:
    static const std::string NAME_SERIALIZER_KEY;
    static const std::string ARCHIVE_SERIALIZER_KEY;
    static const std::string VERSION_SERIALIZER_KEY;
    static const std::string CLIENT_SERIALIZER_KEY;
    static const std::string SERVER_SERIALIZER_KEY;

    Game(const QString& name = QString(""),
         const QString& archiveFilePath = QString(""),
         const GameClient& client = GameClient(),
         const GameServer& server = GameServer(),
         const GameVersion& version = GameVersion()) noexcept;
    Game(const Game& game) noexcept;
    Game(Game&& game) = delete;
    virtual ~Game(void) = default;    // GCOVR_EXCL_LINE

    Game& operator=(const Game& game) noexcept;
    Game& operator=(Game&& game) = delete;
    bool operator==(const Game& game) const noexcept;
    bool operator!=(const Game& game) const noexcept;

    const QString& getName(void) const noexcept;
    const QString& getArchiveFileName(void) const noexcept;
    const GameClient& getClient(void) const noexcept;
    const GameServer& getServer(void) const noexcept;
    const GameVersion& getVersion(void) const noexcept;
    const QPixmap& getCover(void) const noexcept;
    const QPixmap& getIcon(void) const noexcept;

    virtual void setName(const QString& name) noexcept;
    virtual void setArchiveFileName(const QString& archiveFileName) noexcept;
    virtual void setClientExecutableFilePath(const QString& clientExecutableFilePath) noexcept;
    virtual void setClientArgument(const QString& clientArgument) noexcept;
    virtual void setClientConnectArgument(const QString& clientConnectArgument) noexcept;
    virtual void setServerExecutableFilePath(const QString& serverExecutableFilePath) noexcept;
    virtual void setServerArgument(const QString& serverArgument) noexcept;
    virtual void setVersion(const QString& version) noexcept;
    virtual void setVersionSource(const GameVersion::Source versionSource) noexcept;
    virtual void setVersionFilePath(const QString& versionFilePath) noexcept;
    virtual void setVersionFileQuery(const QString& versionFileQuery) noexcept;
    virtual void setCover(const QPixmap& cover) noexcept;
    virtual void setIcon(const QPixmap& icon) noexcept;

    nlohmann::json toJSON(void) const override;
    YAML::Node toYAML(void) const override;

private:
    QString name;
    QString archiveFileName;
    GameClient client;
    GameServer server;
    GameVersion version;
    QPixmap cover;
    QPixmap icon;
};

} /* namespace lanty */
