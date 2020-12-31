/* Copyright <2020> <Levin Jeck>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef SYSTEM_QDIRADAPTER_HPP
#define SYSTEM_QDIRADAPTER_HPP

#include <QString>
#include <QDir>

#include "core/ltycore_global.hpp"

namespace lanty
{

class LTYCORE_EXPORT QDirAdapter
{
public:
    QDirAdapter(const QString &path = QString());
    QDirAdapter(const QString &path,
                const QString &nameFilter,
                QDir::SortFlags sort = QDir::SortFlags(QDir::Name | QDir::IgnoreCase),
                QDir::Filters filters = QDir::AllEntries);
    virtual ~QDirAdapter(void) = default;

    virtual QStringList entryList(const QStringList &nameFilters,
                                  QDir::Filters filters = QDir::NoFilter,
                                  QDir::SortFlags sort = QDir::NoSort) const;
    virtual bool isEmpty(QDir::Filters filters = QDir::Filters(QDir::AllEntries | QDir::NoDotAndDotDot)) const;
    virtual QString absoluteFilePath(const QString &fileName) const;
    virtual QString absolutePath(void) const;

private:
    QDir qDir;
};

} /* namespace lanty */

#endif /* SYSTEM_QDIRADAPTER_HPP */
