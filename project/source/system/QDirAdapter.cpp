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

#include "system/QDirAdapter.hpp"

namespace lanty
{

QDirAdapter::QDirAdapter(const QString& path) : qDir(path) { }

QDirAdapter::QDirAdapter(const QString& path, const QString& nameFilter, QDir::SortFlags sort, QDir::Filters filters) :
    qDir(path, nameFilter, sort, filters)
{ }

QStringList QDirAdapter::entryList(const QStringList& nameFilters, QDir::Filters filters, QDir::SortFlags sort) const
{
    return this->qDir.entryList(nameFilters, filters, sort);
}

bool QDirAdapter::isEmpty(QDir::Filters filters) const
{
    return this->qDir.isEmpty(filters);
}

QString QDirAdapter::absoluteFilePath(const QString& fileName) const
{
    return this->qDir.absoluteFilePath(fileName);
}

QString QDirAdapter::absolutePath(void) const
{
    return qDir.absolutePath();
}

} /* namespace lanty */
