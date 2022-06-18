#include "axesentity.h"

AxesEntity::AxesEntity(Qt3DCore::QNode *parent) :Qt3DCore::QEntity(parent),
m_xAxisEntity(new LineEntity(Qt::red, this)),
m_yAxisEntity(new LineEntity(Qt::green, this)),
m_zAxisEntity(new LineEntity(Qt::blue, this)) {
    this->updateAxes(100);
}

AxesEntity::AxesEntity(unsigned int axisLen, Qt3DCore::QNode *parent) :AxesEntity(parent) {
    this->updateAxes(axisLen);
}

void AxesEntity::setAxisLen(unsigned int axisLen) {
    this->updateAxes(axisLen);
}

void AxesEntity::updateAxes(unsigned int axisLen) {
    m_xAxisEntity->clearVertices();
    m_yAxisEntity->clearVertices();
    m_zAxisEntity->clearVertices();

    m_xAxisEntity->addVertex(QVector3D(0.0f, 0.0f, 0.0f));
    m_xAxisEntity->addVertex(QVector3D(axisLen, 0.0f, 0.0f));

    m_yAxisEntity->addVertex(QVector3D(0.0f, 0.0f, 0.0f));
    m_yAxisEntity->addVertex(QVector3D(0.0f, axisLen,0.0f));

    m_zAxisEntity->addVertex(QVector3D(0.0f, 0.0f, 0.0f));
    m_zAxisEntity->addVertex(QVector3D(0.0f, 0.0f, axisLen));
}


