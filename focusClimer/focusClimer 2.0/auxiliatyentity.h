#ifndef AUXILIATYENTITY_H
#define AUXILIATYENTITY_H
#include "lineentity.h"

// 三个平面上的辅助线
class AuxiliatyEntity: public Qt3DCore::QEntity {
    public: 
    AuxiliatyEntity(Qt3DCore::QNode * parent = nullptr);
    AuxiliatyEntity(
        int auxiliaryLen1,
        int auxiliaryLen2,
        Qt3DCore::QNode * parent = nullptr
    );

    void set_xoy_AuxiliaryLen(int auxiliaryLen1, int auxiliaryLen2);
    void set_yoz_AuxiliaryLen(int auxiliaryLen1, int auxiliaryLen2);
    void set_xoz_AuxiliaryLen(int auxiliaryLen1, int auxiliaryLen2);

    private:
    // 辅助线对象
    LineEntity * xoy_xAuxiliaryEntity = nullptr;
    LineEntity * xoy_yAuxiliaryEntity = nullptr;
    LineEntity * yoz_yAuxiliaryEntity = nullptr;
    LineEntity * yoz_zAuxiliaryEntity = nullptr;
    LineEntity * xoz_xAuxiliaryEntity = nullptr;
    LineEntity * xoz_zAuxiliaryEntity = nullptr;

    void xoy_updateAuxiliary(int auxiliaryLen1, int auxiliaryLen2);
    void yoz_updateAuxiliary(int auxiliaryLen1, int auxiliaryLen2);
    void xoz_updateAuxiliary(int auxiliaryLen1, int auxiliaryLen2);

};
#endif // AUXILIATYENTITY_H


