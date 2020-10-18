#include "Game.hpp"

#include <fstream>
#include <iostream>
#include <QDebug>
#include <QDir>

Game::Game(const QString &yamlfile)
{
    //Load YAML file
    this->base = YAML::LoadFile(yamlfile.toStdString());
    if(this->base.IsNull())
    {
        qDebug() << "Can't load " << yamlfile << ".\n";
    }

    //Check for the 'game' key
    if(false == this->base["game"].IsDefined())
    {
        qDebug() << "Can not find key 'game' in '" << yamlfile << "'.\n";
        return;
    }
    YAML::Node gameNode = base["game"];

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
        this->executableServer = QString("");
        this->argServer = QString("");
        this->openServer = false;
    }

    this->yamlFile = yamlfile;

    this->setImagePath("");

}

Game::Game(const QString &yamlfile, const QString &imagepath) : Game(yamlfile)
{
    this->setImagePath(imagepath);
}

Game::Game(const QDir &yamldir, const QString &name)
{
    version = new Version();
    //yamlfile path
    QString filename = name.simplified().toLower();
    filename.replace(" ", "");
    this->yamlFile = yamldir.absoluteFilePath(filename + ".yaml");
    //Setup name
    this->setName(name);
}

Game::Game(const Game &game) : QObject()
{
    this->base = game.base;
    this->yamlFile = game.yamlFile;
    this->setName(game.getName());
    this->setArchive(game.getArchive());
    this->setExecutable(game.getExecutable());
    this->setArgument(game.getArgument());
    this->setArgumentConnect(game.getArgumentConnect());
    this->setExecutableServer(game.getExecutableServer());
    this->setArgumentServer(game.getArgumentServer());
    this->version = new Version(game.getVersion());
    this->setImagePath(game.getImagePath());
}

Game::~Game(void)
{
    delete this->version;
}

Game& Game::operator=(const Game &game)
{
    this->base = game.base;
    this->yamlFile = game.yamlFile;
    this->setName(game.getName());
    this->setArchive(game.getArchive());
    this->setExecutable(game.getExecutable());
    this->setArgument(game.getArgument());
    this->setArgumentConnect(game.getArgumentConnect());
    this->setExecutableServer(game.getExecutableServer());
    this->setArgumentServer(game.getArgumentServer());
    delete this->version;
    this->version = new Version(game.getVersion());
    this->setImagePath(game.getImagePath());

    return *this;
}

bool Game::operator==(const Game &game) const
{
    return (this->getName() == game.getName())
            && (this->getArchive() == game.getArchive())
            && (this->getExecutable() == game.getExecutable())
            && (this->getArgumentConnect() == game.getArgumentConnect())
            && (this->getExecutableServer() == game.getExecutableServer())
            && (this->getVersionInfo() == game.getVersionInfo())
            && (this->getVersionFormat() == game.getVersionFormat())
            && (this->getVersionFile() == game.getVersionFile())
            && (this->getVersionQuery() == game.getVersionQuery());
}

const QString& Game::getName(void) const
{
    return this->name;
}

const QString& Game::getArchive(void) const
{
    return this->archive;
}

const QString& Game::getExecutable(void) const
{
    return this->executable;
}

const QString& Game::getArgument(void) const
{
    return this->argStart;
}

const QString& Game::getArgumentConnect(void) const
{
    return this->argConnect;
}

const QString& Game::getExecutableServer(void) const
{
    if(this->executableServer.isEmpty())
    {
        return this->getExecutable();
    }
    return this->executableServer;
}

const QString& Game::getArgumentServer(void) const
{
    return this->argServer;
}

const QString& Game::getVersionInfo(void) const
{
    return this->version->getInfo();
}

const Version::VersionFormat& Game::getVersionFormat() const
{
    return this->version->getVersionFormat();
}

const QString& Game::getVersionFile(void) const
{
    return this->version->getFile();
}

const QString& Game::getVersionQuery(void) const
{
    return this->version->getQuery();
}

const Version& Game::getVersion(void) const
{
    return *this->version;
}

const QString& Game::getImagePath(void) const
{
    return this->imagePath;
}

const QPixmap Game::getCover(void) const
{
    if(this->getImagePath().isEmpty())
    {
        return QString("");
    }

    QDir imageDir(getImagePath());
    QStringList filter;
    filter << "*.png" << "*.jpeg" << "*.jpg" << "*.bmp";
    QStringList fileNames = imageDir.entryList(filter, QDir::Files);

    foreach(QString file, fileNames)
    {
        int last = file.lastIndexOf(".");
        int length = file.size();
        QString filename = file;
        filename.remove(last, length - last);
        if(this->getName() == filename)
        {
            return QPixmap(this->getImagePath() + file);
        }
    }
    return QPixmap();
}

const QPixmap Game::getIcon(void) const
{
    if(this->getImagePath().isEmpty())
    {
        return QString("");
    }

    QDir imageDir(getImagePath());
    QStringList filter;
    filter << "*.png" << "*.jpeg" << "*.jpg" << "*.bmp";
    QStringList fileNames = imageDir.entryList(filter, QDir::Files);

    QString coverName(getName() + "_icon");
    foreach(QString file, fileNames)
    {
        int last = file.lastIndexOf(".");
        int length = file.size();
        QString filename = file;
        filename.remove(last, length - last);
        if(coverName == filename)
        {
            return QPixmap(this->getImagePath() + file);
        }
    }
    return QPixmap();
}

