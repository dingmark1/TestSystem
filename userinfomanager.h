#ifndef USERINFOMANAGER_H
#define USERINFOMANAGER_H

#include <QString>

class UserInfoManager
{
public:
    static UserInfoManager& instance();

    void setUsername(const QString &username);
    QString username() const;

private:
    UserInfoManager() = default;
    ~UserInfoManager() = default;

    QString m_username;
};

#endif // USERINFOMANAGER_H
