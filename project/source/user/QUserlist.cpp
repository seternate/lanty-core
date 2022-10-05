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

#include "user/QUserlist.hpp"

namespace lanty
{

bool QUserlist::operator==(const QUserlist& userlist) const
{
    bool result = false;

    for (std::shared_ptr<QUser> userPtr : userlist.list)
    {
        result = this->contains(userPtr.get());
        if (result == false)
        {
            break;
        }
    }

    return result;
}

bool QUserlist::operator!=(const QUserlist& userlist) const
{
    return !(this->operator==(userlist));
}

QUser& QUserlist::operator[](const qint64 index)
{
    return *(this->list[index]);
}

const QUser& QUserlist::operator[](const qint64 index) const
{
    return *(this->list[index]);
}


const QUser& QUserlist::at(const qint64 index) const
{
    return *(this->list.at(index).get());
}

bool QUserlist::append(QUser* user)
{
    bool userWasAppended = false;

    if (this->contains(user) == false)
    {
        beginInsertRows(QModelIndex(), this->size(), this->size());
        this->list.append(std::shared_ptr<QUser>(user));
        endInsertRows();
        userWasAppended = true;
    }

    return userWasAppended;
}

bool QUserlist::contains(const QUser* user) const
{
    bool foundEqualUserInList = false;

    for (std::shared_ptr<QUser> userPtrFromList : this->list)
    {
        QUser& userFromList = *userPtrFromList.get();

        if (user->operator==(userFromList))
        {
            foundEqualUserInList = true;
            break;
        }
    }

    return foundEqualUserInList;
}

void QUserlist::remove(const QUser* user)
{
    for (qint64 i = 0; i < this->list.size(); i++)
    {
        QUser* listuser = this->list.at(i).get();
        if (user == listuser)
        {
            beginRemoveRows(QModelIndex(), i, i);
            this->list.remove(i);
            endRemoveRows();
        }
    }
}

quint64 QUserlist::size(void) const
{
    return this->list.size();
}

void QUserlist::sortUsers(void)
{
    beginResetModel();
    std::sort(this->list.begin(), this->list.end(), [](std::shared_ptr<QUser> l, std::shared_ptr<QUser> r) {
        return *l.get() < *r.get();
    });
    endResetModel();
}

bool QUserlist::update(const QUserlist& userlist)
{
    bool updated = false;

    for (std::shared_ptr<QUser> userPtr : userlist.list)
    {
        if (this->contains(userPtr.get()) == false)
        {
            beginInsertRows(QModelIndex(), this->size(), this->size());
            this->list.append(userPtr);
            endInsertRows();
            updated = true;
        }
    }

    for (std::shared_ptr<QUser> userPtr : this->list)
    {
        if (userlist.contains(userPtr.get()) == false)
        {
            beginRemoveRows(QModelIndex(), this->list.indexOf(userPtr), this->list.indexOf(userPtr));
            this->list.removeOne(userPtr);
            endRemoveRows();
            updated = true;
        }
    }

    return updated;
}


int QUserlist::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return this->list.size();
}

QVariant QUserlist::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }
    if (role == Qt::DisplayRole)
    {
        QString userName = this->list.at(index.row())->getUsername();
        return QVariant::fromValue(userName);
    }

    return QVariant();
}


nlohmann::json QUserlist::toJSON(void) const
{
    nlohmann::json json = nlohmann::json::array();

    for (std::shared_ptr<QUser> userPtr : this->list)
    {
        json.push_back(userPtr->toJSON());
    }

    return json;
}

YAML::Node QUserlist::toYAML(void) const
{
    YAML::Node yaml;

    for (std::shared_ptr<QUser> userPtr : this->list)
    {
        yaml.push_back(userPtr->toYAML());
    }

    return yaml;
}

} /* namespace lanty */
