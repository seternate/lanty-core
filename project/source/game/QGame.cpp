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

#include "game/QGame.hpp"

namespace lanty
{

QGame::QGame(QObject* parent) noexcept : QObject(parent), Game()
{
    this->connectSignals();
}

QGame::QGame(const Game& game, QObject* parent) noexcept : QObject(parent), Game(game)
{
    this->connectSignals();
}


QGame& QGame::operator=(const Game& game) noexcept
{
    Game::operator=(game);
    return *this;
}

bool QGame::operator==(const QGame& game) const noexcept
{
    return static_cast<Game>(*this) == static_cast<Game>(game);
}

bool QGame::operator!=(const QGame& game) const noexcept
{
    return !(*this == game);
}


void QGame::setID(qint64 id) noexcept
{
    Game::setID(id);
    emit this->idChanged(id);
}

void QGame::setName(const QString& name) noexcept
{
    Game::setName(name);
    emit this->nameChanged(name);
}

void QGame::setArchiveFileName(const QString& archiveFileName) noexcept
{
    Game::setArchiveFileName(archiveFileName);
    emit this->archiveFileNameChanged(archiveFileName);
}

void QGame::setClientExecutableFilePath(const QString& clientExecutableFilePath) noexcept
{
    Game::setClientExecutableFilePath(clientExecutableFilePath);
    emit this->clientExecutableFilePathChanged(clientExecutableFilePath);
}

void QGame::setClientArgument(const QString& clientArgument) noexcept
{
    Game::setClientArgument(clientArgument);
    emit this->clientArgumentChanged(clientArgument);
}

void QGame::setClientConnectArgument(const QString& clientConnectArgument) noexcept
{
    Game::setClientConnectArgument(clientConnectArgument);
    emit this->clientConnectArgumentChanged(clientConnectArgument);
}

void QGame::setServerExecutableFilePath(const QString& serverExecutableFilePath) noexcept
{
    Game::setServerExecutableFilePath(serverExecutableFilePath);
    emit this->serverExecutableFilePathChanged(serverExecutableFilePath);
}

void QGame::setServerArgument(const QString& serverArgument) noexcept
{
    Game::setServerArgument(serverArgument);
    emit this->serverArgumentChanged(serverArgument);
}

void QGame::setVersion(const QString& version) noexcept
{
    Game::setVersion(version);
    emit this->versionChanged(version);
}

void QGame::setVersionSource(const GameVersion::Source versionSource) noexcept
{
    Game::setVersionSource(versionSource);
    emit this->versionSourceChanged(versionSource);
}

void QGame::setVersionFilePath(const QString& versionFilePath) noexcept
{
    Game::setVersionFilePath(versionFilePath);
    emit this->versionFilePathChanged(versionFilePath);
}

void QGame::setVersionFileQuery(const QString& versionFileQuery) noexcept
{
    Game::setVersionFileQuery(versionFileQuery);
    emit this->versionFileQueryChanged(versionFileQuery);
}

void QGame::setCover(const QPixmap& cover) noexcept
{
    Game::setCover(cover);
    emit this->coverChanged(cover);
}

void QGame::setIcon(const QPixmap& icon) noexcept
{
    Game::setIcon(icon);
    emit this->iconChanged(icon);
}


void QGame::connectSignals(void) noexcept
{
    QObject::connect(this, SIGNAL(idChanged(quint64)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(nameChanged(const QString&)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(archiveFileNameChanged(const QString&)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(clientExecutableFilePathChanged(const QString&)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(clientArgumentChanged(const QString&)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(clientConnectArgumentChanged(const QString&)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(serverExecutableFilePathChanged(const QString&)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(serverArgumentChanged(const QString&)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(versionChanged(const QString&)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(versionSourceChanged(const lanty::GameVersion::Source)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(versionFilePathChanged(const QString&)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(versionFileQueryChanged(const QString&)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(coverChanged(const QPixmap&)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(iconChanged(const QPixmap&)), this, SIGNAL(changed(void)));
}

} /* namespace lanty */
