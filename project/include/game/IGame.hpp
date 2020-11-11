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

#ifndef GAME_IGAME_HPP
#define GAME_IGAME_HPP

#include <core/ltycore_global.hpp>

#include <QObject>
#include <QPixmap>
#include <QString>

#include <game/GameVersionSource.hpp>

namespace lanty
{

class LTYCORE_EXPORT IGame : public QObject
{

    Q_OBJECT

public:
    virtual ~IGame(void){};

    virtual QString getName(void) const = 0;
    virtual QString getArchiveAbsoluteFilePath(void) const = 0;
    virtual QString getClientExecutableRelativeFilePath(void) const = 0;
    virtual QString getClientArgument(void) const = 0;
    virtual QString getClientConnectArgument(void) const = 0;
    virtual QString getServerExecutableRelativeFilePath(void) const = 0;
    virtual QString getServerArgument(void) const = 0;
    virtual QString getVersion(void) const = 0;
    virtual GameVersionSource getVersionSource(void) const = 0;
    virtual QString getVersionRelativeFilePath(void) const = 0;
    virtual QString getVersionFileQuery(void) const = 0;
    virtual QPixmap getCoverImage(void) const = 0;
    virtual QPixmap getIconImage(void) const = 0;

    virtual bool isVersion(void) const = 0;

    virtual bool canJoinServerWithCLI(void) const = 0;
    virtual bool canOpenDedicatedServer(void) const = 0;
    virtual bool canOpenServer(void) const = 0;

public slots:
    virtual void setName(const QString &name) = 0;
    virtual void setArchiveAbsoluteFilePath(const QString &archiveAbsoluteFilePath) = 0;
    virtual void setClientExecutableRelativeFilePath(const QString &clientExecutableRelativeFilePath) = 0;
    virtual void setClientArgument(const QString &clientArgument) = 0;
    virtual void setClientConnectArgument(const QString &clientConnectArgument) = 0;
    virtual void setServerExecutableRelativeFilePath(const QString &serverExecutableRelativeFilePath) = 0;
    virtual void setServerArgument(const QString &serverArgument) = 0;
    virtual void setVersion(const QString &version) = 0;
    virtual void setVersionSource(const GameVersionSource &gameVersionSource) = 0;
    virtual void setVersionRelativeFilePath(const QString &versionRelativeFilePath) = 0;
    virtual void setVersionFileQuery(const QString &versionFileQuery) = 0;
    virtual void setCoverImage(const QPixmap &coverImage) = 0;
    virtual void setIconImage(const QPixmap &iconImage) = 0;

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
    void coverImageChanged(const QPixmap &newCoverImage);
    void iconImageChanged(const QPixmap &newIconImage);

};

} /* namespace lanty */

#endif /* GAME_IGAME_HPP */
