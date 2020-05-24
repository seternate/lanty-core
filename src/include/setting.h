#ifndef SETTING_H
#define SETTING_H

#include <QObject>
#include <yaml-cpp/yaml.h>

#include "ltycore_global.h"

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

#endif // SETTING_H
