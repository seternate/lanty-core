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

#ifndef SYSTEM_QPIXMAPADAPTER_HPP
#define SYSTEM_QPIXMAPADAPTER_HPP

#include <QPixmap>
#include <QSize>
#include <QString>
#include <Qt>

#include "core/ltycore_global.hpp"

namespace lanty
{

class LTYCORE_EXPORT QPixmapAdapter
{
public:
    QPixmapAdapter(void) = default;
    QPixmapAdapter(const QSize& size);
    QPixmapAdapter(const QString& fileName, const char* format = nullptr, Qt::ImageConversionFlags flags = Qt::AutoColor);

    virtual bool load(const QString& fileName, const char* format = nullptr, Qt::ImageConversionFlags flags = Qt::AutoColor);
    virtual bool isNull(void) const;
    virtual QSize size(void) const;
    QPixmap& getQPixmap(void);

private:
    QPixmap pixmap;
};

} /* namespace lanty */

#endif /* SYSTEM_QPIXMAPADAPTER_HPP */
