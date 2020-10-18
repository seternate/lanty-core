#ifndef SETTING_SETTING_HPP
#define SETTING_SETTING_HPP

#include <QObject>

#include <yaml-cpp/yaml.h>

#include "../core/ltycore_global.hpp"

class LTYCORE_EXPORT Setting : public QObject
{

    Q_OBJECT

public:
    Setting(const QString &);

    const QString getValue(const QString &) const;
    const QString& getFile(void) const;

    void setValue(const QString &, const QString &);

public slots:
    bool saveToFile(void);

private:
    YAML::Node base;
    QString yamlFile;

};

#endif // SETTING_SETTING_HPP
