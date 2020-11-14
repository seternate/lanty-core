/* Copyright <2020> <Levin Jeck>
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

#ifndef GAME_GAME_HPP
#define GAME_GAME_HPP

#include <core/ltycore_global.hpp>

#include <QObject>
#include <QPixmap>
#include <QString>

#include <game/GameVersionSource.hpp>
#include <game/IGame.hpp>
#include <yaml/IYamlNode.hpp>

namespace lanty
{

class LTYCORE_EXPORT Game : public IGame
{

    Q_OBJECT

private:
    void loadGameDataFromNode(const IYamlNode &gameNode);
    void loadVersionDataFromGameNode(const IYamlNode &versionNode);
    void loadClientDataFromGameNode(const IYamlNode &clientNode);
    void loadServerDataFromGameNode(const IYamlNode &serverNode);

public:
    Game(void);
    Game(const IYamlNode &yamlNode);
    virtual ~Game(void) = default;

    Game& operator=(const Game &game);
    bool operator==(const Game &game) const;
    bool operator!=(const Game &game) const;

    QString getName() const override;
    QString getArchiveAbsoluteFilePath() const override;
    QString getClientExecutableRelativeFilePath() const override;
    QString getClientArgument() const override;
    QString getClientConnectArgument() const override;
    QString getServerExecutableRelativeFilePath() const override;
    QString getServerArgument() const override;
    QString getVersion() const override;
    GameVersionSource getVersionSource() const override;
    QString getVersionRelativeFilePath() const override;
    QString getVersionFileQuery() const override;
    QPixmap getCoverImage() const override;
    QPixmap getIconImage() const override;

    bool isVersion() const override;

    bool canJoinServerWithCLI() const override;
    bool canOpenDedicatedServer() const override;
    bool canOpenServer() const override;

public slots:
    void setName(const QString &name) override;
    void setArchiveAbsoluteFilePath(const QString &archiveAbsoluteFilePath) override;
    void setClientExecutableRelativeFilePath(const QString &clientExecutableRelativeFilePath) override;
    void setClientArgument(const QString &clientArgument) override;
    void setClientConnectArgument(const QString &clientConnectArgument) override;
    void setServerExecutableRelativeFilePath(const QString &serverExecutableRelativeFilePath) override;
    void setServerArgument(const QString &serverArgument) override;
    void setVersion(const QString &version) override;
    void setVersionSource(const GameVersionSource &gameVersionSource) override;
    void setVersionRelativeFilePath(const QString &versionRelativeFilePath) override;
    void setVersionFileQuery(const QString &versionFileQuery) override;
    void setCoverImage(const QPixmap &coverImage) override;
    void setIconImage(const QPixmap &iconImage) override;

private:
    QString name;
    QString archiveAbsoluteFilePath;
    QString clientExecutableRelativeFilePath;
    QString clientArgument;
    QString clientConnectArgument;
    QString serverExecutableRelativeFilePath;
    QString serverArgument;
    QString version;
    GameVersionSource versionSource;
    QString versionRelativeFilePath;
    QString versionFileQuery;
    QPixmap coverImage;
    QPixmap iconImage;

};

} /* namespace lanty */

#endif /* GAME_GAME_HPP */
