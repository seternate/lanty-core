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
#include <QAbstractListModel>
#include <QVector>

#include "core/ltycore_global.hpp"
#include "game/Game.hpp"

namespace lanty
{

class LTYCORE_EXPORT Gamelist : public QAbstractListModel
{
    Q_DISABLE_COPY_MOVE(Gamelist)

    friend class GamelistFactory;

public:
    Gamelist(void) = default;
    virtual ~Gamelist(void) = default;

    Game& operator[](const qint32 index);
    const Game& operator[](const qint32 index) const;

    virtual const Game& at(const qint32 index) const;
    virtual const Game& append(Game* game);
    virtual void load(Gamelist *gamelist);
    virtual void remove(const Game* game);
    virtual quint32 size(void) const;

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

private:
    QVector<std::shared_ptr<Game>> list;
};

} /* namespace lanty */

#endif /* GAME_GAMELIST_HPP */
