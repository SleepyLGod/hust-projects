#ifndef AXESENTITY_ROBOT_H
#define AXESENTITY_ROBOT_H

#include "lineentity.h"

// 自身系坐标轴
class AxesEntity_robot: public Qt3DCore::QEntity {
    public: 
    AxesEntity_robot(Qt3DCore::QNode * parent = nullptr);
    AxesEntity_robot(unsigned int axisLen,
    /* unsigned int auxiliaryLen1,unsigned int auxiliaryLen2, */
    Qt3DCore::QNode * parent = nullptr);

    void setAxisLen(unsigned int axisLen);

    private:
    // 坐标轴对象
    LineEntity * m_xAxisEntity = nullptr;
    LineEntity * m_yAxisEntity = nullptr;
    LineEntity * m_zAxisEntity = nullptr;

    void updateAxes(unsigned int axisLen);
};

#endif //  AXESENTITY_ROBOT_H