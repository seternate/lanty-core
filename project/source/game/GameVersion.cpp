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

#include "game/GameVersion.hpp"

namespace lanty
{

const std::string GameVersion::VERSION_SERIALIZER_KEY = "info";
const std::string GameVersion::SOURCE_SERIALIZER_KEY = "format";
const std::string GameVersion::FILEPATH_SERIALIZER_KEY = "file";
const std::string GameVersion::FILEQUERY_SERIALIZER_KEY = "query";

const QVector<QString> GameVersion::sourceQString({ QString("EXECUTABLE"), QString("FILE"), QString("NONE") });


QString GameVersion::SourceToQString(GameVersion::Source source)
{
    return GameVersion::sourceQString.at(static_cast<quint32>(source));
}

GameVersion::Source GameVersion::QStringToSource(const QString& source)
{
    qint32 sourceIndex = GameVersion::sourceQString.indexOf(source);
    GameVersion::Source sourceEnum = GameVersion::Source::NONE;

    if (sourceIndex != -1)
    {
        sourceEnum = static_cast<GameVersion::Source>(sourceIndex);
    }

    return sourceEnum;
}


GameVersion::GameVersion(void) noexcept :
    version(""),
    source(GameVersion::Source::NONE),
    filePath(""),
    fileQuery("") { }

GameVersion::GameVersion(const lanty::GameVersion& gameversion) noexcept :
    version(gameversion.getVersion()),
    source(gameversion.getSource()),
    filePath(gameversion.getFilePath()),
    fileQuery(gameversion.getFileQuery())
{ }

GameVersion::GameVersion(GameVersion&& gameversion) noexcept :
    version(std::move(gameversion.version)),
    source(std::move(gameversion.source)),
    filePath(std::move(gameversion.filePath)),
    fileQuery(std::move(gameversion.fileQuery))
{ }


GameVersion& GameVersion::operator=(const GameVersion& gameversion) noexcept
{
    this->setVersion(gameversion.getVersion());
    this->setSource(gameversion.getSource());
    this->setFilePath(gameversion.getFilePath());
    this->setFileQuery(gameversion.getFileQuery());
    return *this;
}

GameVersion& GameVersion::operator=(GameVersion&& gameversion) noexcept
{
    this->version = std::move(gameversion.version);
    this->source = std::move(gameversion.source);
    this->filePath = std::move(gameversion.filePath);
    this->fileQuery = std::move(gameversion.fileQuery);
    return *this;
}

bool GameVersion::operator==(const GameVersion& gameversion) const noexcept
{
    return this->getVersion() == gameversion.getVersion() && this->getSource() == gameversion.getSource()
           && this->getFilePath() == gameversion.getFilePath() && this->getFileQuery() == gameversion.getFileQuery();
}

bool GameVersion::operator!=(const GameVersion& gameversion) const noexcept
{
    return !(*this == gameversion);
}


const QString& GameVersion::getVersion(void) const noexcept
{
    return this->version;
}

GameVersion::Source GameVersion::getSource(void) const noexcept
{
    return this->source;
}

const QString& GameVersion::getFilePath(void) const noexcept
{
    return this->filePath;
}

const QString& GameVersion::getFileQuery(void) const noexcept
{
    return this->fileQuery;
}


void GameVersion::setVersion(const QString& version) noexcept
{
    this->version = version;
}

void GameVersion::setSource(const GameVersion::Source source) noexcept
{
    this->source = source;
}

void GameVersion::setFilePath(const QString& filepath) noexcept
{
    this->filePath = filepath;
}

void GameVersion::setFileQuery(const QString& query) noexcept
{
    this->fileQuery = query;
}


bool GameVersion::isVersion(void) const noexcept
{
    return this->version.isEmpty() == false && this->source != GameVersion::Source::NONE;
}


nlohmann::json GameVersion::toJSON(void) const
{
    nlohmann::json json = nlohmann::json::object();

    if (this->getVersion().isEmpty() == false)
    {
        if (this->source != GameVersion::Source::NONE)
        {
            json[GameVersion::VERSION_SERIALIZER_KEY] = this->getVersion().toStdString();
            json[GameVersion::SOURCE_SERIALIZER_KEY] = GameVersion::SourceToQString(this->source).toStdString();
        }
        if (this->getFilePath().isEmpty() == false && this->source == GameVersion::Source::FILE)
        {
            json[GameVersion::FILEPATH_SERIALIZER_KEY] = this->getFilePath().toStdString();

            if (this->getFileQuery().isEmpty() == false)
            {
                json[GameVersion::FILEQUERY_SERIALIZER_KEY] = this->getFileQuery().toStdString();
            }
        }
    }

    return json;
}

YAML::Node GameVersion::toYAML(void) const
{
    YAML::Node yaml;

    if (this->getVersion().isEmpty() == false)
    {
        if (this->source != GameVersion::Source::NONE)
        {
            yaml[GameVersion::VERSION_SERIALIZER_KEY] = this->getVersion().toStdString();
            yaml[GameVersion::SOURCE_SERIALIZER_KEY] = GameVersion::SourceToQString(this->source).toStdString();
        }
        if (this->getFilePath().isEmpty() == false && this->source == GameVersion::Source::FILE)
        {
            yaml[GameVersion::FILEPATH_SERIALIZER_KEY] = this->getFilePath().toStdString();

            if (this->getFileQuery().isEmpty() == false)
            {
                yaml[GameVersion::FILEQUERY_SERIALIZER_KEY] = this->getFileQuery().toStdString();
            }
        }
    }

    return yaml;
}

} /* namespace lanty */
