#include "networkmanager.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>
#include "config.h"
#include <QDebug>

//  #define BASE_URL "https://8b14e595-fe19-49fd-9640-d106c314eb26.mock.pstmn.io"   //  基础地址

// 单例实例指针初始化
NetworkManager* NetworkManager::m_instance = nullptr;

// 构造函数
NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent),
    m_networkManager(new QNetworkAccessManager(this)) // 创建网络访问管理器
{
}

// 单例访问方法
NetworkManager& NetworkManager::instance()
{
    if(!m_instance){
        m_instance = new NetworkManager();
    }
    return *m_instance;
}

// 发送登录请求方法
void NetworkManager::sendLoginRequest(const QString &usertype,
                                      const QString &username,
                                      const QString &password)
{
    QUrl url(QString("%1/login").arg(BASE_URL));  // 追加/login路径
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 构造JSON请求体
    QJsonObject json;
    json["user_type"] = usertype;
    json["username"] = username;
    json["password"] = password;

    // 发送POST请求
    QNetworkReply *reply = m_networkManager->post(
        request, QJsonDocument(json).toJson()
        );

    // 连接请求完成信号到处理函数
    connect(reply, &QNetworkReply::finished, [=](){
        handleLoginResponse(reply);
        reply->deleteLater();  // 处理完成后释放reply对象
    });
}

// 处理登录响应方法
void NetworkManager::handleLoginResponse(QNetworkReply *reply)
{
    bool success = false;
    QString message;
    QJsonObject data;

    if(reply->error() == QNetworkReply::NoError){  // 网络请求成功
        QByteArray response = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(response);
        QJsonObject obj = doc.object();

        // 解析服务器返回的JSON数据
        int code = obj.value("code").toInt();
        message = obj.value("message").toString();
        data = obj.value("data").toObject();

        success = (code == 200);  // 判断业务逻辑是否成功
    }else{
        message = reply->errorString();  // 获取网络错误信息
    }

    // 发射登录完成信号
    emit loginFinished(success, message, data);
}

// 上传单选题
void NetworkManager::sendAddSingleSelectRequest(const QString &question,
                                                const QStringList &options,
                                                int answer,
                                                const QString &subject,
                                                const QString &uploader)
{
    QUrl url(QString("%1/add_singleselect").arg(BASE_URL));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["question"] = question;
    json["options"] = QJsonArray::fromStringList(options);
    json["answer"] = answer;
    json["subject"] = subject;
    json["uploader"] = uploader;

    QNetworkReply *reply = m_networkManager->post(
        request, QJsonDocument(json).toJson()
        );

    // 30秒超时定时器
    QTimer *timeoutTimer = new QTimer(reply);
    timeoutTimer->setSingleShot(true);
    QObject::connect(timeoutTimer, &QTimer::timeout, [=]() {
        reply->abort();  // 中止请求
        reply->deleteLater();
        emit addSingleSelectFinished(false, "请求超时");
    });
    timeoutTimer->start(30000);  // 30秒超时

    connect(reply, &QNetworkReply::finished, [=](){
        timeoutTimer->stop();    // 请求完成时停止定时器
        handleAddSingleSelectResponse(reply);
        reply->deleteLater();
        timeoutTimer->deleteLater();
    });
}

// 上传多选题
void NetworkManager::sendAddMulSelectRequest(const QString &question,
                                                const QStringList &options,
                                                int answer,
                                                const QString &subject,
                                                const QString &uploader)
{
    QUrl url(QString("%1/add_mulselect").arg(BASE_URL));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["question"] = question;
    json["options"] = QJsonArray::fromStringList(options);
    json["answer"] = answer;
    json["subject"] = subject;
    json["uploader"] = uploader;

    QNetworkReply *reply = m_networkManager->post(
        request, QJsonDocument(json).toJson()
        );

    // 30秒超时定时器
    QTimer *timeoutTimer = new QTimer(reply);
    timeoutTimer->setSingleShot(true);
    QObject::connect(timeoutTimer, &QTimer::timeout, [=]() {
        reply->abort();  // 中止请求
        reply->deleteLater();
        emit addSingleSelectFinished(false, "请求超时");
    });
    timeoutTimer->start(30000);  // 30秒超时

    connect(reply, &QNetworkReply::finished, [=](){
        timeoutTimer->stop();    // 请求完成时停止定时器
        handleAddSingleSelectResponse(reply);
        reply->deleteLater();
        timeoutTimer->deleteLater();
    });
}

