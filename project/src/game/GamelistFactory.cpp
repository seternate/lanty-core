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

#include "game/GamelistFactory.hpp"

#include "game/Game.hpp"
#include "logging/Logger.hpp"
#include "system/FileExtension.hpp"

namespace lanty
{

GamelistFactory::GamelistFactory() : game(new Game()),
                                     yamlNode(new YamlNode()),
                                     gameHelper(new GameHelper()),
                                     pixmap(new QPixmapAdapter()) { }

Gamelist* GamelistFactory::makeGamelist(const QDirAdapter &gameYamlFileDirectory,
                                        const QDirAdapter &gameImageFileDirectory)
{
    Gamelist* gamelist = new Gamelist();
    QStringList gameFileExtensionFilter;
    QStringList gameYamlFiles;
    QString gameYamlAbsoluteFilePath("");
    QString gameCoverImageAbsoluteFilePath("");
    QString gameIconImageAbsoluteFilePath("");

    Logger() << "Create gamelist with yaml-files from '"
             << gameYamlFileDirectory.absolutePath()
             << "' and image-files from '"
             << gameImageFileDirectory.absolutePath()
             << "'.";

    gameFileExtensionFilter << FileExtension::YAML << FileExtension::YML;
    Logger(LogLevel::TRACE) << "Extensions to filter files: ";
    for(int i = 0; i < gameFileExtensionFilter.size() - 1; i++)
    {
         Logger(LogLevel::TRACE) << gameFileExtensionFilter.at(i) << ", ";
    }
    Logger(LogLevel::TRACE) << gameFileExtensionFilter.last();

    gameYamlFiles = gameYamlFileDirectory.entryList(gameFileExtensionFilter, QDir::Files);
    gameYamlFiles.removeOne(GameHelper::YAML_TEMPLATE_FILE);

    if(!gameYamlFileDirectory.isEmpty())
    {
        for(int32_t i = 0; i < gameYamlFiles.size(); i++)
        {
            gameYamlAbsoluteFilePath = gameYamlFileDirectory.absoluteFilePath(gameYamlFiles.at(i));
            this->yamlNode->loadFromFile(gameYamlAbsoluteFilePath);
            this->game->loadFromYamlNode(*this->yamlNode);
            Logger() << "Create game from yaml-file '" << gameYamlAbsoluteFilePath << "'.";

            if(gameImageFileDirectory.isEmpty() == false)
            {
                gameCoverImageAbsoluteFilePath
                    = this->gameHelper->getCoverImagePathFromDirectory(*this->game,
                                                                       gameImageFileDirectory);
                if(pixmap->load(gameCoverImageAbsoluteFilePath) == false)
                {
                    Logger(LogLevel::WARNING) << "Can not load gamecover from '" << gameCoverImageAbsoluteFilePath << "'.";
                }
                this->game->setCoverImage(*pixmap);

                gameIconImageAbsoluteFilePath
                    = this->gameHelper->getIconImagePathFromDirectory(*this->game,
                                                                      gameImageFileDirectory);
                if(pixmap->load(gameIconImageAbsoluteFilePath) == false)
                {
                    Logger(LogLevel::WARNING) << "Can not load gameicon from '" << gameIconImageAbsoluteFilePath << "'.";
                }
                this->game->setIconImage(*pixmap);
            }
            else
            {
                Logger(LogLevel::WARNING) << "No gameimage files found at '" << gameImageFileDirectory.absolutePath() << "'.";
            }

            gamelist->list.push_back(this->game);
            Logger() << "Added game '" << game->getName() << "' to gamelist.";
        }
    }
    else
    {
        Logger(LogLevel::WARNING) << "Can not create gamelist. No yaml-files at '" << gameYamlFileDirectory.absolutePath() << "'.";
    }

    return gamelist;
}

void GamelistFactory::setGameDependency(Game *game)
{
    if(game != nullptr)
    {
        this->game.reset(game);
        Logger(LogLevel::TRACE) << "Set game dependency for gamelistfactory.";
    }
}

void GamelistFactory::setYamlNodeDependency(YamlNode *yamlNode)
{
    if(yamlNode != nullptr)
    {
        this->yamlNode.reset(yamlNode);
        Logger(LogLevel::TRACE) << "Set yamlNode dependency for gamelistfactory.";
    }
}

void GamelistFactory::setGameHelperDependency(GameHelper *gameHelper)
{
    if(gameHelper != nullptr)
    {
        this->gameHelper.reset(gameHelper);
        Logger(LogLevel::TRACE) << "Set gameHelper dependency for gamelistfactory.";
    }
}

void GamelistFactory::setQPixmapDependency(QPixmapAdapter *qpixmap)
{
    if(qpixmap != nullptr)
    {
        this->pixmap.reset(qpixmap);
        Logger(LogLevel::TRACE) << "Set qpixmap dependency for gamelistfactory.";
    }
}

void GamelistFactory::resetDependencies(void)
{
    this->game.reset(new Game());
    this->yamlNode.reset(new YamlNode());
    this->gameHelper.reset(new GameHelper());
    this->pixmap.reset(new QPixmapAdapter());
    Logger(LogLevel::DEBUG) << "Reseted gamelistfactory dependencies.";
}

} /* namespace lanty */
