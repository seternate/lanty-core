#ifndef GAME_H
#define GAME_H

#include <QDir>
#include <QObject>
#include <QPixmap>

#include "ltycore_global.h"
#include "version.h"

class LTYCORE_EXPORT Game : public QObject
{

    Q_OBJECT

public:
    Game(const QString &yamlfile);
    Game(const QString &yamlfile, const QString &imagepath);
    Game(const QDir &yamldir, const QString &name);
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
    bool setName(const QString &name);
    bool setArchive(const QString &archive);
    bool setExecutable(const QString &executable);
    void setArgument(const QString &argStart);
    void setArgumentConnect(const QString &argConnect);
    void setExecutableServer(const QString &serverExecutable);
    void setArgumentServer(const QString &argServer);
    void setVersionInfo(const QString &versionInfo);
    void setVersionFormat(const Version::VersionFormat &format);
    void setVersionFile(const QString &file);
    void setVersionQuery(const QString &query);
    void setImagePath(const QString &imagepath);
    bool saveToFile(void);

private:
    QString yamlFile;
    YAML::Node base;
    QString name,
        archive,
        executable,
        argStart,
        argConnect,
        executableServer,
        argServer,
        imagePath;
    bool connectDirect, openServer;
    Version *version;

};

#endif // GAME_H
