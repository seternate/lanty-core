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

#include "game/GameServer.hpp"

namespace lanty
{

const std::string GameServer::EXECUTABLE_FILE_PATH_SERIALIZER_KEY = "executable";
const std::string GameServer::ARGUMENT_SERIALIZER_KEY = "argument";

GameServer::GameServer(const QString& filePath, const QString& argument) noexcept :
    executableFilePath(filePath),
    argument(argument)
{ }

GameServer::GameServer(const GameServer& gameserver) noexcept :
    executableFilePath(gameserver.getExecutableFilePath()),
    argument(gameserver.getArgument())
{ }


GameServer& GameServer::operator=(const GameServer& gameserver) noexcept
{
    this->setExecutableFilePath(gameserver.getExecutableFilePath());
    this->setArgument(gameserver.getArgument());
    return *this;
}

bool GameServer::operator==(const GameServer& gameserver) const noexcept
{
    return this->getExecutableFilePath() == gameserver.getExecutableFilePath()
           && this->getArgument() == gameserver.getArgument();
}

bool GameServer::operator!=(const GameServer& gameserver) const noexcept
{
    return !(*this == gameserver);
}


const QString& GameServer::getExecutableFilePath(void) const noexcept
{
    return this->executableFilePath;
}

const QString& GameServer::getArgument(void) const noexcept
{
    return this->argument;
}


void GameServer::setExecutableFilePath(const QString& filePath) noexcept
{
    this->executableFilePath = filePath;
}

void GameServer::setArgument(const QString& argument) noexcept
{
    this->argument = argument;
}


bool GameServer::canOpenDedicatedServer(void) const noexcept
{
    return this->executableFilePath.isEmpty() == false;
}

bool GameServer::canOpenServer(void) const noexcept
{
    return this->canOpenDedicatedServer() == true || this->argument.isEmpty() == false;
}


nlohmann::json GameServer::toJSON(void) const
{
    nlohmann::json json = nlohmann::json::object();

    if (this->getExecutableFilePath().isEmpty() == false)
    {
        json[GameServer::EXECUTABLE_FILE_PATH_SERIALIZER_KEY] = this->getExecutableFilePath().toStdString();
    }
    if (this->getArgument().isEmpty() == false)
    {
        json[GameServer::ARGUMENT_SERIALIZER_KEY] = this->getArgument().toStdString();
    }

    return json;
}

} /* namespace lanty */
