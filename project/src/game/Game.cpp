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

#include "game/Game.hpp"

namespace lanty
{

Game::Game(void) : name(""),
                   archiveAbsoluteFilePath(""),
                   clientExecutableRelativeFilePath(""),
                   clientArgument(""),
                   clientConnectArgument(""),
                   serverExecutableRelativeFilePath(""),
                   serverArgument(""),
                   version(""),
                   versionSource(GameVersionSource::NONE),
                   versionRelativeFilePath(""),
                   versionFileQuery(""),
                   coverImage(QPixmapAdapter()),
                   iconImage(QPixmapAdapter()) { }

Game::Game(const YamlNode &yamlNode) : name(""),
                                        archiveAbsoluteFilePath(""),
                                        clientExecutableRelativeFilePath(""),
                                        clientArgument(""),
                                        clientConnectArgument(""),
                                        serverExecutableRelativeFilePath(""),
                                        serverArgument(""),
                                        version(""),
                                        versionSource(GameVersionSource::NONE),
                                        versionRelativeFilePath(""),
                                        versionFileQuery(""),
                                        coverImage(QPixmapAdapter()),
                                        iconImage(QPixmapAdapter())
{
    this->loadFromYamlNode(yamlNode);
}


bool Game::operator==(const Game &game) const
{
    return this->getName() == game.getName()
           && this->getArchiveAbsoluteFilePath() == game.getArchiveAbsoluteFilePath()
           && this->getClientExecutableRelativeFilePath() == game.getClientExecutableRelativeFilePath()
           && this->getClientArgument() == game.getClientArgument()
           && this->getClientConnectArgument() == game.getClientConnectArgument()
           && this->getServerExecutableRelativeFilePath() == game.getServerExecutableRelativeFilePath()
           && this->getServerArgument() == game.getServerArgument()
           && this->getVersion() == game.getVersion()
           && this->getVersionSource() == game.getVersionSource()
           && this->getVersionRelativeFilePath() == game.getVersionRelativeFilePath()
           && this->getVersionFileQuery() == game.getVersionFileQuery();
}

bool Game::operator!=(const Game &game) const
{
    return !(*this == game);
}


QString Game::getName() const
{
    return this->name;
}

QString Game::getArchiveAbsoluteFilePath() const
{
    return this->archiveAbsoluteFilePath;
}

QString Game::getClientExecutableRelativeFilePath() const
{
    return this->clientExecutableRelativeFilePath;
}

QString Game::getClientArgument() const
{
    return this->clientArgument;
}

QString Game::getClientConnectArgument() const
{
    return this->clientConnectArgument;
}

QString Game::getServerExecutableRelativeFilePath() const
{
    return this->serverExecutableRelativeFilePath;
}

QString Game::getServerArgument() const
{
    return this->serverArgument;
}

QString Game::getVersion() const
{
    return this->version;
}

GameVersionSource Game::getVersionSource() const
{
    return this->versionSource;
}

QString Game::getVersionRelativeFilePath() const
{
    return this->versionRelativeFilePath;
}

QString Game::getVersionFileQuery() const
{
    return this->versionFileQuery;
}

QPixmapAdapter Game::getCoverImage() const
{
    return this->coverImage;
}

QPixmapAdapter Game::getIconImage() const
{
    return this->iconImage;
}

bool Game::isVersion() const
{
    return !version.isEmpty() && versionSource != GameVersionSource::NONE;
}

bool Game::canJoinServerWithCLI() const
{
    return !(this->clientConnectArgument.isEmpty());
}

bool Game::canOpenDedicatedServer() const
{
    return !this->serverExecutableRelativeFilePath.isEmpty();
}

bool Game::canOpenServer() const
{
    return !this->serverExecutableRelativeFilePath.isEmpty() || !this->serverArgument.isEmpty();
}

bool Game::loadFromYamlNode(const YamlNode &yamlNode)
{
    std::shared_ptr<const YamlNode> gameNode = yamlNode.getNode("game");
    this->loadGameDataFromNode(*gameNode);
    return true;
}


void Game::setName(const QString &name)
{
    this->name = name;
    emit nameChanged(this->name);
}

void Game::setArchiveAbsoluteFilePath(const QString &archiveAbsoluteFilePath)
{
    this->archiveAbsoluteFilePath = archiveAbsoluteFilePath;
    emit archivePathChanged(this->archiveAbsoluteFilePath);
}

void Game::setClientExecutableRelativeFilePath(const QString &clientExecutableRelativeFilePath)
{
    this->clientExecutableRelativeFilePath = clientExecutableRelativeFilePath;
    emit clientExecutableChanged(this->clientExecutableRelativeFilePath);
}

void Game::setClientArgument(const QString &clientArgument)
{
    this->clientArgument = clientArgument;
    emit clientArgumentChanged(this->clientArgument);
}

void Game::setClientConnectArgument(const QString &clientConnectArgument)
{
    this->clientConnectArgument = clientConnectArgument;
    emit clientConnectArgumentChanged(this->clientConnectArgument);
}

void Game::setServerExecutableRelativeFilePath(const QString &serverExecutableRelativeFilePath)
{
    this->serverExecutableRelativeFilePath = serverExecutableRelativeFilePath;
    emit serverExecutableChanged(this->serverExecutableRelativeFilePath);
}

void Game::setServerArgument(const QString &serverArgument)
{
    this->serverArgument = serverArgument;
    emit serverArgumentChanged(this->serverArgument);
}

void Game::setVersion(const QString &version)
{
    this->version = version;
    emit versionChanged(this->version);
}

void Game::setVersionSource(const GameVersionSource &gameVersionSource)
{
    this->versionSource = gameVersionSource;
    emit versionSourceChanged(this->versionSource);
}

void Game::setVersionRelativeFilePath(const QString &versionRelativeFilePath)
{
    this->versionRelativeFilePath = versionRelativeFilePath;
    emit versionFileChanged(this->versionRelativeFilePath);
}

void Game::setVersionFileQuery(const QString &versionFileQuery)
{
    this->versionFileQuery = versionFileQuery;
    emit versionFileQueryChanged(this->versionFileQuery);
}

void Game::setCoverImage(const QPixmapAdapter &coverImage)
{
    this->coverImage = coverImage;
    emit coverImageChanged(this->coverImage);
}

void Game::setIconImage(const QPixmapAdapter &iconImage)
{
    this->iconImage = iconImage;
    emit iconImageChanged(this->iconImage);
}


void Game::loadGameDataFromNode(const YamlNode &gameNode)
{
    this->name = gameNode.getQStringFromMap("name");
    this->archiveAbsoluteFilePath = gameNode.getQStringFromMap("archive");

    std::shared_ptr<const YamlNode> versionNode = gameNode.getNode("version");
    this->loadVersionDataFromGameNode(*versionNode);

    std::shared_ptr<const YamlNode> clientNode = gameNode.getNode("client");
    this->loadClientDataFromGameNode(*clientNode);

    std::shared_ptr<const YamlNode> serverNode = gameNode.getNode("server");
    this->loadServerDataFromGameNode(*serverNode);
}

void Game::loadVersionDataFromGameNode(const YamlNode &versionNode)
{
    this->version = versionNode.getQStringFromMap("info");
    QString versionFormat = versionNode.getQStringFromMap("format").toLower();
    if(versionFormat == "file")
    {
        this->versionSource = GameVersionSource::FILE;
    }
    else if(versionFormat == "executable")
    {
        this->versionSource = GameVersionSource::EXECUTABLE;
    }
    else
    {
        this->versionSource = GameVersionSource::NONE;
    }
    this->versionRelativeFilePath = versionNode.getQStringFromMap("file");
    this->versionFileQuery = versionNode.getQStringFromMap("query");
}

void Game::loadClientDataFromGameNode(const YamlNode &clientNode)
{
    this->clientExecutableRelativeFilePath = clientNode.getQStringFromMap("executable");
    this->clientArgument = clientNode.getQStringFromMap("argument");
    this->clientConnectArgument = clientNode.getQStringFromMap("connect");
}

void Game::loadServerDataFromGameNode(const YamlNode &serverNode)
{
    this->serverExecutableRelativeFilePath = serverNode.getQStringFromMap("executable");
    this->serverArgument = serverNode.getQStringFromMap("argument");
}

} /* namespace lanty */
