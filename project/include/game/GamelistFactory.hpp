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

    virtual Gamelist* makeGamelist(const QDirAdapter &gameYamlFileDirectory, const QDirAdapter &gameImageFileDirectory);
    void setGameDependency(Game *game);
    void setYamlNodeDependency(YamlNode *yamlNode);
    void setGameHelperDependency(GameHelper *gameHelper);
    void setQPixmapDependency(QPixmapAdapter *QPixmap);
    void resetDependencies(void);

private:
    std::shared_ptr<Game> game;
    std::shared_ptr<YamlNode> yamlNode;
    std::shared_ptr<GameHelper> gameHelper;
    std::shared_ptr<QPixmapAdapter> pixmap;

    void initDependencies(void);
};

} /* namespace lanty */

#endif /* GAME_GAMELISTFACTORY_HPP */
