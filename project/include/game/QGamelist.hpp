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

#pragma once

#include <QAbstractListModel>
#include <QVariant>
#include <QVector>
#include <memory>
#include <nlohmann/json.hpp>

#include "core/Serializable.hpp"
#include "core/ltycore_global.hpp"
#include "game/Game.hpp"

namespace lanty
{

class LTYCORE_EXPORT QGamelist : public QAbstractListModel, public Serializable
{
    Q_DISABLE_COPY_MOVE(QGamelist)

public:
    QGamelist(void) = default;             // GCOVR_EXCL_LINE
    virtual ~QGamelist(void) = default;    // GCOVR_EXCL_LINE

    bool operator==(const QGamelist& gamelist) const;
    bool operator!=(const QGamelist& gamelist) const;
    Game& operator[](const qint64 index);
    const Game& operator[](const qint64 index) const;

    const Game& at(const qint64 index) const;
    bool append(Game* game);
    bool contains(const Game* game) const;
    quint64 size(void) const;
    void sortGames(void);
    bool update(const QGamelist& gamelist);

    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;

    nlohmann::json toJSON(void) const override;
    YAML::Node toYAML(void) const override;

private:
    QVector<std::shared_ptr<Game>> list;
};

} /* namespace lanty */
