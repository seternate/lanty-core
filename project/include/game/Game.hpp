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
#include <QPixmap>
#include <QString>

#include "core/ltycore_global.hpp"
#include "game/GameVersionSource.hpp"
#include "system/QPixmapAdapter.hpp"
#include "yaml/YamlNode.hpp"

namespace lanty
{

class LTYCORE_EXPORT Game : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(Game);

public:
    Game(void);
    explicit Game(const YamlNode &yamlNode);
    virtual ~Game(void) = default;

    bool operator==(const Game &game) const;
    bool operator!=(const Game &game) const;

    virtual QString getName(void) const;
    virtual QString getArchiveAbsoluteFilePath(void) const;
    virtual QString getClientExecutableRelativeFilePath(void) const;
    virtual QString getClientArgument(void) const;
    virtual QString getClientConnectArgument(void) const;
    virtual QString getServerExecutableRelativeFilePath(void) const;
    virtual QString getServerArgument(void) const;
    virtual QString getVersion(void) const;
    virtual GameVersionSource getVersionSource(void) const;
    virtual QString getVersionRelativeFilePath(void) const;
    virtual QString getVersionFileQuery(void) const;
    virtual QPixmapAdapter getCoverImage(void) const;
    virtual QPixmapAdapter getIconImage(void) const;
    virtual bool isVersion(void) const;
    virtual bool canJoinServerWithCLI(void) const;
    virtual bool canOpenDedicatedServer(void) const;
    virtual bool canOpenServer(void) const;

    virtual bool loadFromYamlNode(const YamlNode &yamlNode);

public slots:
    virtual void setName(const QString &name);
    virtual void setArchiveAbsoluteFilePath(const QString &archiveAbsoluteFilePath);
    virtual void setClientExecutableRelativeFilePath(const QString &clientExecutableRelativeFilePath);
    virtual void setClientArgument(const QString &clientArgument);
    virtual void setClientConnectArgument(const QString &clientConnectArgument);
    virtual void setServerExecutableRelativeFilePath(const QString &serverExecutableRelativeFilePath);
    virtual void setServerArgument(const QString &serverArgument);
    virtual void setVersion(const QString &version);
    virtual void setVersionSource(const GameVersionSource &gameVersionSource);
    virtual void setVersionRelativeFilePath(const QString &versionRelativeFilePath);
    virtual void setVersionFileQuery(const QString &versionFileQuery);
    virtual void setCoverImage(const QPixmapAdapter &coverImage);
    virtual void setIconImage(const QPixmapAdapter &iconImage);

signals:
    void nameChanged(const QString &newName);
    void archivePathChanged(const QString &newArchivePath);
    void clientExecutableChanged(const QString &newClientExecutable);
    void clientArgumentChanged(const QString& newClientArgument);
    void clientConnectArgumentChanged(const QString& newClientConnectArgument);
    void serverExecutableChanged(const QString &newServerExecutable);
    void serverArgumentChanged(const QString& newServerArgument);
    void versionChanged(const QString &newVersion);
    void versionSourceChanged(GameVersionSource newGameVersionSource);
    void versionFileChanged(const QString &newVersionFile);
    void versionFileQueryChanged(const QString &newVersionFile);
    void coverImageChanged(const lanty::QPixmapAdapter &newCoverImage);
    void iconImageChanged(const lanty::QPixmapAdapter &newIconImage);

private:
    void loadGameDataFromNode(const YamlNode &gameNode);
    void loadVersionDataFromGameNode(const YamlNode &versionNode);
    void loadClientDataFromGameNode(const YamlNode &clientNode);
    void loadServerDataFromGameNode(const YamlNode &serverNode);

    QString name;
    QString archiveAbsoluteFilePath;
    QString clientExecutableRelativeFilePath;
    QString clientArgument;
    QString clientConnectArgument;
    QString serverExecutableRelativeFilePath;
    QString serverArgument;
    QString version;
    GameVersionSource versionSource;
    QString versionRelativeFilePath;
    QString versionFileQuery;
    QPixmapAdapter coverImage;
    QPixmapAdapter iconImage;
};

} /* namespace lanty */

#endif /* GAME_GAME_HPP */
