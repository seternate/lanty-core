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

#include "game/QGamelistFactory.hpp"

#include "core/FileExtension.hpp"
#include "game/GameImage.hpp"
#include "game/GameLoader.hpp"

#include "QDebug"

namespace lanty
{

const QString QGamelistFactory::YAML_TEMPLATE_FILE = "template.yaml";
const std::string QGamelistFactory::GAME_DESERIALIZER_KEY = "game";

QGamelist* QGamelistFactory::makeQGamelist(const QDir& gameYamlDirectory, const QDir& gameImageDirectory) const
{
    QGamelist* gamelist = nullptr;

    gamelist = this->loadGamesFromYamlFiles(this->getAllYamlFiles(gameYamlDirectory));
    this->loadGameImages(gamelist, gameImageDirectory);

    return gamelist;
}


QFileInfoList QGamelistFactory::getAllYamlFiles(const QDir& gameYamlDirectory) const
{
    QFileInfoList yamlFiles = gameYamlDirectory.entryInfoList(this->yamlFileFilter(), QDir::Files, QDir::Name);

    QFileInfo yamlTemplateFile(gameYamlDirectory.absoluteFilePath(QGamelistFactory::YAML_TEMPLATE_FILE));
    yamlFiles.removeOne(yamlTemplateFile);

    return yamlFiles;
}

QStringList QGamelistFactory::yamlFileFilter(void) const
{
    QStringList yamlFileFilters;
    FileExtension fileextension;

    yamlFileFilters << fileextension.toWildcard(FileExtension::YAML) << fileextension.toWildcard(FileExtension::YML);

    return yamlFileFilters;
}

QGamelist* QGamelistFactory::loadGamesFromYamlFiles(const QFileInfoList& yamlFiles) const
{
    QGamelist* gamelist = nullptr;

    if (yamlFiles.isEmpty() == false)
    {
        gamelist = new QGamelist();
        GameLoader gameloader;

        for (qint64 i = 0; i < yamlFiles.size(); i++)
        {
            QString yamlFilePath = yamlFiles.at(i).absoluteFilePath();
            YAML::Node yaml = YAML::LoadFile(yamlFilePath.toStdString());
            YAML::Node yamlGame = yaml[QGamelistFactory::GAME_DESERIALIZER_KEY];

            Game game = gameloader.load(yamlGame);
            game.setFilepath(yamlFilePath);
            gamelist->append(new QGame(game));
        }
    }

    return gamelist;
}

void QGamelistFactory::loadGameImages(QGamelist* const gamelist, const QDir& gameImageDirectory) const
{
    QGame* game = nullptr;

    for (quint64 i = 0; i < gamelist->size(); i++)
    {
        game = &gamelist->operator[](i);
        GameImage gameimage(*game);

        QPixmap icon(gameimage.iconFilepath(gameImageDirectory));
        QPixmap cover(gameimage.coverFilepath(gameImageDirectory));

        game->setIcon(icon);
        game->setCover(cover);
    }
}

} /* namespace lanty */