// 上传判断题
void NetworkManager::sendAddJudgeRequest(const QString &question,
                                                int answer,
                                                const QString &subject,
                                                const QString &uploader)
{
    QUrl url(QString("%1/add_judge").arg(BASE_URL));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["question"] = question;
    json["answer"] = answer;
    json["subject"] = subject;
    json["uploader"] = uploader;

    QNetworkReply *reply = m_networkManager->post(
        request, QJsonDocument(json).toJson()
        );

    // 30秒超时定时器
    QTimer *timeoutTimer = new QTimer(reply);
    timeoutTimer->setSingleShot(true);
    QObject::connect(timeoutTimer, &QTimer::timeout, [=]() {
        reply->abort();  // 中止请求
        reply->deleteLater();
        emit addSingleSelectFinished(false, "请求超时");
    });
    timeoutTimer->start(30000);  // 30秒超时

    connect(reply, &QNetworkReply::finished, [=](){
        timeoutTimer->stop();    // 请求完成时停止定时器
        handleAddSingleSelectResponse(reply);
        reply->deleteLater();
        timeoutTimer->deleteLater();
    });
}

// 上传简答题
void NetworkManager::sendAddShortAnswerRequest(const QString &question,
                                                const QString &answer,
                                                const QString &subject,
                                                const QString &uploader)
{
    QUrl url(QString("%1/add_shortanswer").arg(BASE_URL));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["question"] = question;
    json["answer"] = answer;
    json["subject"] = subject;
    json["uploader"] = uploader;

    QNetworkReply *reply = m_networkManager->post(
        request, QJsonDocument(json).toJson()
        );

    // 30秒超时定时器
    QTimer *timeoutTimer = new QTimer(reply);
    timeoutTimer->setSingleShot(true);
    QObject::connect(timeoutTimer, &QTimer::timeout, [=]() {
        reply->abort();  // 中止请求
        reply->deleteLater();
        emit addSingleSelectFinished(false, "请求超时");
    });
    timeoutTimer->start(30000);  // 30秒超时

    connect(reply, &QNetworkReply::finished, [=](){
        timeoutTimer->stop();    // 请求完成时停止定时器
        handleAddSingleSelectResponse(reply);
        reply->deleteLater();
        timeoutTimer->deleteLater();
    });
}

// 单选题响应，其他题也能用
void NetworkManager::handleAddSingleSelectResponse(QNetworkReply *reply)
{
    bool success = false;
    QString message;

    if(reply->error() == QNetworkReply::NoError){
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        int code = doc.object()["code"].toInt();
        message = doc.object()["message"].toString();
        success = (code == 200);
    } else {
        // 区分超时错误和其他网络错误
        message = reply->error() == QNetworkReply::OperationCanceledError ?
                      "请求超时" : reply->errorString();
    }

    emit addSingleSelectFinished(success, message);
}


// 发送题目查询请求
void NetworkManager::sendQueryRequest(const QString &content, const QString &uploader) {
    QUrl url(QString("%1/query_question").arg(BASE_URL));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["content"] = content;
    json["uploader"] = uploader;

    QNetworkReply *reply = m_networkManager->post(request, QJsonDocument(json).toJson());

    QTimer *timeoutTimer = new QTimer(reply);
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, [=]() {
        reply->abort();
        emit queryFinished(false, "请求超时", QJsonArray());
        reply->deleteLater();
    });
    timeoutTimer->start(30000);

    connect(reply, &QNetworkReply::finished, [=]() {
        timeoutTimer->stop();
        handleQueryResponse(reply);
        reply->deleteLater();
        timeoutTimer->deleteLater();
    });
}
// 处理查询响应
void NetworkManager::handleQueryResponse(QNetworkReply *reply) {
    bool success = false;
    QString message;
    QJsonArray questionList;

    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject obj = doc.object();
        int code = obj["code"].toInt();
        message = obj["message"].toString();

        if (code == 200) {
            success = true;
            questionList = obj["data"].toArray();
        }
    } else {
        message = reply->errorString();
    }

    emit queryFinished(success, message, questionList);
}


