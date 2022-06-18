#ifndef DOBOTMODEL_H
#define DOBOTMODEL_H

#include <Qt3DCore/QEntity>
#include <QVector3D>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QDiffuseSpecularMaterial>
#include <Qt3DRender/QMesh>
#include <iostream>
#include "axesentity.h"
// 本人Ubuntu20.04系统中的安装位置
// #include <eigen3/Eigen/Core>
// #include <eigen3/Eigen/Geometry>
// 本人win10下的安装位置
#include <Eigen/Core>
#include <Eigen/Geometry>

class DobotModel : public Qt3DCore::QEntity {
public:
    DobotModel(Qt3DCore::QNode *parent = nullptr);
    void rotate_(float angle3);
    void rotate_quanternion(float x,float y,float z,float w);
    void move(float robot_x,float robot_y,float robot_z);
    void move_(float robot_x,float robot_y);
private:
    QVector3D currentAngles;
    QVector3D currentPositions;
    QVector3D originalPositions;

    Qt3DCore::QTransform *BladeTransform;
    Qt3DCore::QTransform *robotTransform;
    Qt3DCore::QTransform *link1Transform;
};

#endif // DOBOTMODEL_H
