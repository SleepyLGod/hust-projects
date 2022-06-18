#include "connectrobot.h"
#include <QDir>

// 客户端的通信界面
ConnectRobot::ConnectRobot(QString SettingFile) {
    qDebug() <<SettingFile;
    QString path = QDir::currentPath();
    qDebug() <<path;
//     path.replace("/","\");
    QString filename =path+"/setting.json";
    filename.replace("/","\\");
    qDebug() <<filename;
    QFile file(filename);
    QFile loadFile(filename);

    if (loadFile.isReadable()) {
        qDebug() << "can be read";
    }

    if (!loadFile.open(QIODevice::ReadWrite)) {
        qDebug() << "could't open SettingFilePath";
        return;
    }  // 或者用isOk函数表示

    // 读入剩余所有数据
    SettingData = loadFile.readAll();  
    loadFile.close();

    // 保存文件路径
    SettingFilePath=SettingFile;
}

int ConnectRobot::RefreshSettingData() {
    QFile loadFile(SettingFilePath);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qDebug() <<  "could't open SettingFilePath""
        return 0;
    }
    SettingData = loadFile.readAll();
    loadFile.close();
    return 1;
}

/**
 * @brief 获取服务器IP和端口号
 * @param ip
 * @param port
 */
void ConnectRobot::GetServerIP_Port(QString &ip, quint16 &port) {
    QJsonParseError json_error;
    // 解析为UTF-8编码的JSON文档，并从中创建QJsonDocument
    QJsonDocument jsonDoc(QJsonDocument::fromJson(SettingData, &json_error)); 

    if (json_error.error != QJsonParseError::NoError) {
        qDebug() <<  "json error!""
        return;
    }

    QJsonObject rootObj = jsonDoc.object();

    QStringList keys = rootObj.keys();
    if(rootObj.contains("TcpToRobot")) {
        QJsonObject subObj = rootObj.value( "TcpToRobot").toObject())
        ip = subObj[ "IP"].toString())
        port = subObj[ "Port"].toString().toUShort())
        qDebug() << port;
        qDebug() <<  "Server IP is:" << ipp
        qDebug() <<  "Server Port is:" << portt
        return;
    } else {
        qDebug() <<  "No TcpToRobot settings!""
        return;
    }
}


QString ConnectRobot::GetOptiTrackIP_Port() {
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(SettingData, &json_error));

    if (json_error.error != QJsonParseError::NoError) {
        qDebug() <<  "json error!""
        return  """
    }

    QJsonObject rootObj = jsonDoc.object();

    QStringList keys = rootObj.keys();
    if (rootObj.contains("OptiTrack")) {
        QJsonObject subObj = rootObj.value( "OptiTrack").toObject())
        return subObj[ "IP"].toString()+":"+subObj["Port"].toString())
    } else {
        qDebug() <<  "No Optitrack settings!""
        return  """
    }
}
