#include "auxiliatyentity.h"

AuxiliatyEntity::AuxiliatyEntity(Qt3DCore::QNode *parent) :
    Qt3DCore::QEntity(parent),
    xoy_xAuxiliaryEntity(new LineEntity(QColor(0xE4E2A3), this)),
    xoy_yAuxiliaryEntity(new LineEntity(QColor(0xE4E2A3), this)),
    yoz_yAuxiliaryEntity(new LineEntity(QColor(0xE4E2A3), this)),
    yoz_zAuxiliaryEntity(new LineEntity(QColor(0xE4E2A3), this)),
    xoz_xAuxiliaryEntity(new LineEntity(QColor(0xE4E2A3), this)),
    xoz_zAuxiliaryEntity(new LineEntity(QColor(0xE4E2A3), this)) {

    this->xoy_updateAuxiliary(0,0);
    this->yoz_updateAuxiliary(0,0);
    this->xoz_updateAuxiliary(0,0);
}

AuxiliatyEntity::AuxiliatyEntity(int auxiliaryLen1, int auxiliaryLen2, Qt3DCore::QNode *parent) :AuxiliatyEntity(parent) {
    this->xoy_updateAuxiliary(auxiliaryLen1,auxiliaryLen2);
    this->yoz_updateAuxiliary(auxiliaryLen1,auxiliaryLen2);
    this->xoz_updateAuxiliary(auxiliaryLen1,auxiliaryLen2);
}

void AuxiliatyEntity::set_xoy_AuxiliaryLen(int auxiliaryLen1, int auxiliaryLen2) {
    this->xoy_updateAuxiliary(auxiliaryLen1,auxiliaryLen2);
}

void AuxiliatyEntity::set_yoz_AuxiliaryLen(int auxiliaryLen1, int auxiliaryLen2) {
    this->yoz_updateAuxiliary(auxiliaryLen1,auxiliaryLen2);
}

void AuxiliatyEntity::set_xoz_AuxiliaryLen(int auxiliaryLen1, int auxiliaryLen2) {
    this->xoz_updateAuxiliary(auxiliaryLen1,auxiliaryLen2);
}

void AuxiliatyEntity::xoy_updateAuxiliary(int auxiliaryLen1, int auxiliaryLen2) {
    xoy_xAuxiliaryEntity->clearVertices();
    xoy_yAuxiliaryEntity->clearVertices();

    xoy_xAuxiliaryEntity->addVertex(QVector3D(0.0f, 0.0f, 0.0f));
    xoy_xAuxiliaryEntity->addVertex(QVector3D(auxiliaryLen1, 0.0f, 0.0f));
    xoy_yAuxiliaryEntity->addVertex(QVector3D(0.0f, 0.0f, 0.0f));
    xoy_yAuxiliaryEntity->addVertex(QVector3D(0.0f, auxiliaryLen2, 0.0f));

}

void AuxiliatyEntity::yoz_updateAuxiliary(int auxiliaryLen1, int auxiliaryLen2) {
    yoz_yAuxiliaryEntity->clearVertices();
    yoz_zAuxiliaryEntity->clearVertices();

    yoz_yAuxiliaryEntity->addVertex(QVector3D(0.0f, 0.0f, 0.0f));
    yoz_yAuxiliaryEntity->addVertex(QVector3D(0.0f,auxiliaryLen1, 0.0f));
    yoz_zAuxiliaryEntity->addVertex(QVector3D(0.0f, 0.0f, 0.0f));
    yoz_zAuxiliaryEntity->addVertex(QVector3D(0.0f, 0.0f, auxiliaryLen2));
}

void AuxiliatyEntity::xoz_updateAuxiliary(int auxiliaryLen1, int auxiliaryLen2) {
    xoz_xAuxiliaryEntity->clearVertices();
    xoz_zAuxiliaryEntity->clearVertices();

    xoz_xAuxiliaryEntity->addVertex(QVector3D(0.0f, 0.0f, 0.0f));
    xoz_xAuxiliaryEntity->addVertex(QVector3D(auxiliaryLen1, 0.0f, 0.0f));
    xoz_zAuxiliaryEntity->addVertex(QVector3D(0.0f, 0.0f, 0.0f));
    xoz_zAuxiliaryEntity->addVertex(QVector3D(0.0f, 0.0f, auxiliaryLen2));

}