// 发送删除请求
void NetworkManager::sendDeleteRequest(const QString &id)
{
    QUrl url(QString("%1/delete_data").arg(BASE_URL));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["id"] = id;

    QNetworkReply *reply = m_networkManager->post(
        request, QJsonDocument(json).toJson()
        );

    // 30秒超时定时器
    QTimer *timeoutTimer = new QTimer(reply);
    timeoutTimer->setSingleShot(true);
    QObject::connect(timeoutTimer, &QTimer::timeout, [=]() {
        reply->abort();  // 中止请求
        reply->deleteLater();
        emit deleteFinished(false, "请求超时");
    });
    timeoutTimer->start(30000);  // 30秒超时

    connect(reply, &QNetworkReply::finished, [=](){
        timeoutTimer->stop();    // 请求完成时停止定时器
        handleDeleteResponse(reply);
        reply->deleteLater();
        timeoutTimer->deleteLater();
    });
}

void NetworkManager::handleDeleteResponse(QNetworkReply *reply)
{
    bool success = false;
    QString message;

    if(reply->error() == QNetworkReply::NoError){
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        int code = doc.object()["code"].toInt();
        message = doc.object()["message"].toString();
        success = (code == 200);
    } else {
        // 区分超时错误和其他网络错误
        message = reply->error() == QNetworkReply::OperationCanceledError ?
                      "请求超时" : reply->errorString();
    }

    emit deleteFinished(success, message);
}


// 修改单选题功能————获取指定单选题数据
void NetworkManager::sendSpecificSingleSelectRequest(const QString &id)
{
    QUrl url(QString("%1/specific_singlequestion").arg(BASE_URL));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["id"] = id;

    QNetworkReply *reply = m_networkManager->post(
        request, QJsonDocument(json).toJson()
        );

    QTimer *timeoutTimer = new QTimer(reply);
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, [=]() {
        reply->abort();
        emit specificSingleSelectReceived(false, "请求超时", "", {}, -1, "");
        reply->deleteLater();
    });
    timeoutTimer->start(30000);

    connect(reply, &QNetworkReply::finished, [=](){
        timeoutTimer->stop();
        handleSpecificSingleSelectResponse(reply);
        reply->deleteLater();
        timeoutTimer->deleteLater();
    });
}

// 修改多选题功能———获取指定多选题数据
// 其实应该把所有获取数据写在一个函数里再用type做分类选择的，但是我懒得重新整合了，就复制粘贴几份吧
void NetworkManager::sendSpecificMulSelectRequest(const QString &id)
{
    QUrl url(QString("%1/specific_mulquestion").arg(BASE_URL));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["id"] = id;

    QNetworkReply *reply = m_networkManager->post(
        request, QJsonDocument(json).toJson()
        );

    QTimer *timeoutTimer = new QTimer(reply);
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, [=]() {
        reply->abort();
        emit specificSingleSelectReceived(false, "请求超时", "", {}, -1, "");
        reply->deleteLater();
    });
    timeoutTimer->start(30000);

    connect(reply, &QNetworkReply::finished, [=](){
        timeoutTimer->stop();
        handleSpecificSingleSelectResponse(reply);
        reply->deleteLater();
        timeoutTimer->deleteLater();
    });
}

// 固定单选题的返回数据处理，多选题也可以用
void NetworkManager::handleSpecificSingleSelectResponse(QNetworkReply *reply)
{
    bool success = false;
    QString message, question, subject;
    QStringList options;
    int answer = -1;

    if(reply->error() == QNetworkReply::NoError){
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject obj = doc.object();
        int code = obj["code"].toInt();
        message = obj["message"].toString();

        if(code == 200){
            success = true;
            QJsonObject data = obj["data"].toObject();
            question = data["question"].toString();
            subject = data["subject"].toString();
            answer = data["answer"].toInt();

            QJsonArray optionsArray = data["options"].toArray();
            for(const auto& option : optionsArray){
                options << option.toString();
            }
        }
    } else {
        message = reply->errorString();
    }

    emit specificSingleSelectReceived(success, message, question, options, answer, subject);
}

