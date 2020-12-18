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
#include "helper/GameHelper.hpp"
#include "system/FileExtension.hpp"
#include "system/QPixmapAdapter.hpp"
#include "yaml/YamlNode.hpp"

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

    gameFileExtensionFilter << FileExtension::YAML << FileExtension::YML;

    if(!gameYamlFileDirectory.isEmpty())
    {
        gameYamlFiles = gameYamlFileDirectory.entryList(gameFileExtensionFilter, QDir::Files);
        gameYamlFiles.removeOne(GameHelper::YAML_TEMPLATE_FILE);

        for(int32_t i = 0; i < gameYamlFiles.size(); i++)
        {
            gameYamlAbsoluteFilePath = gameYamlFileDirectory.absoluteFilePath(gameYamlFiles.at(i));
            this->yamlNode->loadFromFile(gameYamlAbsoluteFilePath);
            this->game->loadFromYamlNode(*this->yamlNode);

            if(gameImageFileDirectory.isEmpty() == false)
            {
                gameCoverImageAbsoluteFilePath
                    = this->gameHelper->getCoverImagePathFromDirectory(*this->game,
                                                                       gameImageFileDirectory);
                pixmap->load(gameCoverImageAbsoluteFilePath);
                this->game->setCoverImage(*pixmap);

                gameIconImageAbsoluteFilePath
                    = this->gameHelper->getIconImagePathFromDirectory(*this->game,
                                                                      gameImageFileDirectory);
                pixmap->load(gameIconImageAbsoluteFilePath);
                this->game->setIconImage(*pixmap);
            }

            gamelist->list.push_back(this->game);
        }
    }

    return gamelist;
}

void GamelistFactory::setGameDependency(Game *game)
{
    this->game.reset(game);
}

void GamelistFactory::setYamlNodeDependency(YamlNode *yamlNode)
{
    this->yamlNode.reset(yamlNode);
}

void GamelistFactory::setGameHelperDependency(GameHelper *gameHelper)
{
    this->gameHelper.reset(gameHelper);
}

void GamelistFactory::setQPixmapDependency(QPixmapAdapter *QPixmap)
{
    this->pixmap.reset(QPixmap);
}

void GamelistFactory::resetDependencies(void)
{
    this->game.reset(new Game());
    this->yamlNode.reset(new YamlNode());
    this->gameHelper.reset(new GameHelper());
    this->pixmap.reset(new QPixmapAdapter());
}


void GamelistFactory::initDependencies()
{
    if(this->game == nullptr)
    {
        this->game.reset(new Game());
    }
    if(this->yamlNode == nullptr)
    {
        this->yamlNode.reset(new YamlNode());
    }
    if(this->gameHelper == nullptr)
    {
        this->gameHelper.reset(new GameHelper());
    }
    if(this->pixmap == nullptr)
    {
        this->pixmap.reset(new QPixmapAdapter());
    }
}

} /* namespace lanty */
