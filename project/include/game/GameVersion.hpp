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

#include <QString>
#include <QVector>
#include <string>

#include "core/Serializable.hpp"
#include "core/ltycore_global.hpp"

namespace lanty
{

class LTYCORE_EXPORT GameVersion : public Serializable
{
public:
    enum class Source : quint32
    {
        EXECUTABLE = 0x00,
        FILE = 0x01,
        NONE = 0x02
    };

    static const std::string VERSION_SERIALIZER_KEY;
    static const std::string SOURCE_SERIALIZER_KEY;
    static const std::string FILEPATH_SERIALIZER_KEY;
    static const std::string FILEQUERY_SERIALIZER_KEY;

    static QString SourceToQString(GameVersion::Source source);
    static GameVersion::Source QStringToSource(const QString& source);

    GameVersion(void) noexcept;
    GameVersion(const GameVersion& gameversion) noexcept;
    GameVersion(GameVersion&& gameversion) = delete;
    virtual ~GameVersion(void) = default;

    GameVersion& operator=(const GameVersion& gameversion) noexcept;
    GameVersion& operator=(GameVersion&& gameversion) = delete;
    bool operator==(const GameVersion& gameversion) const noexcept;
    bool operator!=(const GameVersion& gameversion) const noexcept;

    const QString& getVersion(void) const noexcept;
    GameVersion::Source getSource(void) const noexcept;
    const QString& getFilePath(void) const noexcept;
    const QString& getFileQuery(void) const noexcept;

    void setVersion(const QString& version) noexcept;
    void setSource(const GameVersion::Source source) noexcept;
    void setFilePath(const QString& filepath) noexcept;
    void setFileQuery(const QString& query) noexcept;

    bool isVersion(void) const noexcept;

    nlohmann::json toJSON(void) const override;

private:
    static const QVector<QString> sourceQString;

    QString version;
    GameVersion::Source source;
    QString filePath;
    QString fileQuery;
};

} /* namespace lanty */
