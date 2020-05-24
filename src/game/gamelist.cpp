#include "gamelist.h"

#include <QDir>
#include <QDebug>
#include <iostream>

Gamelist::Gamelist(const QString &yamlPath, const QString &imagePath)
{
    QDir qYamlDir(yamlPath);
    QDir qImageDir(imagePath);

    QStringList yamlFileNames = qYamlDir.entryList(QStringList() << "*.yaml", QDir::Files);
    yamlFileNames.removeOne("template.yaml");

    latestgamelist = new QList<Game>;
    foreach(QString yamlFileName, yamlFileNames)
    {
        latestgamelist->push_back(Game(qYamlDir.absoluteFilePath(yamlFileName), qImageDir.absolutePath()));
    }
    gamelist = new QList<Game>(*latestgamelist);
}

Gamelist::Gamelist(const Gamelist &gamelist) : QAbstractListModel()
{
    this->latestgamelist = new QList<Game>(*gamelist.latestgamelist);
}

Gamelist::~Gamelist(void){
    delete latestgamelist;
}

Game& Gamelist::operator[](int i)
{
    return (*latestgamelist)[i];
}

bool Gamelist::remove(Game &game)
{
    return game.deleteFile() && latestgamelist->removeOne(game);
}

void Gamelist::add(const Game &game)
{
    latestgamelist->append(game);
}

const Game& Gamelist::at(int i) const
{
    return latestgamelist->at(i);
}

int Gamelist::size(void) const
{
    return latestgamelist->size();
}

bool Gamelist::contains(const QString &name) const
{
    foreach(const Game game, *this->latestgamelist)
    {
        if(game.getName() == name)
        {
            return true;
        }
    }
    return false;
}

QVariant Gamelist::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }
    if (index.row() >= latestgamelist->size())
    {
        return QVariant();
    }
    if (role == Qt::DisplayRole)
    {
        return latestgamelist->at(index.row()).getName();
    }
    else
    {
        return QVariant();
    }
}

int Gamelist::rowCount(const QModelIndex &parent) const
{
    return latestgamelist->size();
}

void Gamelist::printAllInfo(void) const
{
    for(int i = 0; i < latestgamelist->size(); i++)
    {
        latestgamelist->at(i).printInfo();
        std::cout << std::endl;
    }
}

void Gamelist::saveGame(int index)
{
    (*latestgamelist)[index].saveToFile();
}

void Gamelist::updateGameName(int index, const QString &name)
{
    (*latestgamelist)[index].setName(name);
}

void Gamelist::updateGameArchive(int index, const QString &archive)
{
    (*latestgamelist)[index].setArchive(archive);
}

void Gamelist::updateGameExecutable(int index, const QString &executable)
{
    (*latestgamelist)[index].setExecutable(executable);
}

void Gamelist::updateGameArgument(int index, const QString &argument)
{
    (*latestgamelist)[index].setArgument(argument);
}

void Gamelist::updateGameArgumentConnect(int index, const QString &argument)
{
    (*latestgamelist)[index].setArgumentConnect(argument);
}

void Gamelist::updateGameExecutableServer(int index, const QString &executable)
{
    (*latestgamelist)[index].setExecutableServer(executable);
}

void Gamelist::updateGameArgumentServer(int index, const QString &argument)
{
    (*latestgamelist)[index].setArgumentServer(argument);
}

void Gamelist::updateGameVersionInfo(int index, const QString &info)
{
    (*latestgamelist)[index].setVersionInfo(info);
}

void Gamelist::updateGameVersionFormat(int index, const Version::VersionFormat &format)
{
    (*latestgamelist)[index].setVersionFormat(format);
}

void Gamelist::updateGameVersionFile(int index, const QString &file)
{
    (*latestgamelist)[index].setVersionFile(file);
}

void Gamelist::updateGameVersionQuery(int index, const QString &query)
{
    (*latestgamelist)[index].setVersionQuery(query);
}
