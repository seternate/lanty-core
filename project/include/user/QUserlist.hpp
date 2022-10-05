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

#include "core/JSONSerializable.hpp"
#include "core/YAMLSerializable.hpp"
#include "core/ltycore_global.hpp"
#include "user/QUser.hpp"

namespace lanty
{

class LTYCORE_EXPORT QUserlist : public QAbstractListModel, public JSONSerializable, public YAMLSerializable
{
    Q_DISABLE_COPY_MOVE(QUserlist)

public:
    QUserlist(void) = default;
    virtual ~QUserlist(void) = default;

    bool operator==(const QUserlist& userlist) const;
    bool operator!=(const QUserlist& userlist) const;
    QUser& operator[](const qint64 index);
    const QUser& operator[](const qint64 index) const;

    const QUser& at(const qint64 index) const;
    bool append(QUser* user);
    bool contains(const QUser* user) const;
    void remove(const QUser* user);
    quint64 size(void) const;
    void sortUsers(void);
    bool update(const QUserlist& userlist);

    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;

    nlohmann::json toJSON(void) const override;
    YAML::Node toYAML(void) const override;

private:
    QVector<std::shared_ptr<QUser>> list;
};

} /* namespace lanty */
