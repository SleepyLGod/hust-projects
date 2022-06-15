#ifndef AXESENTITY_H
#define AXESENTITY_H

#include "lineentity.h"

// 世界系坐标轴
class AxesEntity: public Qt3DCore::QEntity {
    public: 
    AxesEntity(Qt3DCore::QNode * parent = nullptr);
    AxesEntity(unsigned int axisLen, Qt3DCore::QNode * parent = nullptr);

    void setAxisLen(unsigned int axisLen);

    private:
    // 坐标轴对象
    LineEntity * m_xAxisEntity = nullptr;
    LineEntity * m_yAxisEntity = nullptr;
    LineEntity * m_zAxisEntity = nullptr;

    void updateAxes(unsigned int axisLen);
};

#endif // AXESENTITY_H