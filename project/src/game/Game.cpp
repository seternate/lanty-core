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

#include <game/Game.hpp>

#include <QDebug>

namespace lanty
{

bool Game::lintYaml(const IYamlNode &yamlNode)
{
    /*
    if(!yamlNode.isDefined("game"))
    {
        qDebug() << "Missing 'game' node in file:" << yamlNode.getFileName();
        return false;
    }

    std::shared_ptr<IYamlNode> gameNode = yamlNode.getNode("game");

    if(false == gameNode["name"].IsDefined())
    {
        qDebug() << "At 'game': Can not find key 'name' in '" << yamlfile << "'.\n";
        return;
    }
    this->setName(QString::fromStdString(gameNode["name"].as<std::string>()));

    //Check for the 'archive' key
    if(false == gameNode["archive"].IsDefined())
    {
        qDebug() << "At 'game': Can not find key 'archive' in '" << yamlfile << "'.\n";
        return;
    }
    this->setArchive(QString::fromStdString(gameNode["archive"].as<std::string>()));

    //Check for the 'version' key to be present
    if(true == gameNode["version"].IsDefined())
    {
        version = new Version(gameNode["version"], yamlfile);
    }
    else
    {
        version = new Version();
    }

    //Check for the 'client' key to be present
    if(false == gameNode["client"].IsDefined())
    {
        qDebug() << "At 'game': Can't find key 'client' in '" << yamlfile << "'.\n";
        return;
    }
    YAML::Node gameClientNode = gameNode["client"];

    //Check for the executable key to be present
    if(false == gameClientNode["executable"].IsDefined())
    {
        qDebug() << "At 'client': Can not find key 'executable' in '" << yamlfile <<"'.\n";
        return;
    }
    this->setExecutable(QString::fromStdString(gameClientNode["executable"].as<std::string>()));

    //Check for the argument key to be present
    if(true == gameClientNode["argument"].IsDefined())
    {
        this->setArgument(QString::fromStdString(gameClientNode["argument"].as<std::string>()));
    }
    else
    {
        this->setArgument("");
    }

    //Check for the connect key to be present
    if(true == gameClientNode["connect"].IsDefined())
    {
        this->setArgumentConnect(QString::fromStdString(gameClientNode["connect"].as<std::string>()));
    }
    else
    {
        this->setArgumentConnect("");
    }

    //Check for the 'server' key to be present
    if(true == gameNode["server"].IsDefined())
    {
        YAML::Node gameServerNode = gameNode["server"];
        if(true == gameServerNode["executable"].IsDefined())
        {
            this->setExecutableServer(QString::fromStdString(gameServerNode["executable"].as<std::string>()));
        }
        else
        {
            this->setExecutableServer("");
        }
        if(true == gameServerNode["argument"].IsDefined())
        {
            this->setArgumentServer(QString::fromStdString(gameServerNode["argument"].as<std::string>()));
        }
        else
        {
            this->setArgumentServer("");
        }
    }
    else
    {
        this->serverExecutableFilePath = QString("");
        this->serverCommandLineArgument = QString("");
        this->openServer = false;
    }

    this->yamlFilePath = yamlfile;

    this->setImagePath("");
    */
}


void Game::loadGameNode(const IYamlNode &yamlNode)
{
    /*
    if(yamlNode.isDefined("game"))
    {
        qDebug() << "Missing 'game' node in '" << yamlfile << "'.";
        return;
    }
    IYamlNode gameNode = yamlNode.getNode("game");

    //Check for the 'name' key
    if(false == gameNode["name"].IsDefined())
    {
        qDebug() << "At 'game': Can not find key 'name' in '" << yamlfile << "'.\n";
        return;
    }
    this->setName(QString::fromStdString(gameNode["name"].as<std::string>()));

    //Check for the 'archive' key
    if(false == gameNode["archive"].IsDefined())
    {
        qDebug() << "At 'game': Can not find key 'archive' in '" << yamlfile << "'.\n";
        return;
    }
    this->setArchive(QString::fromStdString(gameNode["archive"].as<std::string>()));

    //Check for the 'version' key to be present
    if(true == gameNode["version"].IsDefined())
    {
        version = new Version(gameNode["version"], yamlfile);
    }
    else
    {
        version = new Version();
    }

    //Check for the 'client' key to be present
    if(false == gameNode["client"].IsDefined())
    {
        qDebug() << "At 'game': Can't find key 'client' in '" << yamlfile << "'.\n";
        return;
    }
    YAML::Node gameClientNode = gameNode["client"];

    //Check for the executable key to be present
    if(false == gameClientNode["executable"].IsDefined())
    {
        qDebug() << "At 'client': Can not find key 'executable' in '" << yamlfile <<"'.\n";
        return;
    }
    this->setExecutable(QString::fromStdString(gameClientNode["executable"].as<std::string>()));

    //Check for the argument key to be present
    if(true == gameClientNode["argument"].IsDefined())
    {
        this->setArgument(QString::fromStdString(gameClientNode["argument"].as<std::string>()));
    }
    else
    {
        this->setArgument("");
    }

    //Check for the connect key to be present
    if(true == gameClientNode["connect"].IsDefined())
    {
        this->setArgumentConnect(QString::fromStdString(gameClientNode["connect"].as<std::string>()));
    }
    else
    {
        this->setArgumentConnect("");
    }

    //Check for the 'server' key to be present
    if(true == gameNode["server"].IsDefined())
    {
        YAML::Node gameServerNode = gameNode["server"];
        if(true == gameServerNode["executable"].IsDefined())
        {
            this->setExecutableServer(QString::fromStdString(gameServerNode["executable"].as<std::string>()));
        }
        else
        {
            this->setExecutableServer("");
        }
        if(true == gameServerNode["argument"].IsDefined())
        {
            this->setArgumentServer(QString::fromStdString(gameServerNode["argument"].as<std::string>()));
        }
        else
        {
            this->setArgumentServer("");
        }
    }
    else
    {
        this->serverExecutableFilePath = QString("");
        this->serverCommandLineArgument = QString("");
        this->openServer = false;
    }

    this->yamlFilePath = yamlfile;

    this->setImagePath("");
    */
}

Game::Game(void) : name(""), archiveAbsoluteFilePath(""), clientExecutableRelativeFilePath(""), clientArgument(""),
    clientConnectArgument(""), serverExecutableRelativeFilePath(""), serverArgument(""), version(""),
    versionSource(GameVersionSource::NONE), versionRelativeFilePath(""), versionFileQuery(""), coverImage(QPixmap()),
    iconImage(QPixmap())
{ }

Game::Game(const IYamlNode &yamlNode)
{
    this->loadGameNode(yamlNode);
}

Game& Game::operator=(const Game &game)
{
    this->setName(game.getName());
    this->setArchiveAbsoluteFilePath(game.getArchiveAbsoluteFilePath());
    this->setClientExecutableRelativeFilePath(game.getClientExecutableRelativeFilePath());
    this->setClientArgument(game.getClientArgument());
    this->setClientConnectArgument(game.getClientConnectArgument());
    this->setServerExecutableRelativeFilePath(game.getServerExecutableRelativeFilePath());
    this->setServerArgument(game.getServerArgument());
    this->setVersion(game.getVersion());
    this->setVersionSource(game.getVersionSource());
    this->setVersionRelativeFilePath(game.getVersionRelativeFilePath());
    this->setVersionFileQuery(game.getVersionFileQuery());
    this->setCoverImage(game.getCoverImage());
    this->setIconImage(game.getIconImage());

    return *this;
}

bool Game::operator==(const Game &game) const
{
    return this->getName() == game.getName() &&
           this->getArchiveAbsoluteFilePath() == game.getArchiveAbsoluteFilePath() &&
           this->getClientExecutableRelativeFilePath() == game.getClientExecutableRelativeFilePath() &&
           this->getClientArgument() == game.getClientArgument() &&
           this->getClientConnectArgument() == game.getClientConnectArgument() &&
           this->getServerExecutableRelativeFilePath() == game.getServerExecutableRelativeFilePath() &&
           this->getServerArgument() == game.getServerArgument() &&
           this->getVersion() == game.getVersion() &&
           this->getVersionSource() == game.getVersionSource() &&
           this->getVersionRelativeFilePath() == game.getVersionRelativeFilePath() &&
           this->getVersionFileQuery() == game.getVersionFileQuery();
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

QPixmap Game::getCoverImage() const
{
    return this->coverImage;
}

QPixmap Game::getIconImage() const
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

void Game::setCoverImage(const QPixmap &coverImage)
{
    this->coverImage = coverImage;
    emit coverImageChanged(this->coverImage);
}

void Game::setIconImage(const QPixmap &iconImage)
{
    this->iconImage = iconImage;
    emit iconImageChanged(this->iconImage);
}

} /* namespace lanty */
