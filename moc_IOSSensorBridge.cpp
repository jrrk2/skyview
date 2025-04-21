/****************************************************************************
** Meta object code from reading C++ file 'IOSSensorBridge.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "IOSSensorBridge.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IOSSensorBridge.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN15IOSSensorBridgeE_t {};
} // unnamed namespace

template <> constexpr inline auto IOSSensorBridge::qt_create_metaobjectdata<qt_meta_tag_ZN15IOSSensorBridgeE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "IOSSensorBridge",
        "azimuthChanged",
        "",
        "azimuth",
        "pitchChanged",
        "pitch",
        "rollChanged",
        "roll",
        "yawChanged",
        "yaw",
        "locationChanged",
        "GeoCoordinate",
        "location",
        "locationErrorOccurred",
        "errorMessage",
        "locationAuthorizationChanged",
        "authorized",
        "locationMetadataChanged",
        "startSensors",
        "stopSensors",
        "setGPSAccuracy",
        "GPSAccuracy",
        "accuracy",
        "setGPSUpdateInterval",
        "meters",
        "isGPSAvailable",
        "isCompassAvailable",
        "locationAuthorized",
        "lastGPSError",
        "locationAccuracy",
        "locationSpeed",
        "locationCourse",
        "Best",
        "Navigation",
        "Balanced",
        "LowPower"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'azimuthChanged'
        QtMocHelpers::SignalData<void(double)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 3 },
        }}),
        // Signal 'pitchChanged'
        QtMocHelpers::SignalData<void(double)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 5 },
        }}),
        // Signal 'rollChanged'
        QtMocHelpers::SignalData<void(double)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 7 },
        }}),
        // Signal 'yawChanged'
        QtMocHelpers::SignalData<void(double)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 9 },
        }}),
        // Signal 'locationChanged'
        QtMocHelpers::SignalData<void(GeoCoordinate)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 11, 12 },
        }}),
        // Signal 'locationErrorOccurred'
        QtMocHelpers::SignalData<void(const QString &)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 14 },
        }}),
        // Signal 'locationAuthorizationChanged'
        QtMocHelpers::SignalData<void(bool)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 16 },
        }}),
        // Signal 'locationMetadataChanged'
        QtMocHelpers::SignalData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'startSensors'
        QtMocHelpers::MethodData<void()>(18, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'stopSensors'
        QtMocHelpers::MethodData<void()>(19, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'setGPSAccuracy'
        QtMocHelpers::MethodData<void(GPSAccuracy)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 21, 22 },
        }}),
        // Method 'setGPSUpdateInterval'
        QtMocHelpers::MethodData<void(double)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 24 },
        }}),
        // Method 'isGPSAvailable'
        QtMocHelpers::MethodData<bool() const>(25, 2, QMC::AccessPublic, QMetaType::Bool),
        // Method 'isCompassAvailable'
        QtMocHelpers::MethodData<bool() const>(26, 2, QMC::AccessPublic, QMetaType::Bool),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'azimuth'
        QtMocHelpers::PropertyData<double>(3, QMetaType::Double, QMC::DefaultPropertyFlags, 0),
        // property 'pitch'
        QtMocHelpers::PropertyData<double>(5, QMetaType::Double, QMC::DefaultPropertyFlags, 1),
        // property 'roll'
        QtMocHelpers::PropertyData<double>(7, QMetaType::Double, QMC::DefaultPropertyFlags, 2),
        // property 'yaw'
        QtMocHelpers::PropertyData<double>(9, QMetaType::Double, QMC::DefaultPropertyFlags, 3),
        // property 'location'
        QtMocHelpers::PropertyData<GeoCoordinate>(12, 0x80000000 | 11, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 4),
        // property 'locationAuthorized'
        QtMocHelpers::PropertyData<bool>(27, QMetaType::Bool, QMC::DefaultPropertyFlags, 6),
        // property 'lastGPSError'
        QtMocHelpers::PropertyData<QString>(28, QMetaType::QString, QMC::DefaultPropertyFlags, 5),
        // property 'locationAccuracy'
        QtMocHelpers::PropertyData<double>(29, QMetaType::Double, QMC::DefaultPropertyFlags, 7),
        // property 'locationSpeed'
        QtMocHelpers::PropertyData<double>(30, QMetaType::Double, QMC::DefaultPropertyFlags, 7),
        // property 'locationCourse'
        QtMocHelpers::PropertyData<double>(31, QMetaType::Double, QMC::DefaultPropertyFlags, 7),
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'GPSAccuracy'
        QtMocHelpers::EnumData<GPSAccuracy>(21, 21, QMC::EnumFlags{}).add({
            {   32, GPSAccuracy::Best },
            {   33, GPSAccuracy::Navigation },
            {   34, GPSAccuracy::Balanced },
            {   35, GPSAccuracy::LowPower },
        }),
    };
    return QtMocHelpers::metaObjectData<IOSSensorBridge, qt_meta_tag_ZN15IOSSensorBridgeE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject IOSSensorBridge::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15IOSSensorBridgeE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15IOSSensorBridgeE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15IOSSensorBridgeE_t>.metaTypes,
    nullptr
} };

void IOSSensorBridge::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<IOSSensorBridge *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->azimuthChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 1: _t->pitchChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 2: _t->rollChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 3: _t->yawChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 4: _t->locationChanged((*reinterpret_cast< std::add_pointer_t<GeoCoordinate>>(_a[1]))); break;
        case 5: _t->locationErrorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->locationAuthorizationChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 7: _t->locationMetadataChanged(); break;
        case 8: _t->startSensors(); break;
        case 9: _t->stopSensors(); break;
        case 10: _t->setGPSAccuracy((*reinterpret_cast< std::add_pointer_t<GPSAccuracy>>(_a[1]))); break;
        case 11: _t->setGPSUpdateInterval((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 12: { bool _r = _t->isGPSAvailable();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 13: { bool _r = _t->isCompassAvailable();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (IOSSensorBridge::*)(double )>(_a, &IOSSensorBridge::azimuthChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (IOSSensorBridge::*)(double )>(_a, &IOSSensorBridge::pitchChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (IOSSensorBridge::*)(double )>(_a, &IOSSensorBridge::rollChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (IOSSensorBridge::*)(double )>(_a, &IOSSensorBridge::yawChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (IOSSensorBridge::*)(GeoCoordinate )>(_a, &IOSSensorBridge::locationChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (IOSSensorBridge::*)(const QString & )>(_a, &IOSSensorBridge::locationErrorOccurred, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (IOSSensorBridge::*)(bool )>(_a, &IOSSensorBridge::locationAuthorizationChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (IOSSensorBridge::*)()>(_a, &IOSSensorBridge::locationMetadataChanged, 7))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<double*>(_v) = _t->azimuth(); break;
        case 1: *reinterpret_cast<double*>(_v) = _t->pitch(); break;
        case 2: *reinterpret_cast<double*>(_v) = _t->roll(); break;
        case 3: *reinterpret_cast<double*>(_v) = _t->yaw(); break;
        case 4: *reinterpret_cast<GeoCoordinate*>(_v) = _t->location(); break;
        case 5: *reinterpret_cast<bool*>(_v) = _t->isLocationAuthorized(); break;
        case 6: *reinterpret_cast<QString*>(_v) = _t->lastGPSError(); break;
        case 7: *reinterpret_cast<double*>(_v) = _t->locationAccuracy(); break;
        case 8: *reinterpret_cast<double*>(_v) = _t->locationSpeed(); break;
        case 9: *reinterpret_cast<double*>(_v) = _t->locationCourse(); break;
        default: break;
        }
    }
}

const QMetaObject *IOSSensorBridge::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IOSSensorBridge::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15IOSSensorBridgeE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int IOSSensorBridge::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void IOSSensorBridge::azimuthChanged(double _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void IOSSensorBridge::pitchChanged(double _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void IOSSensorBridge::rollChanged(double _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void IOSSensorBridge::yawChanged(double _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void IOSSensorBridge::locationChanged(GeoCoordinate _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void IOSSensorBridge::locationErrorOccurred(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void IOSSensorBridge::locationAuthorizationChanged(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void IOSSensorBridge::locationMetadataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