// 修改单选题功能————上传指定单选题数据
void NetworkManager::sendchangeSingleSelectRequest(int ID,  // 修改问题需要指明问题ID
                                                const QString &question,
                                                const QStringList &options,
                                                int answer,
                                                const QString &subject,
                                                const QString &uploader)
{
    QUrl url(QString("%1/change_specific_singlequestion").arg(BASE_URL));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["ID"] = ID;
    json["question"] = question;
    json["options"] = QJsonArray::fromStringList(options);
    json["answer"] = answer;
    json["subject"] = subject;
    json["uploader"] = uploader;

    // qDebug() << "json构建完成";

    QNetworkReply *reply = m_networkManager->post(
        request, QJsonDocument(json).toJson()
        );

    // 30秒超时定时器
    QTimer *timeoutTimer = new QTimer(reply);
    timeoutTimer->setSingleShot(true);
    QObject::connect(timeoutTimer, &QTimer::timeout, [=]() {
        reply->abort();  // 中止请求
        reply->deleteLater();
        emit changeSingleSelectFinished(false, "请求超时");
    });
    timeoutTimer->start(30000);  // 30秒超时

    connect(reply, &QNetworkReply::finished, [=](){
        timeoutTimer->stop();    // 请求完成时停止定时器
        handlechangeSingleSelectResponse(reply);
        reply->deleteLater();
        timeoutTimer->deleteLater();
    });
}

// 修改多选题功能————上传指定多选题数据
void NetworkManager::sendchangeMulSelectRequest(int ID,  // 修改问题需要指明问题ID
                                                   const QString &question,
                                                   const QStringList &options,
                                                   int answer,
                                                   const QString &subject,
                                                   const QString &uploader)
{
    QUrl url(QString("%1/change_specific_mulquestion").arg(BASE_URL));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["ID"] = ID;
    json["question"] = question;
    json["options"] = QJsonArray::fromStringList(options);
    json["answer"] = answer;
    json["subject"] = subject;
    json["uploader"] = uploader;

    // qDebug() << "json构建完成";

    QNetworkReply *reply = m_networkManager->post(
        request, QJsonDocument(json).toJson()
        );

    // 30秒超时定时器
    QTimer *timeoutTimer = new QTimer(reply);
    timeoutTimer->setSingleShot(true);
    QObject::connect(timeoutTimer, &QTimer::timeout, [=]() {
        reply->abort();  // 中止请求
        reply->deleteLater();
        emit changeSingleSelectFinished(false, "请求超时");
    });
    timeoutTimer->start(30000);  // 30秒超时

    connect(reply, &QNetworkReply::finished, [=](){
        timeoutTimer->stop();    // 请求完成时停止定时器
        handlechangeSingleSelectResponse(reply);
        reply->deleteLater();
        timeoutTimer->deleteLater();
    });
}

// 单选题修改——上传的响应处理（其他题目也能用）
void NetworkManager::handlechangeSingleSelectResponse(QNetworkReply *reply)
{
    bool success = false;
    QString message;

    if(reply->error() == QNetworkReply::NoError){
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        int code = doc.object()["code"].toInt();
        message = doc.object()["message"].toString();
        success = (code == 200);
    } else {
        // 区分超时错误和其他网络错误
        message = reply->error() == QNetworkReply::OperationCanceledError ?
                      "请求超时" : reply->errorString();
    }

    emit changeSingleSelectFinished(success, message);
}


// 发送用户查询请求
void NetworkManager::senduserQueryRequest(const QString &content, const QString &type) {
    QUrl url(QString("%1/query_user").arg(BASE_URL));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["content"] = content;
    json["type"] = type;

    QNetworkReply *reply = m_networkManager->post(request, QJsonDocument(json).toJson());

    QTimer *timeoutTimer = new QTimer(reply);
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, [=]() {
        reply->abort();
        emit userqueryFinished(false, "请求超时", QJsonArray());
        reply->deleteLater();
    });
    timeoutTimer->start(30000);

    connect(reply, &QNetworkReply::finished, [=]() {
        timeoutTimer->stop();
        handleuserQueryResponse(reply);
        reply->deleteLater();
        timeoutTimer->deleteLater();
    });
}
// 处理用户查询响应
void NetworkManager::handleuserQueryResponse(QNetworkReply *reply) {
    bool success = false;
    QString message;
    QJsonArray userList;

    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject obj = doc.object();
        int code = obj["code"].toInt();
        message = obj["message"].toString();

        if (code == 200) {
            success = true;
            userList = obj["data"].toArray();
        }
    } else {
        message = reply->errorString();
    }

    emit userqueryFinished(success, message, userList);
}

