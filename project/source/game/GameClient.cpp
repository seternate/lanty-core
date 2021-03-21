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

#include "game/GameClient.hpp"

namespace lanty
{

const std::string GameClient::EXECUTABLE_FILE_PATH_SERIALIZER_KEY = "executable";
const std::string GameClient::CONNECT_ARGUMENT_SERIALIZER_KEY = "connect";
const std::string GameClient::ARGUMENT_SERIALIZER_KEY = "argument";

GameClient::GameClient(const QString& filePath, const QString& connectArgument, const QString& argument) noexcept :
    executableFilePath(filePath),
    connectArgument(connectArgument),
    argument(argument)
{ }

GameClient::GameClient(const GameClient& gameclient) noexcept :
    executableFilePath(gameclient.getExecutableFilePath()),
    connectArgument(gameclient.getConnectArgument()),
    argument(gameclient.getArgument())
{ }


GameClient& GameClient::operator=(const GameClient& gameclient) noexcept
{
    this->setExecutableFilePath(gameclient.getExecutableFilePath());
    this->setConnectArgument(gameclient.getConnectArgument());
    this->setArgument(gameclient.getArgument());
    return *this;
}

bool GameClient::operator==(const GameClient& gameclient) const noexcept
{
    return this->getExecutableFilePath() == gameclient.getExecutableFilePath()
           && this->getConnectArgument() == gameclient.getConnectArgument()
           && this->getArgument() == gameclient.getArgument();
}

bool GameClient::operator!=(const GameClient& gameclient) const noexcept
{
    return !(*this == gameclient);
}


const QString& GameClient::getExecutableFilePath(void) const noexcept
{
    return this->executableFilePath;
}

const QString& GameClient::getConnectArgument(void) const noexcept
{
    return this->connectArgument;
}

const QString& GameClient::getArgument(void) const noexcept
{
    return this->argument;
}


void GameClient::setExecutableFilePath(const QString& filePath) noexcept
{
    this->executableFilePath = filePath;
}

void GameClient::setConnectArgument(const QString& connectArgument) noexcept
{
    this->connectArgument = connectArgument;
}

void GameClient::setArgument(const QString& argument) noexcept
{
    this->argument = argument;
}


bool GameClient::canJoinServerWithCLI(void) const noexcept
{
    return this->connectArgument.isEmpty() == false;
}


nlohmann::json GameClient::toJSON(void) const
{
    nlohmann::json json = nlohmann::json::object();

    if (this->getExecutableFilePath().isEmpty() == false)
    {
        json[GameClient::EXECUTABLE_FILE_PATH_SERIALIZER_KEY] = this->getExecutableFilePath().toStdString();
    }
    if (this->getArgument().isEmpty() == false)
    {
        json[GameClient::ARGUMENT_SERIALIZER_KEY] = this->getArgument().toStdString();
    }
    if (this->getConnectArgument().isEmpty() == false)
    {
        json[GameClient::CONNECT_ARGUMENT_SERIALIZER_KEY] = this->getConnectArgument().toStdString();
    }

    return json;
}

} /* namespace lanty */
