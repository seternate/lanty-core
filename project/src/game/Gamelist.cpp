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

#include "game/Gamelist.hpp"

#include "game/Game.hpp"
#include "yaml/YamlNode.hpp"

namespace lanty
{

Game& Gamelist::operator[](const qint32 index)
{
    return *list[index];
}

const Game &Gamelist::operator[](const qint32 index) const
{
    return *list[index];
}


const Game& Gamelist::at(const qint32 index) const
{
    return *list.at(index);
}

const Game& Gamelist::append(Game *game)
{
    std::shared_ptr<Game> newGame(game);
    beginInsertRows(QModelIndex(), this->size(), this->size());
    this->list.append(newGame);
    endInsertRows();
    return *newGame;
}

void Gamelist::remove(const Game *game)
{
    for(qint32 i = 0; i < this->list.size(); i++)
    {
        Game *listgame = this->list.at(i).get();
        if(game == listgame)
        {
            beginRemoveRows(QModelIndex(), i, i);
            this->list.remove(i);
            endRemoveRows();
        }
    }
}

quint32 Gamelist::size(void) const
{
    return list.size();
}


int Gamelist::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return this->list.size();
}

QVariant Gamelist::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
    {
        return QVariant();
    }
    if(index.row() >= this->list.size())
    {
        return QVariant();
    }
    if(role == Qt::DisplayRole)
    {
        QString gameName = this->list.at(index.row())->getName();
        return QVariant::fromValue(gameName);
    }

    return QVariant();
}

} /* namespace lanty */