// 用户删除功能实现
// 发送删除请求
void NetworkManager::senduserDeleteRequest(const QString &id)
{
    QUrl url(QString("%1/delete_user").arg(BASE_URL));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["id"] = id;

    QNetworkReply *reply = m_networkManager->post(
        request, QJsonDocument(json).toJson()
        );

    // 30秒超时定时器
    QTimer *timeoutTimer = new QTimer(reply);
    timeoutTimer->setSingleShot(true);
    QObject::connect(timeoutTimer, &QTimer::timeout, [=]() {
        reply->abort();  // 中止请求
        reply->deleteLater();
        emit userdeleteFinished(false, "请求超时");
    });
    timeoutTimer->start(30000);  // 30秒超时

    connect(reply, &QNetworkReply::finished, [=](){
        timeoutTimer->stop();    // 请求完成时停止定时器
        handleuserDeleteResponse(reply);
        reply->deleteLater();
        timeoutTimer->deleteLater();
    });
}

void NetworkManager::handleuserDeleteResponse(QNetworkReply *reply)
{
    bool success = false;
    QString message;

    if(reply->error() == QNetworkReply::NoError){
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        int code = doc.object()["code"].toInt();
        message = doc.object()["message"].toString();
        success = (code == 200);
    } else {
        // 区分超时错误和其他网络错误
        message = reply->error() == QNetworkReply::OperationCanceledError ?
                      "请求超时" : reply->errorString();
    }

    emit userdeleteFinished(success, message);
}

// 用户新增功能实现
// 发送新增请求
void NetworkManager::senduserAddRequest(const QString &name, const QString &type)
{
    QUrl url(QString("%1/add_user").arg(BASE_URL));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["name"] = name;
    json["type"] = type;

    QNetworkReply *reply = m_networkManager->post(
        request, QJsonDocument(json).toJson()
        );

    // 30秒超时定时器
    QTimer *timeoutTimer = new QTimer(reply);
    timeoutTimer->setSingleShot(true);
    QObject::connect(timeoutTimer, &QTimer::timeout, [=]() {
        reply->abort();  // 中止请求
        reply->deleteLater();
        emit userAddFinished(false, "请求超时");
    });
    timeoutTimer->start(30000);  // 30秒超时

    connect(reply, &QNetworkReply::finished, [=](){
        timeoutTimer->stop();    // 请求完成时停止定时器
        handleuserAddResponse(reply);
        reply->deleteLater();
        timeoutTimer->deleteLater();
    });
}

void NetworkManager::handleuserAddResponse(QNetworkReply *reply)
{
    bool success = false;
    QString message;

    if(reply->error() == QNetworkReply::NoError){
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        int code = doc.object()["code"].toInt();
        message = doc.object()["message"].toString();
        success = (code == 200);
    } else {
        // 区分超时错误和其他网络错误
        message = reply->error() == QNetworkReply::OperationCanceledError ?
                      "请求超时" : reply->errorString();
    }

    emit userAddFinished(success, message);
}

// 上传试卷
// 试卷上传功能
void NetworkManager::sendAddTestRequest(const QString &testName,
                                        const QString &uploader,
                                        const QJsonArray &questionIds)
{
    QUrl url(QString("%1/add_test").arg(BASE_URL));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["test_name"] = testName;
    json["uploader"] = uploader;
    json["question_ids"] = questionIds;

    QNetworkReply *reply = m_networkManager->post(
        request, QJsonDocument(json).toJson()
        );

    QTimer *timeoutTimer = new QTimer(reply);
    timeoutTimer->setSingleShot(true);
    disconnect(reply, &QNetworkReply::finished, nullptr, nullptr);
    connect(timeoutTimer, &QTimer::timeout, [=]() {
        reply->abort();
        emit addTestFinished(false, "请求超时");
        reply->deleteLater();
    });
    timeoutTimer->start(30000);

    connect(reply, &QNetworkReply::finished, [=](){
        timeoutTimer->stop();
        handleAddTestResponse(reply);
        reply->deleteLater();
        timeoutTimer->deleteLater();
    });
}

void NetworkManager::handleAddTestResponse(QNetworkReply *reply)
{
    bool success = false;
    QString message;

    if(reply->error() == QNetworkReply::NoError){
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        int code = doc.object()["code"].toInt();
        message = doc.object()["message"].toString();
        success = (code == 200);
    } else {
        message = reply->error() == QNetworkReply::OperationCanceledError ?
                      "请求超时" : reply->errorString();
    }

    emit addTestFinished(success, message);
}
