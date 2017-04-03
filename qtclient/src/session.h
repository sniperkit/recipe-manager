#ifndef SESSION_H
#define SESSION_H

#include <QObject>

#include "jsondb.h"

struct SessionInfo {
    QString sessionID;
    QString sessionKey;
    QString chefID;
    QString chefName;
    QString chefEmail;
};

class Session : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString sessionID READ sessionID NOTIFY sessionChanged)
    Q_PROPERTY(QString sessionKey READ sessionKey NOTIFY sessionChanged)
    Q_PROPERTY(QString chefID READ userID NOTIFY sessionChanged)
    Q_PROPERTY(QString chefName READ userName NOTIFY sessionChanged)
    Q_PROPERTY(QString chefEmail READ userEmail NOTIFY sessionChanged)

public:
    explicit Session(QObject *parent = 0);

    QString sessionID() const {return m_sessionInfo.sessionID;}
    QString sessionKey() const {return m_sessionInfo.sessionKey;}
    QString chefID() const {return m_sessionInfo.chefID;}
    QString chefName() const {return m_sessionInfo.chefName;}
    QString chefEmail() const {return m_sessionInfo.chefEmail;}

private:
    JsonDB m_db;
    SessionInfo m_sessionInfo;

    bool getSessionFromObject(const QJsonObject &obj);

signals:
    void sessionChanged();

public slots:
};

#endif // SESSION_H