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

#include "game/GameVersion.hpp"

class GameVersionLoaderTest : public ::testing::Test
{
protected:
    QString versionString = "1.13.20";
    lanty::GameVersion::Source source = lanty::GameVersion::Source::EXECUTABLE;
    QString filePath = "version.txt";
    QString fileQuery = "version=";

    YAML::Node gameversionYAMLWithAllFields;
    YAML::Node gameclientYAMLWithMissingFields;

    void SetUp(void) override
    {
        gameversionYAMLWithAllFields[lanty::GameVersion::VERSION_SERIALIZER_KEY] = versionString.toStdString();
        gameversionYAMLWithAllFields[lanty::GameVersion::SOURCE_SERIALIZER_KEY]
            = lanty::GameVersion::SourceToQString(source).toStdString();
        gameversionYAMLWithAllFields[lanty::GameVersion::FILEPATH_SERIALIZER_KEY] = filePath.toStdString();
        gameversionYAMLWithAllFields[lanty::GameVersion::FILEQUERY_SERIALIZER_KEY] = fileQuery.toStdString();

        gameclientYAMLWithMissingFields[lanty::GameVersion::VERSION_SERIALIZER_KEY] = versionString.toStdString();
        gameclientYAMLWithMissingFields[lanty::GameVersion::SOURCE_SERIALIZER_KEY]
            = lanty::GameVersion::SourceToQString(source).toStdString();
    }
};
