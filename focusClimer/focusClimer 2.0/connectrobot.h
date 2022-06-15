#ifndef CONNECTROBOT_H
#define CONNECTROBOT_H

#include "QFile"
#include "QString"
#include "QJsonDocument"
#include "QJsonParseError"
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include "QDebug"

class ConnectRobot {
public:

    ConnectRobot(QString SettingFile);
    // 获取IP地址和端口
    void GetServerIP_Port(QString &ip, quint16 &port);
    QString GetOptiTrackIP_Port();
    // 更新数据
    int RefreshSettingData();
private:
    // 数据
    QByteArray SettingData;
    // 文件路径
    QString SettingFilePath;

};

#endif // CONNECTROBOT_H
