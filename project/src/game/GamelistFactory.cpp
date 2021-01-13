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

namespace lanty
{

GamelistFactory::GamelistFactory() : yamlNode(std::make_shared<YamlNode>()),
                                        gameHelper(std::make_shared<GameHelper>()),
                                        pixmap(std::make_shared<QPixmapAdapter>()) { }


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
    this->yamlNode.reset(new YamlNode());
    this->gameHelper.reset(new GameHelper());
    this->pixmap.reset(new QPixmapAdapter());
    Logger(LogLevel::DEBUG) << "Reseted gamelistfactory dependencies.";
}

} /* namespace lanty */
