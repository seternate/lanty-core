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

#ifndef GAME_GAMELIST_HPP
#define GAME_GAMELIST_HPP

#include <memory>
#include <QVector>

#include "core/ltycore_global.hpp"
#include "game/Game.hpp"

namespace lanty
{

class LTYCORE_EXPORT Gamelist
{
    friend class GamelistFactory;

public:
    Gamelist(void) = default;
    explicit Gamelist(const Gamelist &list) = delete;
    explicit Gamelist(const Gamelist &&list);
    virtual ~Gamelist(void) = default;

    Gamelist& operator=(const Gamelist &list) = delete;
    Gamelist& operator=(const Gamelist &&list);
    Game& operator[](const qint32 index);
    const Game& operator[](const qint32 index) const;

    virtual const Game& at(const qint32 index) const;
    virtual qint32 size(void) const;

private:
    QVector<std::shared_ptr<Game>> list;
};

} /* namespace lanty */

#endif /* GAME_GAMELIST_HPP */
