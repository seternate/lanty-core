#include "version.h"

#include <QDebug>

Version::Version()
{
    this->setInfo("");
    this->setFile("");
    this->setQuery("");
}

Version::Version(const YAML::Node &base, const QString &yamlFile)
{   
    if(true == base.IsNull())
    {
        qDebug() << "Empty 'version' node in '" << yamlFile << "'.\n";
    }

    this->base = base;

    if(true == base["info"].IsDefined())
    {
        this->setInfo(QString::fromStdString(base["info"].as<std::string>()));
    }
    else
    {
        this->setInfo("");
    }

    if(true == base["format"].IsDefined())
    {
        this->setVersionFormat(Version::toVersionFormat(QString::fromStdString(base["format"].as<std::string>())));
    }
    else
    {
        this->setVersionFormat(VersionFormat::NONE);
    }

    if(true == base["file"].IsDefined())
    {
        this->setFile(QString::fromStdString(base["file"].as<std::string>()));
    }
    else
    {
        this->setFile("");
    }

    if(true == base["query"].IsDefined())
    {
        this->setQuery(QString::fromStdString(base["query"].as<std::string>()));
    }
    else
    {
        this->setQuery("");
    }

    //TODO: Beim Einlesen check ob Felder in richtiger Abhängigkeit vorhanden sind.

    this->yamlFile = yamlFile;
}

Version::Version(const Version &version) : QObject()
{
    this->base = version.base;
    this->setInfo(version.getInfo());
    this->setVersionFormat(version.getVersionFormat());
    this->setFile(version.getFile());
    this->setQuery(version.getQuery());
}

const QString& Version::getInfo(void) const
{
    return this->info;
}

const Version::VersionFormat& Version::getVersionFormat(void) const
{
    return this->versionFormat;
}

const QString& Version::getFile(void) const
{
    return this->file;
}

const QString& Version::getQuery(void) const
{
    return this->query;
}

bool Version::isVersion(void) const
{
    return false == this->getInfo().isEmpty();
}

const YAML::Node& Version::toNode(void) const
{
    return base;
}

void Version::setInfo(const QString &info)
{
    this->info = info;
    this->base["info"] = info.toStdString();
    if(info.isEmpty())
    {
        this->setVersionFormat(VersionFormat::NONE);
        this->base["format"] = this->formatToQString().toStdString();
        this->setFile("");
        this->base["file"] = this->getFile().toStdString();
        this->setQuery("");
        this->base["query"] = this->getQuery().toStdString();
    }
}

void Version::setVersionFormat(const Version::VersionFormat &format)
{
    if(getInfo().isEmpty())
    {
        this->versionFormat = VersionFormat::NONE;
        this->base["format"] = this->formatToQString().toStdString();
        return;
    }
    else if(format == VersionFormat::EXECUTABLE)
    {
        setFile("");
        this->base["file"] = this->getFile().toStdString();
        setQuery("");
        this->base["query"] = this->getQuery().toStdString();
    }
    this->versionFormat = format;
    this->base["format"] = this->formatToQString().toStdString();
}

void Version::setFile(const QString & file)
{
    this->file = file;
    this->base["file"] = this->getFile().toStdString();
}

void Version::setQuery(const QString &query)
{
    this->query = query;
    this->base["query"] = this->getQuery().toStdString();
}

const QString Version::formatToQString(void) const
{
    if(this->getVersionFormat() == VersionFormat::EXECUTABLE)
    {
        return "executable";
    }
    if(this->getVersionFormat() == VersionFormat::FILE)
    {
        return "file";
    }
    return "NONE";
}

Version::VersionFormat Version::toVersionFormat(const QString &versionFormat)
{
    if(versionFormat.toLower() == "executable" || versionFormat.toLower() == "exe")
    {
        return VersionFormat::EXECUTABLE;
    }

    if(versionFormat.toLower() == "file")
    {
        return VersionFormat::FILE;
    }

    return VersionFormat::NONE;
}
