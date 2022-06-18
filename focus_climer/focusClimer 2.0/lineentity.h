#ifndef LINEENTITY_H
#define LINEENTITY_H

#include <Qt3DCore/QEntity>
#include <Qt3DRender/QGeometry>
#include <Qt3DRender/QBuffer>
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DExtras/QDiffuseSpecularMaterial>
#include <Qt3DRender/QAttribute>
#include <QVector3D>

class LineEntity : public Qt3DCore::QEntity {

public:
    LineEntity(Qt3DCore::QNode *parent = nullptr);
    LineEntity(const QColor &color, Qt3DCore::QNode *parent = nullptr);

    void setLineColor(const QColor &color);     // 设置颜色
    void addVertex(const QVector3D &vertex);    // 画线
    void clearVertices();                       // 清空所有线

private:
    Qt3DRender::QGeometry *m_lineGeometry = nullptr;
    Qt3DRender::QBuffer *m_lineVertexPositionBuf = nullptr;
    Qt3DRender::QBuffer *m_lineVertexIndexBuf = nullptr;
    Qt3DRender::QGeometryRenderer *m_lineGeometryRenderer = nullptr;
    Qt3DExtras::QDiffuseSpecularMaterial *m_lineMaterial = nullptr;
    Qt3DRender::QAttribute *m_lineVertexPositionAttribute = nullptr;
    Qt3DRender::QAttribute *m_lineVertexIndexAttribute = nullptr;
    QByteArray m_lineVertexPositionByteArray;
    QByteArray m_lineVertexIndexByteArray;

    unsigned int m_count = 0;   // 用于vertex数目计数
};

#endif // LINEENTITY_H
