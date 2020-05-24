#include "setting.h"

#include <fstream>

#include <QDebug>

Setting::Setting(const QString &yamlFile)
{
    this->base = YAML::LoadFile(yamlFile.toStdString());
    if(this->base.IsNull())
    {
        qDebug() << "Can not load YAML file '" << yamlFile << "'.\n";
        return;
    }
    this->yamlFile = yamlFile;
}

const QString Setting::getValue(const QString &key) const
{
    if(this->base[key.toStdString()].IsDefined())
    {
        return QString::fromStdString(this->base[key.toStdString()].as<std::string>());
    }
    return QString("");
}

const QString& Setting::getFile(void) const
{
    return yamlFile;
}

void Setting::setValue(const QString &key, const QString &value)
{
    this->base[key.toStdString()] = value.toStdString();
}

bool Setting::saveToFile(void)
{
    std::ofstream fout(this->yamlFile.toStdString());
    fout << this->base;
    return fout.good();
}
