#ifndef SQLENGINE_H
#define SQLENGINE_H

#include <QObject>
#include <QDateTime>
#include <QTimeZone>

#include "engine.h"

class QSqlQuery;

namespace Cutelyst {
class Context;
}

namespace CMS {

class FileEnginePrivate;
class SqlEngine : public Engine
{
    Q_OBJECT
public:
    explicit SqlEngine(QObject *parent = 0);

    virtual bool init(const QHash<QString, QString> &settings) override;

    virtual Page *getPage(const QString &path, QObject *parent) override;

    virtual Page *getPageById(const QString &id, QObject *parent) override;

    virtual bool removePage(int id) override;

    /**
     * Returns the available pages,
     * when depth is -1 all pages are listed
     */
    virtual QList<Page *> listPages(QObject *parent,
                                    int offset,
                                    int limit) override;

    virtual QList<Page *> listPagesPublished(QObject *parent,
                                             int offset,
                                             int limit) override;

    virtual QList<Page *> listPosts(QObject *parent,
                                    int offset,
                                    int limit) override;

    virtual QList<Page *> listPostsPublished(QObject *parent,
                                             int offset,
                                             int limit) override;

    virtual QList<Page *> listAuthorPostsPublished(QObject *parent,
                                                   int authorId,
                                                   int offset,
                                                   int limit) override;

    virtual QHash<QString, QString> settings() const override;

    virtual QString settingsValue(const QString &key, const QString &defaultValue = QString()) const override;
    virtual bool setSettingsValue(Cutelyst::Context *c, const QString &key, const QString &value) override;

    virtual QList<Menu *> menus() override;

    virtual bool saveMenu(Cutelyst::Context *c, Menu *menu, bool replace) override;
    virtual bool removeMenu(Cutelyst::Context *c, const QString &name) override;

    virtual QHash<QString, Menu *> menuLocations() override;

    virtual bool settingsIsWritable() const override;

    QHash<QString, QString> loadSettings(Cutelyst::Context *c) override;

    virtual QDateTime lastModified() override;

    virtual QString addUser(Cutelyst::Context *c, const Cutelyst::ParamsMultiMap &user, bool replace) override;
    virtual bool removeUser(Cutelyst::Context *c, int id) override;
    virtual QVariantList users() override;
    virtual QHash<QString, QString> user(const QString &slug) override;
    virtual QHash<QString, QString> user(int id) override;

private:
    virtual int savePageBackend(Page *page) override;

    void loadMenus();
    void loadUsers();
    void configureView(Cutelyst::Context *c);
    void createDb();
    Page *createPageObj(const QSqlQuery &query, QObject *parent);

    QString m_theme;
    QVariantList m_users;
    QHash<QString, QHash<QString, QString> > m_usersSlug;
    QHash<int, QHash<QString, QString> > m_usersId;
    QHash<QString, QString> m_settings;
    QDateTime m_settingsDateTime;
    QTimeZone m_timezone;
    qint64 m_settingsDate = -1;
    QList<CMS::Menu *> m_menus;
    QHash<QString, CMS::Menu *> m_menuLocations;
};

}

#endif // SQLENGINE_H
