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

#include <QObject>

#include "core/ltycore_global.hpp"
#include "game/Game.hpp"

namespace lanty
{

class LTYCORE_EXPORT QGame : public QObject, public Game
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(QGame)

public:
    explicit QGame(QObject* parent = nullptr) noexcept;
    QGame(const Game& game, QObject* parent = nullptr) noexcept;
    virtual ~QGame(void) = default;    // GCOVR_EXCL_LINE

    QGame& operator=(const Game& game) noexcept;
    bool operator==(const QGame& game) const noexcept;
    bool operator!=(const QGame& game) const noexcept;

public slots:
    void setName(const QString& name) noexcept override;
    void setArchiveFileName(const QString& archiveFileName) noexcept override;
    void setClientExecutableFilePath(const QString& clientExecutableFilePath) noexcept override;
    void setClientArgument(const QString& clientArgument) noexcept override;
    void setClientConnectArgument(const QString& clientConnectArgument) noexcept override;
    void setServerExecutableFilePath(const QString& serverExecutableFilePath) noexcept override;
    void setServerArgument(const QString& serverArgument) noexcept override;
    void setVersion(const QString& version) noexcept override;
    void setVersionSource(const GameVersion::Source versionSource) noexcept override;
    void setVersionFilePath(const QString& versionFilePath) noexcept override;
    void setVersionFileQuery(const QString& versionFileQuery) noexcept override;
    void setCover(const QPixmap& cover) noexcept override;
    void setIcon(const QPixmap& icon) noexcept override;

signals:
    void nameChanged(const QString& newName);
    void archiveFileNameChanged(const QString& newArchiveFileName);
    void clientExecutableFilePathChanged(const QString& newClientExecutableFilePath);
    void clientArgumentChanged(const QString& newClientArgument);
    void clientConnectArgumentChanged(const QString& newClientConnectArgument);
    void serverExecutableFilePathChanged(const QString& newServerExecutableFilePath);
    void serverArgumentChanged(const QString& newServerArgument);
    void versionChanged(const QString& newVersion);
    void versionSourceChanged(const lanty::GameVersion::Source newVersionSource);
    void versionFilePathChanged(const QString& newVersionFilePath);
    void versionFileQueryChanged(const QString& newVersionFileQuery);
    void coverChanged(const QPixmap& newCover);
    void iconChanged(const QPixmap& newIcon);
    void changed(void);

private:
    void connectSignals(void) noexcept;
};

} /* namespace lanty */
