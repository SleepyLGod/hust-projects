#include "dobotmodel.h"
#include <QDir>
#include "ClimbotWin.h"
#define PI (3.1415926535897932346f)
using namespace std;

DobotModel::DobotModel(Qt3DCore::QNode *parent) : Qt3DCore::QEntity(parent) {
    currentAngles = QVector3D();
    currentPositions = QVector3D(0.0f, 0.0f, 0.0f);
    originalPositions = QVector3D(0.0f, 0.0f, 0.0f);

    // 材质组件（Material）
    // 叶片材质
    Qt3DExtras::QDiffuseSpecularMaterial *bladeMaterial = new Qt3DExtras::QDiffuseSpecularMaterial;
    bladeMaterial->setDiffuse(QColor(142, 181, 206));
    // 机器人材质
    Qt3DExtras::QDiffuseSpecularMaterial *robotMaterial = new Qt3DExtras::QDiffuseSpecularMaterial;
    robotMaterial->setDiffuse(QColor(179,219,159));// 绿
    // robotMaterial->setDiffuse(QColor(204,93,93));// 红

    // 爬壁机器人模型
    Qt3DCore::QEntity *robotEntity = new Qt3DCore::QEntity(this);
    Qt3DRender::QMesh *robotMesh = new Qt3DRender::QMesh;
    robotTransform = new Qt3DCore::QTransform;
    robotTransform->setScale(4.0f);
    robotTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 0.0f), 0.0f));
    robotTransform->setTranslation(QVector3D(0.0f,0.0f, 0.0f));
    //     // 实现初始化模型旋转
    //     /**
    //      * @brief rotation_matrix
    //      * 首先确定旋转矩阵 rotation_matrix
    //      * 根据自己要求算出矩阵（绕自身系轴转，则先转矩阵居左；绕世界系转，则先转矩阵居右）
    //      * 根据旋转矩阵转轴-角 即旋转向量
    //      */
    //     Eigen::Matrix3d rotation_matrix;
    //     // 算出矩阵
    //     rotation_matrix << 0 ,-0.7071067,0.7071067,
    //                        0 , 0.7071067,0.7071067,
    //                        -1,         0,        0;
    //     // 转化为旋转向量
    //     Eigen::AngleAxisd rotation_vector;
    //     rotation_vector.fromRotationMatrix(rotation_matrix);
    //     float vector_angle = rotation_vector.angle()*(180.00/M_PI);
    //     float vector_x=rotation_vector.axis().transpose().x();
    //     float vector_y=rotation_vector.axis().transpose().y();
    //     float vector_z=rotation_vector.axis().transpose().z();
    //     // 绕向量旋转，拇指方向为轴向为向量方向，旋转方向为右手螺旋定则确定
    //     robotTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(vector_x,vector_y,vector_z),vector_angle));
    // 导入obj
    robotMesh->setSource(QUrl(QStringLiteral("qrc:/model/robot.obj")));
    // 最终结合
    robotEntity->addComponent(robotMesh);
    robotEntity->addComponent(robotMaterial);
    robotEntity->addComponent(robotTransform);

    // 风机叶片模型
    Qt3DRender::QMesh *BladeMesh =new Qt3DRender::QMesh;
    BladeMesh->setSource(QUrl(QStringLiteral("qrc:/model/AL_board.obj")));
    BladeTransform =new Qt3DCore::QTransform;
    BladeTransform->setScale(40.0f);
    BladeTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f),90.0f));
    BladeTransform->setTranslation(QVector3D(0.0f,0.0f, 0.0f));
    Qt3DCore::QEntity *BladeEntity = new Qt3DCore::QEntity(this);
    BladeEntity->addComponent(BladeMesh);
    BladeEntity->addComponent(bladeMaterial);
    BladeEntity->addComponent(BladeTransform);

    // 世界系坐标轴
    AxesEntity *axesEntity = new AxesEntity(this);
    axesEntity->setAxisLen(466);
    // 机器人自身系坐标轴
    AxesEntity_robot *axesEntity_robot = new AxesEntity_robot(robotEntity);
    axesEntity_robot->setAxisLen(30);
    // 辅助线
    AuxiliatyEntity *xoyEntity = new AuxiliatyEntity(axesEntity);
    xoyEntity->set_xoy_AuxiliaryLen(-400,-320);
    Qt3DCore::QTransform *xoyTransform = new Qt3DCore::QTransform;
    xoyTransform->setTranslation(QVector3D(400.0f,320.0f, 0.0f));
    xoyEntity->addComponent(xoyTransform);

    AuxiliatyEntity *yozEntity = new AuxiliatyEntity(axesEntity);
    yozEntity->set_yoz_AuxiliaryLen(-320,-350);
    Qt3DCore::QTransform *yozTransform = new Qt3DCore::QTransform;
    yozTransform->setTranslation(QVector3D(0.0f, 320.0f,350.0f));
    yozEntity->addComponent(yozTransform);

    AuxiliatyEntity *xozEntity = new AuxiliatyEntity(axesEntity);
    xozEntity->set_xoz_AuxiliaryLen(-400,-350);
    Qt3DCore::QTransform *xozTransform = new Qt3DCore::QTransform;
    xozTransform->setTranslation(QVector3D(400.0f, 0.0f,350.0f));
    xozEntity->addComponent(xozTransform);
}

