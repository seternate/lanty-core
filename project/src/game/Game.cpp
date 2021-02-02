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

#include <QFile>

#include "logging/Logger.hpp"
#include "logging/LogLevel.hpp"

namespace lanty
{

Game::Game(QObject *parent) : QObject(parent),
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

Game::Game(const YamlNode &yamlNode) : QObject(nullptr),
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


bool Game::operator==(const Game &game) const
{
    return this->getName() == game.getName()
           && this->getArchiveFileName() == game.getArchiveFileName()
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

    if(this->serverExecutableRelativeFilePath == QString(""))
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
    Logger(LogLevel::TRACE) << "isVersion: "
                            << this->getName()
                            << ": version ("
                            << QString(version.isEmpty())
                            << ") = "
                            << this->getVersion();
    return !version.isEmpty() && versionSource != GameVersionSource::NONE;
}

bool Game::canJoinServerWithCLI(void) const
{
    Logger(LogLevel::TRACE) << "canJoinServerWithCLI: "
                            << this->getName()
                            << ": Connect Argument = "
                            << this->getClientConnectArgument();
    return !(this->clientConnectArgument.isEmpty());
}

bool Game::canOpenDedicatedServer(void) const
{
    Logger(LogLevel::TRACE) << "canOpenDedicatedServer: "
                            << this->getName()
                            << ": Serverexecutable = "
                            << this->getServerExecutableRelativeFilePath();
    return !this->serverExecutableRelativeFilePath.isEmpty();
}

bool Game::canOpenServer(void) const
{
    Logger(LogLevel::TRACE) << "canOpenServer: "
                            << this->getName()
                            << ": Serverexecutable = "
                            << this->getServerExecutableRelativeFilePath()
                            << ": Server Argument = "
                            << this->getServerArgument();
    return !this->serverExecutableRelativeFilePath.isEmpty() || !this->serverArgument.isEmpty();
}


bool Game::load(const YamlNode &yamlNode)
{
    loadFromYamlNode(yamlNode);
    return true;
}


void Game::setName(const QString &name)
{
    Logger(LogLevel::TRACE) << this->name << " changed to " << name;
    this->name = name;
    emit nameChanged(this->name);
}

void Game::setArchiveFileName(const QString &archiveFileName)
{
    Logger(LogLevel::TRACE) << this->name
                            << " changed path from '"
                            << this->archiveFileName
                            << "' to '" << archiveFileName
                            << "'.";
    this->archiveFileName = archiveFileName;
    emit archiveFileNameChanged(this->archiveFileName);
}

void Game::setClientExecutableRelativeFilePath(const QString &clientExecutableRelativeFilePath)
{
    Logger(LogLevel::TRACE) << this->name
                            << " changed clientexecutable from '"
                            << this->clientExecutableRelativeFilePath
                            << "' to '" << clientExecutableRelativeFilePath
                            << "'.";
    this->clientExecutableRelativeFilePath = clientExecutableRelativeFilePath;
    emit clientExecutableChanged(this->clientExecutableRelativeFilePath);
}

void Game::setClientArgument(const QString &clientArgument)
{
    Logger(LogLevel::TRACE) << this->name
                            << " changed client argument from '"
                            << this->clientArgument
                            << "' to '" << clientArgument
                            << "'.";
    this->clientArgument = clientArgument;
    emit clientArgumentChanged(this->clientArgument);
}

void Game::setClientConnectArgument(const QString &clientConnectArgument)
{
    Logger(LogLevel::TRACE) << this->name
                            << " changed client connect argument from '"
                            << this->clientConnectArgument
                            << "' to '" << clientConnectArgument
                            << "'.";
    this->clientConnectArgument = clientConnectArgument;
    emit clientConnectArgumentChanged(this->clientConnectArgument);
}

void Game::setServerExecutableRelativeFilePath(const QString &serverExecutableRelativeFilePath)
{
    Logger(LogLevel::TRACE) << this->name
                            << " changed serverexecutable from '"
                            << this->serverExecutableRelativeFilePath
                            << "' to '" << serverExecutableRelativeFilePath
                            << "'.";
    this->serverExecutableRelativeFilePath = serverExecutableRelativeFilePath;
    emit serverExecutableChanged(this->serverExecutableRelativeFilePath);
}

void Game::setServerArgument(const QString &serverArgument)
{
    Logger(LogLevel::TRACE) << this->name
                            << " changed server argument from '"
                            << this->serverArgument
                            << "' to '" << serverArgument
                            << "'.";
    this->serverArgument = serverArgument;
    emit serverArgumentChanged(this->serverArgument);
}

void Game::setVersion(const QString &version)
{
    Logger(LogLevel::TRACE) << this->name
                            << " changed version from '"
                            << this->version
                            << "' to '" << version
                            << "'.";
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
    Logger(LogLevel::TRACE) << this->name
                            << " changed version file from '"
                            << this->versionRelativeFilePath
                            << "' to '" << versionRelativeFilePath
                            << "'.";
    this->versionRelativeFilePath = versionRelativeFilePath;
    emit versionFileChanged(this->versionRelativeFilePath);
}

void Game::setVersionFileQuery(const QString &versionFileQuery)
{
    Logger(LogLevel::TRACE) << this->name
                            << " changed versionfile query from '"
                            << this->versionFileQuery
                            << "' to '" << versionFileQuery
                            << "'.";
    this->versionFileQuery = versionFileQuery;
    emit versionFileQueryChanged(this->versionFileQuery);
}

void Game::setCoverImage(const QPixmapAdapter &coverImage)
{
    Logger(LogLevel::TRACE) << this->name
                            << " changed coverimage.";
    this->coverImage = coverImage;
    emit coverImageChanged(this->coverImage);
}

void Game::setIconImage(const QPixmapAdapter &iconImage)
{
    Logger(LogLevel::TRACE) << this->name
                            << " changed iconimage.";
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

bool Game::save(const QString &yamlFilePath)
{
    YamlNode rootNode(yamlFilePath, false);
    this->yamlFilePath = yamlFilePath;

    this->saveToYamlNode(rootNode);

    return rootNode.saveToFile();
}


void Game::loadFromYamlNode(const YamlNode &yamlNode)
{
    const YamlNode* gameNode = yamlNode.getNode("game");

    this->loadGameDataFromGameNode(*gameNode);
    this->yamlFilePath = yamlNode.getFilePath();
    Logger() << "Loaded game from YAML-file '" << yamlNode.getFileName() << "'.";
}

void Game::loadGameDataFromGameNode(const YamlNode &gameNode)
{
    this->name = gameNode.getQStringFromMap("name");
    Logger() << "Loaded gamename '" << this->name << "' from YAML-file '" << gameNode.getFileName() << "'.";
    this->archiveFileName = gameNode.getQStringFromMap("archive");
    Logger() << "Loaded gamearchive '" << this->archiveFileName << "' from YAML-file '" << gameNode.getFileName() << "'.";

    const YamlNode* versionNode = gameNode.getNode("version");
    if(versionNode != nullptr)
    {
        this->loadVersionDataFromGameNode(*versionNode);
        Logger() << "Loaded gameversion info from YAML-file '" << gameNode.getFileName() << "'.";
    }
    else
    {
        Logger() << "No gameversion info available from YAML-file '" << gameNode.getFileName() << "'.";
    }

    const YamlNode* clientNode = gameNode.getNode("client");
    this->loadClientDataFromGameNode(*clientNode);
    Logger() << "Loaded gameclient info from YAML-file '" << gameNode.getFileName() << "'.";

    const YamlNode* serverNode = gameNode.getNode("server");
    if(serverNode != nullptr)
    {
        this->loadServerDataFromGameNode(*serverNode);
        Logger() << "Loaded gameserver info from YAML-file '" << gameNode.getFileName() << "'.";
    }
    else
    {
        Logger() << "No gameserver info available from YAML-file '" << gameNode.getFileName() << "'.";
    }
}

void Game::loadVersionDataFromGameNode(const YamlNode &versionNode)
{
    this->version = versionNode.getQStringFromMap("info");
    Logger() << "Loaded gameversion-info '" << this->version << "' from YAML-file '" << versionNode.getFileName() << "'.";
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
    Logger() << "Loaded gameversion-file '"
             << this->versionRelativeFilePath
             << "' from YAML-file '"
             << versionNode.getFileName()
             << "'.";
    this->versionFileQuery = versionNode.getQStringFromMap("query");
    Logger() << "Loaded gameversion-query '"
             << this->versionFileQuery
             << "' from YAML-file '"
             << versionNode.getFileName()
             << "'.";
}

void Game::loadClientDataFromGameNode(const YamlNode &clientNode)
{
    this->clientExecutableRelativeFilePath = clientNode.getQStringFromMap("executable");
    Logger() << "Loaded gameclient-executable '"
             << this->clientExecutableRelativeFilePath
             << "' from YAML-file '"
             << clientNode.getFileName()
             << "'.";
    this->clientArgument = clientNode.getQStringFromMap("argument");
    Logger() << "Loaded gameclient-argument '"
             << this->clientArgument
             << "' from YAML-file '"
             << clientNode.getFileName()
             << "'.";
    this->clientConnectArgument = clientNode.getQStringFromMap("connect");
    Logger() << "Loaded gameclient-connect '"
             << this->clientConnectArgument
             << "' from YAML-file '"
             << clientNode.getFileName()
             << "'.";
}

void Game::loadServerDataFromGameNode(const YamlNode &serverNode)
{
    this->serverExecutableRelativeFilePath = serverNode.getQStringFromMap("executable");
    Logger() << "Loaded gameclient-executable '"
             << this->serverExecutableRelativeFilePath
             << "' from YAML-file '"
             << serverNode.getFileName()
             << "'.";
    this->serverArgument = serverNode.getQStringFromMap("argument");
    Logger() << "Loaded gameclient-argument '"
             << this->serverArgument
             << "' from YAML-file '"
             << serverNode.getFileName()
             << "'.";
}


void Game::saveToYamlNode(YamlNode &yamlNode)
{
    YamlNode* gamenode = yamlNode.setNode("game");
    this->saveGameDataToGameNode(*gamenode);
}

void Game::saveGameDataToGameNode(YamlNode &gameNode)
{
    gameNode.setString("name", this->name);
    gameNode.setString("archive", this->archiveFileName);

    YamlNode *versionNode = gameNode.setNode("version");
    this->saveVersionDataToGameNode(*versionNode);

    YamlNode *clientNode = gameNode.setNode("client");
    this->saveClientDataToGameNode(*clientNode);

    YamlNode *serverNode = gameNode.setNode("server");
    this->saveServerDataToGameNode(*serverNode);
}

void Game::saveVersionDataToGameNode(YamlNode &versionNode)
{
    if(this->version.isEmpty() == false)
    {
        versionNode.setString("info", this->version);
    }

    if(this->versionSource == GameVersionSource::EXECUTABLE)
    {
        versionNode.setString("format", "executable");
    }
    else if(this->versionSource == GameVersionSource::FILE)
    {
        versionNode.setString("format", "file");
    }
    else
    {
        versionNode.setString("format", "none");
    }

    if(this->versionRelativeFilePath.isEmpty() == false)
    {
        versionNode.setString("file", this->versionRelativeFilePath);
    }

    if(this->versionFileQuery.isEmpty() == false)
    {
        versionNode.setString("query", this->versionFileQuery);
    }
}

void Game::saveClientDataToGameNode(YamlNode &clientNode)
{
    clientNode.setString("executable", this->clientExecutableRelativeFilePath);

    if(this->clientArgument.isEmpty() == false)
    {
        clientNode.setString("argument", this->clientArgument);
    }

    if(this->clientConnectArgument.isEmpty() == false)
    {
        clientNode.setString("connect", this->clientConnectArgument);
    }
}

void Game::saveServerDataToGameNode(YamlNode &serverNode)
{
    if(this->serverExecutableRelativeFilePath.isEmpty() == false)
    {
        serverNode.setString("executable", this->serverExecutableRelativeFilePath);
    }

    if(this->serverArgument.isEmpty() == false)
    {
        serverNode.setString("argument", this->serverArgument);
    }
}

} /* namespace lanty */
