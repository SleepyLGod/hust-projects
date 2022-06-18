#ifndef TRAJECTORY_H
#define TRAJECTORY_H


#include <QTransform>
#include "lineentity.h"
#include <QEntity>
// 在我的Ubuntu20.04系统中的安装位置
//#include <eigen3/Eigen/Core>
//#include <eigen3/Eigen/Geometry>
// win10下的安装位置
#include <Eigen/Core>
#include <Eigen/Geometry>

class Trajectory : public LineEntity {

private:
    Eigen::Vector3d lastPoint;
public:
    Trajectory(const QColor &color, Qt3DCore::QNode *parent = nullptr):LineEntity(color, parent) {
    };
    void pointUpdate(Eigen::Vector3d lastPoint);    // 更新起点
    bool isOk(Eigen::Vector3d latestPoint);         // 判断是否更新起点
    void drawLine(Eigen::Vector3d lastPoint);       // 画线
    void clearTrajectory();                         // 清空
};

#endif // TRAJECTORY_H
