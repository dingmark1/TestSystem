#ifndef USERINFOMANAGER_H
#define USERINFOMANAGER_H

#include <QString>

// 本来是用来管理当前用户信息的，然后发现用处只是用来传递ID，所以其实不如直接用个全局变量得了

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