/*
AxesEntity::AxesEntity(Qt3DCore::QNode *parent) :
    Qt3DCore::QEntity(parent),
    m_xAxisEntity(new LineEntity(Qt::red, this)),
    m_yAxisEntity(new LineEntity(Qt::green, this)),
    m_zAxisEntity(new LineEntity(Qt::blue, this)),
    xoy_xAuxiliaryEntity(new LineEntity(Qt::blue, this)),
    xoy_yAuxiliaryEntity(new LineEntity(Qt::blue, this)),
    yoz_yAuxiliaryEntity(new LineEntity(Qt::blue, this)),
    yoz_zAuxiliaryEntity(new LineEntity(Qt::blue, this)),
    xoz_xAuxiliaryEntity(new LineEntity(Qt::blue, this)),
    xoz_zAuxiliaryEntity(new LineEntity(Qt::blue, this))
{
    this->updateAxes(100);
    this->xoy_updateAuxiliary(0,0);
    this->yoz_updateAuxiliary(0,0);
    this->xoz_updateAuxiliary(0,0);
}

AxesEntity::AxesEntity(int axisLen, int auxiliaryLen1,int auxiliaryLen2, Qt3DCore::QNode *parent) : AxesEntity(parent)
{
    this->updateAxes(axisLen);
    this->xoy_updateAuxiliary(auxiliaryLen1,auxiliaryLen2);
    this->yoz_updateAuxiliary(auxiliaryLen1,auxiliaryLen2);
    this->xoz_updateAuxiliary(auxiliaryLen1,auxiliaryLen2);
}

void AxesEntity::setAxisLen(int axisLen)
{
    this->updateAxes(axisLen);
}

void AxesEntity::set_xoy_AuxiliaryLen(int auxiliaryLen1,int auxiliaryLen2)
{
    this->xoy_updateAuxiliary(auxiliaryLen1,auxiliaryLen2);
}

void AxesEntity::set_yoz_AuxiliaryLen(int auxiliaryLen1,int auxiliaryLen2)
{
    this->yoz_updateAuxiliary(auxiliaryLen1,auxiliaryLen2);
}
void AxesEntity::set_xoz_AuxiliaryLen(int auxiliaryLen1,int auxiliaryLen2)
{
    this->xoz_updateAuxiliary(auxiliaryLen1,auxiliaryLen2);
}

void AxesEntity::updateAxes(int axisLen)
{
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

void AxesEntity::xoy_updateAuxiliary(int auxiliaryLen1,int auxiliaryLen2)
{
    xoy_xAuxiliaryEntity->clearVertices();
    xoy_yAuxiliaryEntity->clearVertices();

    xoy_xAuxiliaryEntity->addVertex(QVector3D(0.0f, 0.0f, 0.0f));
    xoy_xAuxiliaryEntity->addVertex(QVector3D(-auxiliaryLen1, 0.0f, 0.0f));
    xoy_yAuxiliaryEntity->addVertex(QVector3D(0.0f, 0.0f, 0.0f));
    xoy_yAuxiliaryEntity->addVertex(QVector3D(0.0f, -auxiliaryLen2, 0.0f));

}

void AxesEntity::yoz_updateAuxiliary(int auxiliaryLen1,int auxiliaryLen2)
{
    yoz_yAuxiliaryEntity->clearVertices();
    yoz_zAuxiliaryEntity->clearVertices();

    yoz_yAuxiliaryEntity->addVertex(QVector3D(0.0f, 0.0f, 0.0f));
    yoz_yAuxiliaryEntity->addVertex(QVector3D(0.0f,-auxiliaryLen1,  0.0f));
    yoz_zAuxiliaryEntity->addVertex(QVector3D(0.0f, 0.0f, 0.0f));
    yoz_zAuxiliaryEntity->addVertex(QVector3D(0.0f, 0.0f, -auxiliaryLen2));
}

void AxesEntity::xoz_updateAuxiliary(int auxiliaryLen1,int auxiliaryLen2)
{
    xoz_xAuxiliaryEntity->clearVertices();
    xoz_zAuxiliaryEntity->clearVertices();

    xoz_xAuxiliaryEntity->addVertex(QVector3D(0.0f, 0.0f, 0.0f));
    xoz_xAuxiliaryEntity->addVertex(QVector3D(-auxiliaryLen1, 0.0f, 0.0f));
    xoz_zAuxiliaryEntity->addVertex(QVector3D(0.0f, 0.0f, 0.0f));
    xoz_zAuxiliaryEntity->addVertex(QVector3D(0.0f, 0.0f, -auxiliaryLen2));

}
*/
