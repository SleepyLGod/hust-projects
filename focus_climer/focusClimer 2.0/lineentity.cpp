#include "lineentity.h"

LineEntity::LineEntity(Qt3DCore::QNode *parent) :
    Qt3DCore::QEntity(parent),
    m_lineGeometry(new Qt3DRender::QGeometry(this)),
    m_lineVertexPositionBuf(new Qt3DRender::QBuffer(m_lineGeometry)),
    m_lineVertexIndexBuf(new Qt3DRender::QBuffer(m_lineGeometry)),
    m_lineGeometryRenderer(new Qt3DRender::QGeometryRenderer(this)),
    m_lineMaterial(new Qt3DExtras::QDiffuseSpecularMaterial(this)),
    m_lineVertexPositionAttribute(new Qt3DRender::QAttribute(m_lineGeometry)),
    m_lineVertexIndexAttribute(new Qt3DRender::QAttribute(m_lineGeometry)) {
    m_lineVertexPositionByteArray.resize(100000 * 3);
    m_lineVertexIndexByteArray.resize(100000 * 3);

    m_lineVertexPositionAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());
    m_lineVertexPositionAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
    m_lineVertexPositionAttribute->setVertexSize(3);
    m_lineVertexPositionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    m_lineVertexPositionAttribute->setBuffer(m_lineVertexPositionBuf);
    m_lineVertexPositionAttribute->setByteStride(3 * sizeof(float));
    m_lineVertexPositionAttribute->setCount(0);
    m_lineGeometry->addAttribute(m_lineVertexPositionAttribute);

    m_lineVertexIndexAttribute->setVertexBaseType(Qt3DRender::QAttribute::UnsignedInt);
    m_lineVertexIndexAttribute->setAttributeType(Qt3DRender::QAttribute::IndexAttribute);
    m_lineVertexIndexAttribute->setBuffer(m_lineVertexIndexBuf);
    m_lineVertexIndexAttribute->setCount(0);
    m_lineGeometry->addAttribute(m_lineVertexIndexAttribute);

    m_lineGeometryRenderer->setGeometry(m_lineGeometry);
    m_lineGeometryRenderer->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);

    this->addComponent(m_lineGeometryRenderer);
    this->addComponent(m_lineMaterial);
}

LineEntity::LineEntity(const QColor & color, Qt3DCore::QNode * parent): LineEntity(parent) {
        this -> setLineColor(color);
    }

    void LineEntity::setLineColor(const QColor & color) {
        m_lineMaterial -> setAmbient(color);
        m_lineMaterial -> setDiffuse(color);
    }

    void LineEntity::addVertex(const QVector3D & vertex) {
        float * bufPositionEndPtr = reinterpret_cast < float *> (
            m_lineVertexPositionByteArray.data()
        );
        *(bufPositionEndPtr + m_count * 3) = vertex.x();
        *(bufPositionEndPtr + m_count * 3 + 1) = vertex.y();
        *(bufPositionEndPtr + m_count * 3 + 2) = vertex.z();
        m_lineVertexPositionBuf -> setData(m_lineVertexPositionByteArray);

        unsigned int * bufIndexEndPtr = reinterpret_cast < unsigned int *> (
            m_lineVertexIndexByteArray.data()
        );
        *(bufIndexEndPtr + m_count) = m_count;
        m_lineVertexIndexBuf -> setData(m_lineVertexIndexByteArray);

        ++m_count;
        m_lineVertexPositionAttribute -> setCount(m_count);
        m_lineVertexIndexAttribute -> setCount(m_count);
    }

    void LineEntity::clearVertices() {
        m_count = 0;
        m_lineVertexPositionAttribute -> setCount(m_count);
        m_lineVertexIndexAttribute -> setCount(m_count);
    }
