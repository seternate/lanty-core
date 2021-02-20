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

#include <QDebug>
#include <QFile>

namespace lanty
{

Game::Game(QObject* parent) :
    QObject(parent),
    yamlFilePath(""),
    name(""),
    archiveFileName(""),
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
    QObject::connect(this, SIGNAL(nameChanged(const QString&)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(archiveFileNameChanged(const QString&)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(clientExecutableChanged(const QString&)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(clientArgumentChanged(const QString&)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(clientConnectArgumentChanged(const QString&)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(serverExecutableChanged(const QString&)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(serverArgumentChanged(const QString&)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(versionChanged(const QString&)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(versionSourceChanged(GameVersionSource)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(versionFileChanged(const QString&)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(versionFileQueryChanged(const QString&)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(coverImageChanged(const lanty::QPixmapAdapter&)), this, SIGNAL(changed(void)));
    QObject::connect(this, SIGNAL(iconImageChanged(const lanty::QPixmapAdapter&)), this, SIGNAL(changed(void)));
}

Game::Game(const YamlNode& yamlNode) :
    QObject(nullptr),
    yamlFilePath(""),
    name(""),
    archiveFileName(""),
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


bool Game::operator==(const Game& game) const
{
    return this->getName() == game.getName() && this->getArchiveFileName() == game.getArchiveFileName()
           && this->getClientExecutableRelativeFilePath() == game.getClientExecutableRelativeFilePath()
           && this->getClientArgument() == game.getClientArgument()
           && this->getClientConnectArgument() == game.getClientConnectArgument()
           && this->getServerExecutableRelativeFilePath() == game.getServerExecutableRelativeFilePath()
           && this->getServerArgument() == game.getServerArgument() && this->getVersion() == game.getVersion()
           && this->getVersionSource() == game.getVersionSource()
           && this->getVersionRelativeFilePath() == game.getVersionRelativeFilePath()
           && this->getVersionFileQuery() == game.getVersionFileQuery();
}

bool Game::operator!=(const Game& game) const
{
    return !(*this == game);
}


QString Game::getName(void) const
{
    return this->name;
}

QString Game::getArchiveFileName(void) const
{
    return this->archiveFileName;
}

QString Game::getClientExecutableRelativeFilePath(void) const
{
    return this->clientExecutableRelativeFilePath;
}

QString Game::getClientArgument(void) const
{
    return this->clientArgument;
}

QString Game::getClientConnectArgument(void) const
{
    return this->clientConnectArgument;
}

QString Game::getServerExecutableRelativeFilePath(void) const
{
    QString result;

    if (this->serverExecutableRelativeFilePath == QString(""))
    {
        result = this->clientExecutableRelativeFilePath;
    }
    else
    {
        result = this->serverExecutableRelativeFilePath;
    }

    return result;
}

QString Game::getServerArgument(void) const
{
    return this->serverArgument;
}

QString Game::getVersion(void) const
{
    return this->version;
}

GameVersionSource Game::getVersionSource(void) const
{
    return this->versionSource;
}

QString Game::getVersionRelativeFilePath(void) const
{
    return this->versionRelativeFilePath;
}

QString Game::getVersionFileQuery(void) const
{
    return this->versionFileQuery;
}

QPixmapAdapter Game::getCoverImage(void) const
{
    return this->coverImage;
}

QPixmapAdapter Game::getIconImage(void) const
{
    return this->iconImage;
}

bool Game::isVersion(void) const
{
    bool result = !version.isEmpty() && versionSource != GameVersionSource::NONE;

    qDebug() << this->getName() << " is version: " << result;

    return result;
}

bool Game::canJoinServerWithCLI(void) const
{
    bool result = !this->clientConnectArgument.isEmpty();

    qDebug() << this->getName() << " can join server with CLI: " << result;

    return result;
}

bool Game::canOpenDedicatedServer(void) const
{
    bool result = !this->serverExecutableRelativeFilePath.isEmpty();

    qDebug() << this->getName() << " can open dedicated server: " << result;

    return result;
}

bool Game::canOpenServer(void) const
{
    bool result = !this->serverExecutableRelativeFilePath.isEmpty() || !this->serverArgument.isEmpty();

    qDebug() << this->getName() << " can open server: " << result;

    return result;
}


bool Game::load(const YamlNode& yamlNode)
{
    loadFromYamlNode(yamlNode);
    return true;
}


void Game::setName(const QString& name)
{
    qDebug() << this->getName() << " changed name: " << name;
    this->name = name;
    emit nameChanged(this->name);
}

void Game::setArchiveFileName(const QString& archiveFileName)
{
    qDebug() << this->name << " changed archive filename: " << archiveFileName;
    this->archiveFileName = archiveFileName;
    emit archiveFileNameChanged(this->archiveFileName);
}

void Game::setClientExecutableRelativeFilePath(const QString& clientExecutableRelativeFilePath)
{
    qDebug() << this->name << " changed client executable filepath: " << clientExecutableRelativeFilePath;
    this->clientExecutableRelativeFilePath = clientExecutableRelativeFilePath;
    emit clientExecutableChanged(this->clientExecutableRelativeFilePath);
}

void Game::setClientArgument(const QString& clientArgument)
{
    qDebug() << this->name << " changed client argument: " << clientArgument;
    this->clientArgument = clientArgument;
    emit clientArgumentChanged(this->clientArgument);
}

void Game::setClientConnectArgument(const QString& clientConnectArgument)
{
    qDebug() << this->name << " changed client connect argument: " << clientConnectArgument;
    this->clientConnectArgument = clientConnectArgument;
    emit clientConnectArgumentChanged(this->clientConnectArgument);
}

void Game::setServerExecutableRelativeFilePath(const QString& serverExecutableRelativeFilePath)
{
    qDebug() << this->name << " changed server executable filepath: " << serverExecutableRelativeFilePath;
    this->serverExecutableRelativeFilePath = serverExecutableRelativeFilePath;
    emit serverExecutableChanged(this->serverExecutableRelativeFilePath);
}

void Game::setServerArgument(const QString& serverArgument)
{
    qDebug() << this->name << " changed server argument: " << serverArgument;
    this->serverArgument = serverArgument;
    emit serverArgumentChanged(this->serverArgument);
}

void Game::setVersion(const QString& version)
{
    qDebug() << this->name << " changed version: " << version;
    this->version = version;
    emit versionChanged(this->version);
}

void Game::setVersionSource(const GameVersionSource& gameVersionSource)
{
    this->versionSource = gameVersionSource;
    emit versionSourceChanged(this->versionSource);
}

void Game::setVersionRelativeFilePath(const QString& versionRelativeFilePath)
{
    qDebug() << this->name << " changed version filepath: " << versionRelativeFilePath;
    this->versionRelativeFilePath = versionRelativeFilePath;
    emit versionFileChanged(this->versionRelativeFilePath);
}

void Game::setVersionFileQuery(const QString& versionFileQuery)
{
    qDebug() << this->name << " changed version file query: " << versionFileQuery;
    this->versionFileQuery = versionFileQuery;
    emit versionFileQueryChanged(this->versionFileQuery);
}

void Game::setCoverImage(const QPixmapAdapter& coverImage)
{
    qDebug() << this->name << " changed coverimage";
    this->coverImage = coverImage;
    emit coverImageChanged(this->coverImage);
}

void Game::setIconImage(const QPixmapAdapter& iconImage)
{
    qDebug() << this->name << " changed iconimage";
    this->iconImage = iconImage;
    emit iconImageChanged(this->iconImage);
}


bool Game::deleteYamlFile(void)
{
    QFile yamlFile(this->yamlFilePath);

    return yamlFile.remove();
}

bool Game::save(void)
{
    return this->save(this->yamlFilePath);
}

bool Game::save(const QString& yamlFilePath)
{
    YamlNode rootNode(yamlFilePath, false);
    this->yamlFilePath = yamlFilePath;

    this->saveToYamlNode(rootNode);

    return rootNode.saveToFile();
}


void Game::loadFromYamlNode(const YamlNode& yamlNode)
{
    const YamlNode* gameNode = yamlNode.getNode("game");

    this->loadGameDataFromGameNode(*gameNode);
    this->yamlFilePath = yamlNode.getFilePath();
    qDebug() << "Loaded game from YAML-file: " << yamlNode.getFileName();
}

void Game::loadGameDataFromGameNode(const YamlNode& gameNode)
{
    this->name = gameNode.getQStringFromMap("name");
    qDebug() << "Loaded gamename: " << this->getName();
    this->archiveFileName = gameNode.getQStringFromMap("archive");
    qDebug() << "Loaded archive filename: " << this->getArchiveFileName();

    const YamlNode* versionNode = gameNode.getNode("version");
    if (versionNode != nullptr)
    {
        this->loadVersionDataFromGameNode(*versionNode);
        qDebug() << "Loaded game version info";
    }
    else
    {
        qDebug() << "No game version info available";
    }

    const YamlNode* clientNode = gameNode.getNode("client");
    this->loadClientDataFromGameNode(*clientNode);
    qDebug() << "Loaded game client info";

    const YamlNode* serverNode = gameNode.getNode("server");
    if (serverNode != nullptr)
    {
        this->loadServerDataFromGameNode(*serverNode);
        qDebug() << "Loaded game server info";
    }
    else
    {
        qDebug() << "No game server info available";
    }
}

void Game::loadVersionDataFromGameNode(const YamlNode& versionNode)
{
    this->version = versionNode.getQStringFromMap("info");
    qDebug() << "Loaded game version info: " << this->getVersion();
    QString versionFormat = versionNode.getQStringFromMap("format").toLower();
    if (versionFormat == "file")
    {
        this->versionSource = GameVersionSource::FILE;
    }
    else if (versionFormat == "executable")
    {
        this->versionSource = GameVersionSource::EXECUTABLE;
    }
    else
    {
        this->versionSource = GameVersionSource::NONE;
    }
    this->versionRelativeFilePath = versionNode.getQStringFromMap("file");
    qDebug() << "Loaded game version file: " << this->getVersionRelativeFilePath();
    this->versionFileQuery = versionNode.getQStringFromMap("query");
    qDebug() << "Loaded game version query: '" << this->getVersionFileQuery();
}

void Game::loadClientDataFromGameNode(const YamlNode& clientNode)
{
    this->clientExecutableRelativeFilePath = clientNode.getQStringFromMap("executable");
    qDebug() << "Loaded game client executable: " << this->getClientExecutableRelativeFilePath();
    this->clientArgument = clientNode.getQStringFromMap("argument");
    qDebug() << "Loaded game client argument: " << this->getClientArgument();
    this->clientConnectArgument = clientNode.getQStringFromMap("connect");
    qDebug() << "Loaded game client connect: " << this->getClientConnectArgument();
}

void Game::loadServerDataFromGameNode(const YamlNode& serverNode)
{
    this->serverExecutableRelativeFilePath = serverNode.getQStringFromMap("executable");
    qDebug() << "Loaded game server executable: " << this->getServerExecutableRelativeFilePath();
    this->serverArgument = serverNode.getQStringFromMap("argument");
    qDebug() << "Loaded game server argument: " << this->getServerArgument();
}


void Game::saveToYamlNode(YamlNode& yamlNode)
{
    YamlNode* gamenode = yamlNode.setNode("game");
    this->saveGameDataToGameNode(*gamenode);
}

void Game::saveGameDataToGameNode(YamlNode& gameNode)
{
    gameNode.setString("name", this->name);
    gameNode.setString("archive", this->archiveFileName);

    YamlNode* versionNode = gameNode.setNode("version");
    this->saveVersionDataToGameNode(*versionNode);

    YamlNode* clientNode = gameNode.setNode("client");
    this->saveClientDataToGameNode(*clientNode);

    YamlNode* serverNode = gameNode.setNode("server");
    this->saveServerDataToGameNode(*serverNode);
}

void Game::saveVersionDataToGameNode(YamlNode& versionNode)
{
    if (this->version.isEmpty() == false)
    {
        versionNode.setString("info", this->version);
    }

    if (this->versionSource == GameVersionSource::EXECUTABLE)
    {
        versionNode.setString("format", "executable");
    }
    else if (this->versionSource == GameVersionSource::FILE)
    {
        versionNode.setString("format", "file");
    }
    else
    {
        versionNode.setString("format", "none");
    }

    if (this->versionRelativeFilePath.isEmpty() == false)
    {
        versionNode.setString("file", this->versionRelativeFilePath);
    }

    if (this->versionFileQuery.isEmpty() == false)
    {
        versionNode.setString("query", this->versionFileQuery);
    }
}

void Game::saveClientDataToGameNode(YamlNode& clientNode)
{
    clientNode.setString("executable", this->clientExecutableRelativeFilePath);

    if (this->clientArgument.isEmpty() == false)
    {
        clientNode.setString("argument", this->clientArgument);
    }

    if (this->clientConnectArgument.isEmpty() == false)
    {
        clientNode.setString("connect", this->clientConnectArgument);
    }
}

void Game::saveServerDataToGameNode(YamlNode& serverNode)
{
    if (this->serverExecutableRelativeFilePath.isEmpty() == false)
    {
        serverNode.setString("executable", this->serverExecutableRelativeFilePath);
    }

    if (this->serverArgument.isEmpty() == false)
    {
        serverNode.setString("argument", this->serverArgument);
    }
}

} /* namespace lanty */
