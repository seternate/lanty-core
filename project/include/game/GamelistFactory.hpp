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

#ifndef GAME_GAMELISTFACTORY_HPP
#define GAME_GAMELISTFACTORY_HPP

#include <memory>

#include "core/ltycore_global.hpp"
#include "game/Gamelist.hpp"
#include "helper/GameHelper.hpp"
#include "logging/Logger.hpp"
#include "system/FileExtension.hpp"
#include "system/QDirAdapter.hpp"
#include "system/QPixmapAdapter.hpp"
#include "yaml/YamlNode.hpp"

namespace lanty
{

class LTYCORE_EXPORT GamelistFactory
{
public:
    GamelistFactory(void);
    virtual ~GamelistFactory(void) = default;

    template<typename T>
    Gamelist* makeGamelist(const QDirAdapter &gameYamlFileDirectory, const QDirAdapter &gameImageFileDirectory)
    {
        Gamelist* gamelist = new Gamelist();
        std::shared_ptr<Game> game = nullptr;
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
                game = std::make_shared<T>();
                gameYamlAbsoluteFilePath = gameYamlFileDirectory.absoluteFilePath(gameYamlFiles.at(i));
                this->yamlNode->loadFromFile(gameYamlAbsoluteFilePath);
                game->load(*this->yamlNode);
                Logger() << "Create game from yaml-file '" << gameYamlAbsoluteFilePath << "'.";

                if(gameImageFileDirectory.isEmpty() == false)
                {
                    gameCoverImageAbsoluteFilePath
                        = this->gameHelper->getCoverImagePathFromDirectory(*game, gameImageFileDirectory);
                    if(pixmap->load(gameCoverImageAbsoluteFilePath) == false)
                    {
                        Logger(LogLevel::WARNING) << "Can not load gamecover from '" << gameCoverImageAbsoluteFilePath << "'.";
                    }
                    game->setCoverImage(*pixmap);

                    gameIconImageAbsoluteFilePath
                        = this->gameHelper->getIconImagePathFromDirectory(*game, gameImageFileDirectory);
                    if(pixmap->load(gameIconImageAbsoluteFilePath) == false)
                    {
                        Logger(LogLevel::WARNING) << "Can not load gameicon from '" << gameIconImageAbsoluteFilePath << "'.";
                    }
                    game->setIconImage(*pixmap);
                }
                else
                {
                    Logger(LogLevel::WARNING) << "No gameimage files found at '" << gameImageFileDirectory.absolutePath() << "'.";
                }

                gamelist->list.push_back(game);
                Logger() << "Added game '" << game->getName() << "' to gamelist.";
            }
        }
        else
        {
            Logger(LogLevel::WARNING) << "Can not create gamelist. No yaml-files at '" << gameYamlFileDirectory.absolutePath() << "'.";
        }

        return gamelist;
    }
    void setYamlNodeDependency(YamlNode *yamlNode);
    void setGameHelperDependency(GameHelper *gameHelper);
    void setQPixmapDependency(QPixmapAdapter *QPixmap);
    void resetDependencies(void);

private:
    std::shared_ptr<YamlNode> yamlNode;
    std::shared_ptr<GameHelper> gameHelper;
    std::shared_ptr<QPixmapAdapter> pixmap;
};

} /* namespace lanty */

#endif /* GAME_GAMELISTFACTORY_HPP */
