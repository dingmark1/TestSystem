#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>

// 网络管理类（单例模式）
class NetworkManager : public QObject
{
    Q_OBJECT
public:
    static NetworkManager& instance();  // 单例访问方法

    // 发送登录请求接口
    void sendLoginRequest(const QString &usertype,
                          const QString &username,
                          const QString &password);

    // 上传单选题
    void sendAddSingleSelectRequest(const QString &question,
                                    const QStringList &options,
                                    int answer,
                                    const QString &subject,
                                    const QString &uploader);
    // 上传多选题
    void sendAddMulSelectRequest(const QString &question,
                                    const QStringList &options,
                                    int answer,
                                    const QString &subject,
                                    const QString &uploader);

    // 上传判断题
    void sendAddJudgeRequest(const QString &question,
                                    int answer,
                                    const QString &subject,
                                    const QString &uploader);

    // 上传简答题
    void sendAddShortAnswerRequest(const QString &question,
                                    const QString &answer,
                                    const QString &subject,
                                    const QString &uploader);

    // 题目查询
    void sendQueryRequest(const QString &content, const QString &uploader);

    // 题目删除
    void sendDeleteRequest(const QString &id);

    // 修改————获取单选题数据
    void sendSpecificSingleSelectRequest(const QString &id);

    // 修改————获取多选题数据
    void sendSpecificMulSelectRequest(const QString &id);

    // 修改————获取判断题数据
    void sendSpecificJudgeRequest(const QString &id);

    // 修改————获取简答题数据
    void sendSpecificShortRequest(const QString &id);

    // 修改————上传单选题
    void sendchangeSingleSelectRequest(int ID,
                                    const QString &question,
                                    const QStringList &options,
                                    int answer,
                                    const QString &subject,
                                    const QString &uploader);

    // 修改————上传多选题
    void sendchangeMulSelectRequest(int ID,
                                    const QString &question,
                                    const QStringList &options,
                                    int answer,
                                    const QString &subject,
                                    const QString &uploader);

    // 修改————上传判断题
    void sendchangeJudgeRequest(int ID,
                                    const QString &question,
                                    int answer,
                                    const QString &subject,
                                    const QString &uploader);

    // 修改————上传简答题
    void sendchangeShortRequest(int ID,
                                const QString &question,
                                const QString &answer,
                                const QString &subject,
                                const QString &uploader);


    // 用户查询
    void senduserQueryRequest(const QString &content, const QString &type);

    // 用户删除
    void senduserDeleteRequest(const QString &id);

    // 用户新增
    void senduserAddRequest(const QString &name, const QString &type, const QString &code);

    // 上传试卷
    void sendAddTestRequest(const QString &testName,
                            const QString &uploader,
                            const QJsonArray &questionIds);

    // 请求AI
    void sendAIRequest(const QString &prompt, const QString &questionType);



signals:
    // 登录完成信号
    void loginFinished(bool success,
                       const QString &message,
                       const QJsonObject &data);

    // 单选题上传完成信号(其他题也能用)
    void addSingleSelectFinished(bool success, const QString &message);

    // 题目查询
    void queryFinished(bool success, const QString &message, const QJsonArray &questionList);

    // 题目删除完成信号
    void deleteFinished(bool success, const QString &message);

    // 获取指定单选题目数据完成信号，其他题型也可以用，只不过要注意部分参数使无用的
    void specificSingleSelectReceived(bool success, const QString &message,
                                      const QString &question,
                                      const QStringList &options,
                                      int answer,
                                      const QString &subject);

    // 修改————上传单选题数据的完成信号，其实也没用，直接用addSingleSelectFinished信号就行
    // 不过为了格式统一，后续的所有类型题目的修改功能的上传完成信号就都用这个了
    void changeSingleSelectFinished(bool success, const QString &message);

    // 用户查询完成信号
    void userqueryFinished(bool success, const QString &message, const QJsonArray &questionList);

    // 用户删除完成信号
    void userdeleteFinished(bool success, const QString &message);

    // 用户新增完成信号
    void userAddFinished(bool success, const QString &message);

    // 上传试卷
    void addTestFinished(bool success, const QString &message);

    // AI生成单选题目完成信号
    void aiRequestFinished_single(bool success, const QString &message,
                           const QString &question,
                           const QStringList &options,
                           int answer);


private:
    explicit NetworkManager(QObject *parent = nullptr);
    void handleLoginResponse(QNetworkReply *reply);  // 处理登录响应

    void handleAddSingleSelectResponse(QNetworkReply *reply);   //处理上传单选题的响应（其他的题型也一样用）

    void handleQueryResponse(QNetworkReply *reply); // 处理题目查询
    void handleDeleteResponse(QNetworkReply *reply);// 处理题目删除

    void handleSpecificSingleSelectResponse(QNetworkReply *reply);  // 处理单选题/多选题数据响应
    void handleSpecificJudgeResponse(QNetworkReply *reply);  // 处理判断题数据响应
    void handleSpecificShortResponse(QNetworkReply *reply);  // 处理简答题数据响应

    void handlechangeSingleSelectResponse(QNetworkReply *reply);//处理修改后上传单选题的响应,其实多余了，可以直接用上传题目的响应的

    void handleuserQueryResponse(QNetworkReply *reply); // 处理用户查询
    void handleuserDeleteResponse(QNetworkReply *reply);// 处理用户删除
    void handleuserAddResponse(QNetworkReply *reply);// 处理用户删除

    void handleAddTestResponse(QNetworkReply *reply);// 处理试卷上传

    void handleAIResponse_single(QNetworkReply *reply);// AI请求——单选题

    static NetworkManager* m_instance;  // 单例实例指针
    QNetworkAccessManager *m_networkManager;  // 网络访问管理器实例
};

#endif // NETWORKMANAGER_H
