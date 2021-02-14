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

#include "helper/GameHelper.hpp"

#include <QRegularExpression>
#include <QStringList>
#include <cstdint>

#include "logging/Logger.hpp"
#include "system/FileExtension.hpp"

namespace lanty
{

const QString GameHelper::YAML_TEMPLATE_FILE("template.yaml");


QString GameHelper::getCoverImagePathFromDirectory(const Game& game, const QDirAdapter& gameImageFileDirectory)
{
    return getImagePathFromDirectory(game, gameImageFileDirectory);
}

QString GameHelper::getIconImagePathFromDirectory(const Game& game, const QDirAdapter& gameImageFileDirectory)
{
    return getImagePathFromDirectory(game, gameImageFileDirectory, QString("_icon"));
}

QString GameHelper::formatNameToCoverImageFileName(const Game& game)
{
    return formatNameToImageFileName(game);
}

QString GameHelper::formatNameToIconImageFileName(const Game& game)
{
    return formatNameToImageFileName(game, QString("_icon"));
}


QString GameHelper::getImagePathFromDirectory(const Game& game,
                                              const QDirAdapter& gameImageFileDirectory,
                                              const QString& imageFileNameSuffix)
{
    QStringList gameImageExtensionFilter;
    QStringList gameImageFiles;
    QString gameImageFile("");
    QString gameImageFileNameWithoutExtension("");
    QString gameNameFormatedToGameImageFileName("");
    QString gameImageAbsoluteFilePath("");

    gameImageExtensionFilter << FileExtension::PNG << FileExtension::JPG << FileExtension::JPEG << FileExtension::BMP;
    gameImageFiles = gameImageFileDirectory.entryList(gameImageExtensionFilter, QDir::Files);

    if (gameImageFiles.isEmpty() == false)
    {
        Logger() << "Found " << QString::number(gameImageFiles.size()) << " game images at '"
                 << gameImageFileDirectory.absolutePath() << "'.";
        for (int32_t i = 0; i < gameImageFiles.size(); i++)
        {
            gameImageFile = gameImageFiles.at(i);
            gameImageFileNameWithoutExtension = gameImageFile.split(".")[0];
            gameNameFormatedToGameImageFileName = formatNameToImageFileName(game, imageFileNameSuffix);

            if (gameImageFileNameWithoutExtension == gameNameFormatedToGameImageFileName)
            {
                gameImageAbsoluteFilePath = gameImageFileDirectory.absoluteFilePath(gameImageFile);
                break;
            }
        }
    }
    else
    {
        Logger() << "Can not return image path from game '" << game.getName() << "'. No image file at directory '"
                 << gameImageFileDirectory.absolutePath() << "'.";
    }

    return gameImageAbsoluteFilePath;
}

QString GameHelper::formatNameToImageFileName(const Game& game, const QString& imageFileNameSuffix)
{
    QString name("");
    QString lowerName("");
    QString specialCharacters("-");
    QString result("");

    name = game.getName();
    lowerName = name.remove(QRegularExpression(specialCharacters)).simplified().toLower();
    result = lowerName.replace(" ", "_").replace(".", "_") + imageFileNameSuffix;

    return result;
}

} /* namespace lanty */
