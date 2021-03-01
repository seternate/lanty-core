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

#ifndef USER_USERLIST_HPP
#define USER_USERLIST_HPP

#include <QAbstractListModel>
#include <QObject>
#include <QVector>

#include "core/ltycore_global.hpp"
#include "user/User.hpp"

namespace lanty
{

class LTYCORE_EXPORT Userlist : public QAbstractListModel
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(Userlist)

public:
    Userlist(void) = default;
    virtual ~Userlist(void) = default;

    User& operator[](const qint32 index);
    const User& operator[](const qint32 index) const;

    virtual const User& at(const qint32 index) const;
    virtual const User& append(User* game);
    virtual void remove(const User* game);
    virtual quint32 size(void) const;

    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;

private:
    QVector<std::shared_ptr<User>> userlist;
};

} /* namespace lanty */

#endif /* USER_USERLIST_HPP */
