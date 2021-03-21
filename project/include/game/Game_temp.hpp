/* Copyright <2020> <Levin Jeck>
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

#ifndef GAME_GAME_HPP
#define GAME_GAME_HPP

#include <QObject>
#include <QString>

#include "core/ltycore_global.hpp"
#include "game/GameData.hpp"
#include "game/GameVersionSource.hpp"
#include "serializer/Serializable.hpp"
#include "yaml/YamlNode.hpp"

namespace lanty
{

class LTYCORE_EXPORT Game : public QObject, public Serializable, public GameData
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(Game);

public:
    explicit Game(QObject* parent = nullptr);
    explicit Game(const YamlNode& yamlNode);
    virtual ~Game(void) = default;

    bool operator==(const Game& game) const;
    bool operator!=(const Game& game) const;

    // bool fromJSON(const nlohmann::json& json) override;
    // bool fromYAML(const YamlNode& yaml) override;

    // nlohmann::json* toJSON(void) const override;
    // virtual YamlNode* toYAML(void) const override;

public slots:
    void setName(const QString& name) noexcept override;
    void setArchiveFileName(const QString& archiveFileName) noexcept override;
    void setClientExecutableRelativeFilePath(const QString& clientExecutableRelativeFilePath) noexcept override;
    void setClientArgument(const QString& clientArgument) noexcept override;
    void setClientConnectArgument(const QString& clientConnectArgument) noexcept override;
    void setServerExecutableRelativeFilePath(const QString& serverExecutableRelativeFilePath) noexcept override;
    void setServerArgument(const QString& serverArgument) noexcept override;
    void setVersion(const QString& version) noexcept override;
    void setVersionSource(const GameVersionSource gameVersionSource) noexcept override;
    void setVersionRelativeFilePath(const QString& versionRelativeFilePath) noexcept override;
    void setVersionFileQuery(const QString& versionFileQuery) noexcept override;
    void setCoverImage(const QPixmap& coverImage) noexcept override;
    void setIconImage(const QPixmap& iconImage) noexcept override;

    // virtual bool deleteYamlFile(void);
    // virtual bool save(void);
    // virtual bool save(const QString& yamlFilePath);

signals:
    void changed(void);
    void nameChanged(const QString& newName);
    void archiveFileNameChanged(const QString& newArchiveFileName);
    void clientExecutableChanged(const QString& newClientExecutable);
    void clientArgumentChanged(const QString& newClientArgument);
    void clientConnectArgumentChanged(const QString& newClientConnectArgument);
    void serverExecutableChanged(const QString& newServerExecutable);
    void serverArgumentChanged(const QString& newServerArgument);
    void versionChanged(const QString& newVersion);
    void versionSourceChanged(GameVersionSource newGameVersionSource);
    void versionFileChanged(const QString& newVersionFile);
    void versionFileQueryChanged(const QString& newVersionFile);
    void coverImageChanged(const QPixmap& newCoverImage);
    void iconImageChanged(const QPixmap& newIconImage);

private:
    // void loadGameYAML(const YamlNode& gameNode);
    // void loadVersionYAML(const YamlNode& versionNode);
    // void loadClientYAML(const YamlNode& clientNode);
    // void loadServerYAML(const YamlNode& serverNode);

    // void loadGameJSON(const nlohmann::json& gameJSON);
    // void loadVersionJSON(const nlohmann::json& versionJSON);
    // void loadClientJSON(const nlohmann::json& clientJSON);
    // void loadServerJSON(const nlohmann::json& serverJSON);

    // void createGameNode(YamlNode& gameNode) const;
    // void createVersionNode(YamlNode& versionNode) const;
    // void createClientNode(YamlNode& clientNode) const;
    // void createServerNode(YamlNode& serverNode) const;

    // void createGameJSON(nlohmann::json& gameJSON) const;
    // void createVersionJSON(nlohmann::json& versionJSON) const;
    // void createClientJSON(nlohmann::json& clientJSON) const;
    // void createServerJSON(nlohmann::json& serverJSON) const;

    QString yamlFilePath;
};

} /* namespace lanty */

#endif /* GAME_GAME_HPP */