bool Game::canConnectDirect(void) const
{
    return this->connectDirect;
}

bool Game::canOpenServer() const
{
    return this->openServer;
}

bool Game::isVersion(void) const
{
    return false == this->getVersionInfo().isEmpty();
}

bool Game::deleteFile(void)
{
    QFile yaml(yamlFile);
    return yaml.remove();
}

bool Game::saveToFile(void)
{
    this->base["game"]["version"] = version->toNode();
    std::ofstream fout(this->yamlFile.toStdString());
    fout << this->base;
    return fout.good();
}

bool Game::setName(const QString &name)
{
    if(name.isEmpty())
    {
        qDebug() << "Error: Name can not be empty.\n";
        return false;
    }
    this->name = name;
    this->base["game"]["name"] = name.toStdString();

    return true;
}

bool Game::setArchive(const QString &archive)
{
    if(archive.isEmpty())
    {
        qDebug() << "Error: Archive can not be empty.\n";
        return false;
    }
    this->archive = archive;
    this->base["game"]["archive"] = archive.toStdString();

    return true;
}

bool Game::setExecutable(const QString &executable)
{
    if(executable.isEmpty())
    {
        qDebug() << "Error: Executable can not be empty.\n";
        return false;
    }
    this->executable = executable;
    this->base["game"]["client"]["executable"] = executable.toStdString();

    return true;
}

void Game::setArgument(const QString &argStart)
{
    this->argStart = argStart;
    this->base["game"]["client"]["argument"] = argStart.toStdString();
}

void Game::setArgumentConnect(const QString &argConnect)
{
    this->argConnect = argConnect;
    this->base["game"]["client"]["connect"] = argConnect.toStdString();
    if(argConnect.isEmpty())
    {
        connectDirect = false;
    }
    else
    {
        connectDirect = true;
    }
}

void Game::setExecutableServer(const QString &serverExecutable)
{
    if(serverExecutable == this->executable)
    {
        this->executableServer = QString("");
        this->base["game"]["server"]["executable"] = "";
    }
    else
    {
        this->executableServer = serverExecutable;
        this->base["game"]["server"]["executable"] = serverExecutable.toStdString();
        if(serverExecutable.isEmpty() && argServer.isEmpty())
        {
            openServer = false;
        }
        else
        {
            openServer = true;
        }
    }
}

void Game::setArgumentServer(const QString &argServer)
{
    this->argServer = argServer;
    this->base["game"]["server"]["argument"] = argServer.toStdString();
    if(executableServer.isEmpty() && argServer.isEmpty())
    {
        openServer = false;
    }
    else
    {
        openServer = true;
    }
}

void Game::setVersionInfo(const QString &versionInfo)
{
    this->version->setInfo(versionInfo);
}

void Game::setVersionFormat(const Version::VersionFormat &format)
{
    this->version->setVersionFormat(format);
}

void Game::setVersionFile(const QString &file)
{
    this->version->setFile(file);
}

void Game::setVersionQuery(const QString &query)
{
    this->version->setQuery(query);
}

void Game::setImagePath(const QString &imagepath)
{
    this->imagePath = imagepath;
    if((false == imagepath.endsWith("/")) && (false == imagepath.isEmpty()))
    {
        this->imagePath += "/";
    }
}

void Game::printInfo(void) const
{
    if(false == this->getName().isEmpty())
    {
        std::cout << "Name: " << this->getName().toStdString() << std::endl;
    }
    if(false == this->getArchive().isEmpty())
    {
        std::cout << "Archive: " << this->getArchive().toStdString() << std::endl;
    }
    if(false == this->getVersionInfo().isEmpty())
    {
        std::cout << "Version: " << this->getVersionInfo().toStdString() << std::endl;
    }
    if(Version::VersionFormat::NONE != this->getVersionFormat())
    {
        std::cout << "Version format: " << this->getVersion().formatToQString().toStdString() << std::endl;
    }
    if(false == this->getVersionFile().isEmpty())
    {
        std::cout << "Version file: " << this->getVersionFile().toStdString() << std::endl;
    }
    if(false == this->getVersionQuery().isEmpty())
    {
        std::cout << "Version query: " << this->getVersionQuery().toStdString() << std::endl;
    }
    if(false == this->getExecutable().isEmpty())
    {
        std::cout << "Executable: " << this->getExecutable().toStdString() << std::endl;
    }
    if(false == this->getArgument().isEmpty())
    {
        std::cout << "Argument: " << this->getArgument().toStdString() << std::endl;
    }
    if(false == this->getArgumentConnect().isEmpty())
    {
        std::cout << "Connect argument: " << this->getArgumentConnect().toStdString() << std::endl;
    }
    if(false == this->getExecutableServer().isEmpty())
    {
        std::cout << "Executable server: " << this->getExecutableServer().toStdString() << std::endl;
    }
    if(false == this->getArgumentServer().isEmpty())
    {
        std::cout << "Argument server: " << this->getArgumentServer().toStdString() << std::endl;
    }
    if(this->canConnectDirect())
    {
        std::cout << "Direct connect: True" << std::endl;
    }
    else
    {
        std::cout << "Direct connect: False" << std::endl;
    }
    if(this->canOpenServer())
    {
        std::cout << "Server: True" << std::endl;
    }
    else
    {
        std::cout << "Server: False" << std::endl;
    }
}
