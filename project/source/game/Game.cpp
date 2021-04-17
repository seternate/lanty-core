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

#include "game/Game.hpp"

namespace lanty
{

const std::string Game::NAME_SERIALIZER_KEY = "name";
const std::string Game::ARCHIVE_SERIALIZER_KEY = "archive";
const std::string Game::VERSION_SERIALIZER_KEY = "version";
const std::string Game::CLIENT_SERIALIZER_KEY = "client";
const std::string Game::SERVER_SERIALIZER_KEY = "server";

Game::Game(const QString& name,
           const QString& archiveFilePath,
           const GameClient& client,
           const GameServer& server,
           const GameVersion& version) noexcept :
    Serializable(),
    name(name),
    archiveFileName(archiveFilePath),
    client(client),
    server(server),
    version(version),
    cover(),
    icon()
{ }

Game::Game(const Game& game) noexcept :
    name(game.getName()),
    archiveFileName(game.getArchiveFileName()),
    client(game.client),
    server(game.server),
    version(game.version),
    cover(game.getCover()),
    icon(game.getIcon())
{ }


Game& Game::operator=(const Game& game) noexcept
{
    this->setName(game.getName());
    this->client = game.client;
    this->server = game.server;
    this->version = game.version;
    this->setCover(game.getCover());
    this->setIcon(game.getIcon());
    return *this;
}

bool Game::operator==(const Game& game) const noexcept
{

    return this->getName() == game.getName() && this->getArchiveFileName() == game.getArchiveFileName()
           && this->client == game.client && this->server == game.server && this->version == game.version
           && this->getCover().toImage() == game.getCover().toImage()
           && this->getIcon().toImage() == game.getCover().toImage();
}

bool Game::operator!=(const Game& game) const noexcept
{
    return !(*this == game);
}


const QString& Game::getName(void) const noexcept
{
    return this->name;
}

const QString& Game::getArchiveFileName(void) const noexcept
{
    return this->archiveFileName;
}

const GameClient& Game::getClient(void) const noexcept
{
    return this->client;
}

const GameServer& Game::getServer(void) const noexcept
{
    return this->server;
}

const GameVersion& Game::getVersion(void) const noexcept
{
    return this->version;
}

const QPixmap& Game::getCover(void) const noexcept
{
    return this->cover;
}

const QPixmap& Game::getIcon(void) const noexcept
{
    return this->icon;
}


void Game::setName(const QString& name) noexcept
{
    this->name = name;
}

void Game::setArchiveFileName(const QString& archiveFileName) noexcept
{
    this->archiveFileName = archiveFileName;
}

void Game::setClientExecutableFilePath(const QString& clientExecutableFilePath) noexcept
{
    this->client.setExecutableFilePath(clientExecutableFilePath);
}

void Game::setClientArgument(const QString& clientArgument) noexcept
{
    this->client.setArgument(clientArgument);
}

void Game::setClientConnectArgument(const QString& clientConnectArgument) noexcept
{
    this->client.setConnectArgument(clientConnectArgument);
}

void Game::setServerExecutableFilePath(const QString& serverExecutableFilePath) noexcept
{
    this->server.setExecutableFilePath(serverExecutableFilePath);
}

void Game::setServerArgument(const QString& serverArgument) noexcept
{
    this->server.setArgument(serverArgument);
}

void Game::setVersion(const QString& version) noexcept
{
    this->version.setVersion(version);
}

void Game::setVersionSource(const GameVersion::Source versionSource) noexcept
{
    this->version.setSource(versionSource);
}

void Game::setVersionFilePath(const QString& versionFilePath) noexcept
{
    this->version.setFilePath(versionFilePath);
}

void Game::setVersionFileQuery(const QString& versionFileQuery) noexcept
{
    this->version.setFileQuery(versionFileQuery);
}

void Game::setCover(const QPixmap& cover) noexcept
{
    this->cover = cover;
}

void Game::setIcon(const QPixmap& icon) noexcept
{
    this->icon = icon;
}

nlohmann::json Game::toJSON(void) const
{
    nlohmann::json json = nlohmann::json::object();

    if (this->getName().isEmpty() == false)
    {
        json["name"] = this->getName().toStdString();
    }
    if (this->getArchiveFileName().isEmpty() == false)
    {
        json["archive"] = this->getArchiveFileName().toStdString();
    }

    nlohmann::json version = this->getVersion().toJSON();
    if (version.empty() == false)
    {
        json["version"] = version;
    }

    nlohmann::json client = this->getClient().toJSON();
    if (client.empty() == false)
    {
        json["client"] = client;
    }

    nlohmann::json server = this->getServer().toJSON();
    if (server.empty() == false)
    {
        json["server"] = server;
    }

    return json;
}

YAML::Node Game::toYAML(void) const
{
    YAML::Node yaml;

    if (this->getName().isEmpty() == false)
    {
        yaml["name"] = this->getName().toStdString();
    }
    if (this->getArchiveFileName().isEmpty() == false)
    {
        yaml["archive"] = this->getArchiveFileName().toStdString();
    }

    YAML::Node version = this->getVersion().toYAML();
    if (version.IsNull() == false)
    {
        yaml["version"] = version;
    }

    YAML::Node client = this->getClient().toYAML();
    if (client.IsNull() == false)
    {
        yaml["client"] = client;
    }

    YAML::Node server = this->getServer().toYAML();
    if (server.IsNull() == false)
    {
        yaml["server"] = server;
    }

    return yaml;
}


} /* namespace lanty */
