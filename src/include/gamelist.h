#ifndef GAMELIST_H
#define GAMELIST_H

#include <QList>
#include <QAbstractListModel>

#include "ltycore_global.h"
#include "game.h"

class LTYCORE_EXPORT Gamelist : public QAbstractListModel
{

    Q_OBJECT

public:
    Gamelist(const QString &, const QString &);
    Gamelist(const Gamelist &);
    ~Gamelist(void);

    Game& operator[](int i);
    bool remove(Game &);
    void add(const Game &);

    const Game& at(int i) const;
    int size(void) const;
    bool contains(const QString &) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent) const override;

    void printAllInfo(void) const;

public slots:
    void saveGame(int);
    void updateGameName(int, const QString &);
    void updateGameArchive(int, const QString &);
    void updateGameExecutable(int, const QString &);
    void updateGameArgument(int, const QString &);
    void updateGameArgumentConnect(int, const QString &);
    void updateGameExecutableServer(int, const QString &);
    void updateGameArgumentServer(int, const QString &);
    void updateGameVersionInfo(int, const QString &);
    void updateGameVersionFormat(int, const Version::VersionFormat &);
    void updateGameVersionFile(int, const QString &);
    void updateGameVersionQuery(int, const QString &);

private:
    QList<Game> *latestgamelist,
                *gamelist;

};

#endif // GAMELIST_H
