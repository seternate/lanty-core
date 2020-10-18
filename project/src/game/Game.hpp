#ifndef GAME_GAME_HPP
#define GAME_GAME_HPP

#include <QDir>
#include <QObject>
#include <QPixmap>

#include "../core/ltycore_global.hpp"
#include "GameVersion.hpp"

class LTYCORE_EXPORT Game : public QObject
{

    Q_OBJECT

public:
    Game(void);
    Game(const QString &yamlfile);
    Game(const QString &yamlfile, const QString &imagepath);
    Game(const QDir &yamldir, const QString &gameName);
    Game(const Game &game);
    ~Game(void);

    Game& operator=(const Game &game);
    bool operator==(const Game &game) const;

    const QString& getName(void) const;
    const QString& getArchive(void) const;
    const QString& getExecutable(void) const;
    const QString& getArgument(void) const;
    const QString& getArgumentConnect(void) const;
    const QString& getExecutableServer(void) const;
    const QString& getArgumentServer(void) const;
    const QString& getVersionInfo(void) const;
    const Version::VersionFormat& getVersionFormat(void) const;
    const QString& getVersionFile(void) const;
    const QString& getVersionQuery(void) const;
    const Version& getVersion(void) const;
    const QString& getImagePath(void) const;
    const QPixmap getCover(void) const;
    const QPixmap getIcon(void) const;
    bool canConnectDirect(void) const;
    bool canOpenServer(void) const;
    bool isVersion(void) const;

    bool deleteFile(void);

    void printInfo(void) const;

public slots:
    bool setName(const QString &gameName);
    bool setArchive(const QString &archiveFilePath);
    bool setExecutable(const QString &clientExecutableFilePath);
    void setArgument(const QString &clientCommandLineArgument);
    void setArgumentConnect(const QString &clientConnectCommandLineArgument);
    void setExecutableServer(const QString &serverExecutable);
    void setArgumentServer(const QString &serverCommandLineArgument);
    void setVersionInfo(const QString &versionInfo);
    void setVersionFormat(const Version::VersionFormat &format);
    void setVersionFile(const QString &file);
    void setVersionQuery(const QString &query);
    void setImagePath(const QString &imagepath);
    bool saveToFile(void);

signals:
    void nameChanged(const QString &newName);

private:
    QString yamlFilePath;
    YAML::Node loadedYamlFile;
    QString gameName;
    QString archiveFilePath;
    QString clientExecutableFilePath;
    QString clientCommandLineArgument;
    QString clientConnectCommandLineArgument;
    QString serverExecutableFilePath;
    QString serverCommandLineArgument;
    QString imagePath;
    bool connectDirect, openServer;
    Version *version;

};

#endif // GAME_GAME_HPP
