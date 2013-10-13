/****************************************************************************
** Meta object code from reading C++ file 'rendering_thread_manager.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "rendering_thread_manager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rendering_thread_manager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RenderManager[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      30,   14,   14,   14, 0x0a,
      49,   39,   14,   14, 0x0a,
      82,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RenderManager[] = {
    "RenderManager\0\0updateScreen()\0render()\0"
    "x,y,color\0tracerRayCompleted(int,int,Vec3)\0"
    "tracerCompleted()\0"
};

void RenderManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RenderManager *_t = static_cast<RenderManager *>(_o);
        switch (_id) {
        case 0: _t->updateScreen(); break;
        case 1: _t->render(); break;
        case 2: _t->tracerRayCompleted((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< Vec3(*)>(_a[3]))); break;
        case 3: _t->tracerCompleted(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RenderManager::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RenderManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RenderManager,
      qt_meta_data_RenderManager, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RenderManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RenderManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RenderManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RenderManager))
        return static_cast<void*>(const_cast< RenderManager*>(this));
    return QObject::qt_metacast(_clname);
}

int RenderManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void RenderManager::updateScreen()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
