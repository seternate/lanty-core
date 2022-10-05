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

#include "game/GameLoader.hpp"
#include "game/GameClientLoader.hpp"
#include "game/GameServerLoader.hpp"
#include "game/GameVersionLoader.hpp"

#include <string>

namespace lanty
{

Game GameLoader::load(const YAML::Node& yaml) const
{
    Game game;

    game.setName(this->loadFieldAsQString(yaml, Game::NAME_SERIALIZER_KEY));
    game.setArchiveFileName(this->loadFieldAsQString(yaml, Game::ARCHIVE_SERIALIZER_KEY));
    game.client = GameClientLoader().load(this->loadFieldAsYAML(yaml, Game::CLIENT_SERIALIZER_KEY));
    game.server = GameServerLoader().load(this->loadFieldAsYAML(yaml, Game::SERVER_SERIALIZER_KEY));
    game.version = GameVersionLoader().load(this->loadFieldAsYAML(yaml, Game::VERSION_SERIALIZER_KEY));

    return game;
}

} /* namespace lanty */
