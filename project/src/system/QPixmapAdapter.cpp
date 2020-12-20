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

#include "system/QPixmapAdapter.hpp"

namespace lanty
{

QPixmapAdapter::QPixmapAdapter(const QString &fileName,
                               const char *format,
                               Qt::ImageConversionFlags flags) : pixmap(fileName, format, flags) { }

QPixmapAdapter::QPixmapAdapter(const QSize &size) : pixmap(size) { }

bool QPixmapAdapter::load(const QString &fileName, const char *format, Qt::ImageConversionFlags flags)
{
    return pixmap.load(fileName, format, flags);
}

bool QPixmapAdapter::isNull(void) const
{
    return pixmap.isNull();
}

QSize QPixmapAdapter::size(void) const
{
    return pixmap.size();
}

QPixmap& QPixmapAdapter::getQPixmap(void)
{
    return pixmap;
}

} /*namespace lanty */
