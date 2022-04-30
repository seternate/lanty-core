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

#include "game/QGamelist.hpp"

namespace lanty
{

bool QGamelist::operator==(const QGamelist& gamelist) const
{
    bool result = false;

    for (std::shared_ptr<QGame> gamePtr : gamelist.list)
    {
        result = this->contains(gamePtr.get());
        if (result == false)
        {
            break;
        }
    }

    return result;
}

bool QGamelist::operator!=(const QGamelist& gamelist) const
{
    return !(this->operator==(gamelist));
}

QGame& QGamelist::operator[](const qint64 index)
{
    return *(this->list[index]);
}

const QGame& QGamelist::operator[](const qint64 index) const
{
    return *(this->list[index]);
}


const QGame& QGamelist::at(const qint64 index) const
{
    return *(this->list.at(index).get());
}

bool QGamelist::append(QGame* game)
{
    bool gameWasAppended = false;

    if (this->contains(game) == false)
    {
        beginInsertRows(QModelIndex(), this->size(), this->size());
        this->list.append(std::shared_ptr<QGame>(game));
        endInsertRows();
        gameWasAppended = true;
    }

    return gameWasAppended;
}

bool QGamelist::contains(const QGame* game) const
{
    bool foundEqualGameInList = false;

    for (std::shared_ptr<QGame> gamePtrFromList : this->list)
    {
        if (*game == *gamePtrFromList.get())
        {
            foundEqualGameInList = true;
            break;
        }
    }

    return foundEqualGameInList;
}

void QGamelist::remove(const QGame* game)
{
    for (qint64 i = 0; i < this->list.size(); i++)
    {
        QGame* listgame = this->list.at(i).get();
        if (game == listgame)
        {
            beginRemoveRows(QModelIndex(), i, i);
            this->list.remove(i);
            endRemoveRows();
        }
    }
}

quint64 QGamelist::size(void) const
{
    return this->list.size();
}

void QGamelist::sortGames(void)
{
    beginResetModel();
    std::sort(this->list.begin(), this->list.end(), [](std::shared_ptr<QGame> l, std::shared_ptr<QGame> r) {
        return *l.get() < *r.get();
    });
    endResetModel();
}

bool QGamelist::update(const QGamelist& gamelist)
{
    bool updated = false;

    for (std::shared_ptr<QGame> gamePtr : gamelist.list)
    {
        if (this->contains(gamePtr.get()) == false)
        {
            beginInsertRows(QModelIndex(), this->size(), this->size());
            this->list.append(gamePtr);
            endInsertRows();
            updated = true;
        }
    }

    for (std::shared_ptr<QGame> gamePtr : this->list)
    {
        if (gamelist.contains(gamePtr.get()) == false)
        {
            beginRemoveRows(QModelIndex(), this->list.indexOf(gamePtr), this->list.indexOf(gamePtr));
            this->list.removeOne(gamePtr);
            endRemoveRows();
            updated = true;
        }
    }

    return updated;
}


int QGamelist::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return this->list.size();
}

QVariant QGamelist::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }
    if (role == Qt::DisplayRole)
    {
        QString gameName = this->list.at(index.row())->getName();
        return QVariant::fromValue(gameName);
    }

    return QVariant();
}


nlohmann::json QGamelist::toJSON(void) const
{
    nlohmann::json json = nlohmann::json::array();

    for (std::shared_ptr<Game> gamePtr : this->list)
    {
        json.push_back(gamePtr->toJSON());
    }

    return json;
}

YAML::Node QGamelist::toYAML(void) const
{
    YAML::Node yaml;

    for (std::shared_ptr<QGame> gamePtr : this->list)
    {
        yaml.push_back(gamePtr->toYAML());
    }

    return yaml;
}

} /* namespace lanty */