void DobotModel::move(float robot_x, float robot_y, float robot_z) {
    // 位移扩大 100*(4)^(1/3) 倍
    float x0 = 0;
    float y0 = 0;
    float z0 = 0;
    robotTransform->setTranslation(QVector3D(158.7401051968199474 * (robot_x - x0), 
                                    158.7401051968199474 * (robot_y - y0), 
                                    158.7401051968199474 * (robot_z - z0) - 4.345));
}

/*
 * 一代旋转代码（参数：x,y坐标，yaw角）
void DobotModel::rotate_(float angle3)
{
    Eigen::Matrix3d rotation_matrix;
    Eigen::Matrix3d rotation_matrix1;// 绕Y轴逆时针旋转180度
    Eigen::Matrix3d rotation_matrix2;// 绕Z轴逆时针旋转-90度
    Eigen::Matrix3d rotation_matrix3;// 绕Z轴逆时针旋转YAW角度
    rotation_matrix1<<-1, 0, 0,
                       0, 1, 0,
                       0, 0,-1;
    rotation_matrix2<< 0, 1, 0,
                      -1, 0, 0,
                       0, 0, 1;
    rotation_matrix3<<cos(angle3),-sin(angle3),  0,
                      sin(angle3), cos(angle3),  0,
                      0          ,           0,  1;
    rotation_matrix=rotation_matrix3*rotation_matrix2*rotation_matrix1;
    // 旋转矩阵 转 轴-角（旋转向量）
    Eigen::AngleAxisd rotation_vector;
    rotation_vector.fromRotationMatrix(rotation_matrix);
    float vector_angle = rotation_vector.angle()*(180.00/M_PI);
    float vector_x=rotation_vector.axis().transpose().x();
    float vector_y=rotation_vector.axis().transpose().y();
    float vector_z=rotation_vector.axis().transpose().z();
    robotTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(vector_x,vector_y,vector_z),vector_angle));
}
*/

// 二代旋转代码
void DobotModel::rotate_quanternion(float x, float y, float z, float w) {
    // 四元数转旋转矩阵转旋转矢量
    // 初始化四元数，参数顺序为 w,x,y,z
    Eigen::Quaterniond quanternion(w, x, y, z);
    // 初始化旋转矩阵
    Eigen::Matrix3d rotation_matrix1,rotation_matrix2,rotation_matrix3,rotation_matrix_final;
    rotation_matrix1 << 0, 1, 0,
                       -1, 0, 0,
                        0, 0, 1;                // 首先绕z轴顺时针旋转90度
    rotation_matrix2 << 1, 0, 0,
                        0,-1, 0,
                        0, 0,-1;                // 其次绕X轴逆时针旋转180度
    rotation_matrix3 = quanternion.matrix();    // 四元数转旋转矩阵
    rotation_matrix_final = rotation_matrix3 * rotation_matrix2 * rotation_matrix1;
    // 旋转矩阵转旋转向量
    Eigen::AngleAxisd rotation_vector;
    rotation_vector.fromRotationMatrix(rotation_matrix_final);
    float vector_angle = rotation_vector.angle()*(180.00/M_PI);
    float vector_x=rotation_vector.axis().transpose().x();
    float vector_y=rotation_vector.axis().transpose().y();
    float vector_z=rotation_vector.axis().transpose().z();
    robotTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(vector_x, vector_y, vector_z), vector_angle));
}


