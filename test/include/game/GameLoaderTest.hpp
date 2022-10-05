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

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include "game/Game.hpp"
#include "game/GameClient.hpp"
#include "game/GameServer.hpp"
#include "game/GameVersion.hpp"

class GameLoaderTest : public ::testing::Test
{
protected:
    QString name = "Call of Duty 5";
    QString archive = "cod5.zip";

    lanty::GameClient client;
    lanty::GameServer server;
    lanty::GameVersion version;

    YAML::Node gameWithAllFields;
    YAML::Node gameWithNoFields;
    YAML::Node gameWithMissingFields;

    void SetUp(void) override
    {
        client = lanty::GameClient("bin/wow.exe", "+map fistlog", "+connect ?");
        server = lanty::GameServer("wow.exe", "+map azeroth");
        version.setVersion("1.1.0");
        version.setSource(lanty::GameVersion::Source::EXECUTABLE);

        gameWithAllFields[lanty::Game::NAME_SERIALIZER_KEY] = name.toStdString();
        gameWithAllFields[lanty::Game::ARCHIVE_SERIALIZER_KEY] = archive.toStdString();
        gameWithAllFields[lanty::Game::CLIENT_SERIALIZER_KEY] = client.toYAML();
        gameWithAllFields[lanty::Game::SERVER_SERIALIZER_KEY] = server.toYAML();
        gameWithAllFields[lanty::Game::VERSION_SERIALIZER_KEY] = version.toYAML();

        gameWithMissingFields[lanty::Game::NAME_SERIALIZER_KEY] = name.toStdString();
        gameWithMissingFields[lanty::Game::CLIENT_SERIALIZER_KEY] = client.toYAML();
        gameWithMissingFields[lanty::Game::VERSION_SERIALIZER_KEY] = version.toYAML();
        gameWithMissingFields[lanty::Game::ARCHIVE_SERIALIZER_KEY] = archive.toStdString();
    }
};
