#ifndef VERSION_H
#define VERSION_H

#include <QObject>

#include <yaml-cpp/yaml.h>

#include "../core/ltycore_global.hpp"

class LTYCORE_EXPORT Version : public QObject
{

    Q_OBJECT

public:
    enum VersionFormat
    {
        EXECUTABLE = 0x01,
        FILE = 0x02,
        NONE = 0x00
    };

    Version();
    Version(const YAML::Node &, const QString &);
    Version(const Version &);

    const QString& getInfo(void) const;
    const Version::VersionFormat& getVersionFormat(void) const;
    const QString& getFile(void) const;
    const QString& getQuery(void) const;
    bool isVersion(void) const;
    const YAML::Node& toNode(void) const;

    void setInfo(const QString &);
    void setVersionFormat(const Version::VersionFormat &);
    void setFile(const QString &);
    void setQuery(const QString &);

    const QString formatToQString(void) const;

    static Version::VersionFormat toVersionFormat(const QString &);

private:
    QString yamlFile;
    YAML::Node base;
    Version::VersionFormat versionFormat;
    QString info,
        file,
        query;

};

#endif // VERSION_H
