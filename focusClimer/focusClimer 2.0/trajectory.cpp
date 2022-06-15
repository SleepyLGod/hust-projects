#include "trajectory.h"
#include <QDir>

// 前后距离小于一厘米，不移动
bool Trajectory::isOk(Eigen::Vector3d latestPoint) {
    return (latestPoint-lastPoint).norm()>0.01;
}

// 更新线段起点
void Trajectory::pointUpdate(Eigen::Vector3d latestPoint) {
    lastPoint=latestPoint;
}

// 绘制线段
void Trajectory::drawLine(Eigen::Vector3d latestPoint) {
    // 起点
    addVertex(QVector3D(158.7401051968199474*lastPoint[0],158.7401051968199474*lastPoint[1],158.7401051968199474*lastPoint[2]-4.345));
    // 终点
    addVertex(QVector3D(158.7401051968199474*latestPoint[0],158.7401051968199474*latestPoint[1],158.7401051968199474*latestPoint[2]-4.345));
}

// 清空线段
void Trajectory::clearTrajectory() {
    clearVertices();
}
