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

#include "user/User.hpp"

class UserLoaderTest : public ::testing::Test
{
protected:
    QString username = "seternate";
    QString gamepath = "C:/games";
    quint64 resolutionX = 1920;
    quint64 resolutionY = 1080;
    QString ipAddress = "192.168.0.86";

    YAML::Node userYAMLWithAllFields;
    YAML::Node userYAMLWithMissingIPAddress;
    YAML::Node userYAMLWithOnlyUsername;

    void SetUp(void) override
    {
        userYAMLWithAllFields[lanty::User::USERNAME_SERIALIZER_KEY] = username.toStdString();
        userYAMLWithAllFields[lanty::User::GAMEPATH_SERIALIZER_KEY] = gamepath.toStdString();
        userYAMLWithAllFields[lanty::User::RESOLUTION_SERIALIZER_KEY][lanty::User::RESOLUTION_X_SERIALIZER_KEY] = resolutionX;
        userYAMLWithAllFields[lanty::User::RESOLUTION_SERIALIZER_KEY][lanty::User::RESOLUTION_Y_SERIALIZER_KEY] = resolutionY;
        userYAMLWithAllFields[lanty::User::IPADDRESS_SERIALIZER_KEY] = ipAddress.toStdString();

        userYAMLWithMissingIPAddress[lanty::User::USERNAME_SERIALIZER_KEY] = username.toStdString();
        userYAMLWithMissingIPAddress[lanty::User::GAMEPATH_SERIALIZER_KEY] = gamepath.toStdString();
        userYAMLWithMissingIPAddress[lanty::User::RESOLUTION_SERIALIZER_KEY][lanty::User::RESOLUTION_X_SERIALIZER_KEY]
            = resolutionX;
        userYAMLWithMissingIPAddress[lanty::User::RESOLUTION_SERIALIZER_KEY][lanty::User::RESOLUTION_Y_SERIALIZER_KEY]
            = resolutionY;

        userYAMLWithOnlyUsername[lanty::User::USERNAME_SERIALIZER_KEY] = username.toStdString();
    }
};
