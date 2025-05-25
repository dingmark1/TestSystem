#include "userinfomanager.h"

UserInfoManager& UserInfoManager::instance()
{
    static UserInfoManager instance;
    return instance;
}

void UserInfoManager::setUsername(const QString &username)
{
    m_username = username;
}

QString UserInfoManager::username() const
{
    return m_username;
}
