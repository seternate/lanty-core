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

#include "user/Userlist.hpp"

namespace lanty
{

User& Userlist::operator[](const qint32 index)
{
    return *this->userlist[index];
}

const User& Userlist::operator[](const qint32 index) const
{
    return *this->userlist[index];
}


const User& Userlist::at(const qint32 index) const
{
    return *this->userlist.at(index);
}

const User& Userlist::append(User* user)
{
    std::shared_ptr<User> newUser(user);
    beginInsertRows(QModelIndex(), this->size(), this->size());
    this->userlist.append(newUser);
    endInsertRows();
    return *newUser;
}

void Userlist::remove(const User* user)
{
    for (qint32 i = 0; i < this->userlist.size(); i++)
    {
        User* listuser = this->userlist.at(i).get();
        if (user == listuser)
        {
            beginRemoveRows(QModelIndex(), i, i);
            this->userlist.remove(i);
            endRemoveRows();
        }
    }
}

quint32 Userlist::size(void) const
{
    return this->userlist.size();
}


int Userlist::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return this->userlist.size();
}

QVariant Userlist::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }
    if (index.row() >= this->userlist.size())
    {
        return QVariant();
    }
    if (role == Qt::DisplayRole)
    {
        QString username = this->userlist.at(index.row())->getUsername();
        return QVariant::fromValue(username);
    }

    return QVariant();
}

} /* namespace lanty */
