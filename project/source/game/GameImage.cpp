/* Copyright <2021> <Levin Jeck>
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

#include "game/GameImage.hpp"

#include <QFileInfo>
#include <QRegularExpression>
#include <QStringList>

#include "core/FileExtension.hpp"

namespace lanty
{

const QString GameImage::ICON_SUFFIX = QString("_icon");


GameImage::GameImage(const Game& game) noexcept : game(game) { }


QString GameImage::coverFilename(void) const noexcept
{
    return this->imageBaseFilename();
}

QString GameImage::iconFilename(void) const noexcept
{
    return this->imageBaseFilename().append(GameImage::ICON_SUFFIX);
}

QString GameImage::coverFilepath(const QDir& imageDirectory) const noexcept
{
    return this->imageFilepath(this->coverFilename(), imageDirectory);
}

QString GameImage::iconFilepath(const QDir& imageDirectory) const noexcept
{
    return this->imageFilepath(this->iconFilename(), imageDirectory);
}


QString GameImage::imageFilepath(const QString& imageFilename, const QDir& imageDirectory) const noexcept
{
    QStringList imageFileList;
    QString imageFilepath;

    imageFileList = imageDirectory.entryList(this->fileExtensionFilterForImages(), QDir::Files);

    for (QString image : imageFileList)
    {
        QString imageFileListFilename = QFileInfo(image).baseName();

        if (imageFileListFilename == imageFilename)
        {
            imageFilepath = imageDirectory.absoluteFilePath(image);
            break;
        }
    }

    return imageFilepath;
}

QString GameImage::imageBaseFilename(void) const noexcept
{
    QString gameName;
    QString lowerGameName;
    QString specialCharacters("-");
    QString imageBaseFilename;

    gameName = game.getName();
    lowerGameName = gameName.remove(QRegularExpression(specialCharacters)).simplified().toLower();
    imageBaseFilename = lowerGameName.replace(" ", "_").replace(".", "_");

    return imageBaseFilename;
}

QStringList GameImage::fileExtensionFilterForImages(void) const noexcept
{
    QStringList fileExtensionFilter;
    FileExtension fileExtension;

    fileExtensionFilter.append(fileExtension.toWildcard(FileExtension::BMP));
    fileExtensionFilter.append(fileExtension.toWildcard(FileExtension::JPEG));
    fileExtensionFilter.append(fileExtension.toWildcard(FileExtension::JPG));
    fileExtensionFilter.append(fileExtension.toWildcard(FileExtension::PNG));

    return fileExtensionFilter;
}

} /* namespace lanty */
