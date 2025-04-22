/****************************************************************************
** Meta object code from reading C++ file 'skyviewcontroller.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "skyviewcontroller.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'skyviewcontroller.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN17SkyViewControllerE_t {};
} // unnamed namespace

template <> constexpr inline auto SkyViewController::qt_create_metaobjectdata<qt_meta_tag_ZN17SkyViewControllerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "SkyViewController",
        "azimuthChanged",
        "",
        "azimuth",
        "altitudeChanged",
        "altitude",
        "quaternionChanged",
        "quaternion",
        "visibleDSOsChanged",
        "locationChanged",
        "gpsStatusChanged",
        "enabled",
        "locationMetadataChanged",
        "locationStatusChanged",
        "status",
        "rightAscensionChanged",
        "ra",
        "declinationChanged",
        "dec",
        "debugDataChanged",
        "onAzimuthChanged",
        "onAttitudeChanged",
        "onRotationMatrixChanged",
        "RotationMatrix",
        "matrix",
        "onLocationChanged",
        "GeoCoordinate",
        "location",
        "onLocationError",
        "errorMessage",
        "onLocationAuthorizationChanged",
        "authorized",
        "onLocationMetadataChanged",
        "updateVisibleDSOs",
        "addCustomDSO",
        "name",
        "imageUrl",
        "size",
        "croppedWidth",
        "croppedHeight",
        "scaleFactor",
        "loadDefaultDSOs",
        "startSensors",
        "stopSensors",
        "setGPSAccuracy",
        "accuracy",
        "useManualLocation",
        "manual",
        "requestLocationPermission",
        "quaternionX",
        "quaternionY",
        "quaternionZ",
        "quaternionW",
        "m11",
        "m12",
        "m13",
        "m21",
        "m22",
        "m23",
        "m31",
        "m32",
        "m33",
        "visibleDSOs",
        "QVariantList",
        "isGPSEnabled",
        "locationAccuracy",
        "locationStatus",
        "rightAscension",
        "declination",
        "formattedRA",
        "formattedDEC"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'azimuthChanged'
        QtMocHelpers::SignalData<void(double)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 3 },
        }}),
        // Signal 'altitudeChanged'
        QtMocHelpers::SignalData<void(double)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 5 },
        }}),
        // Signal 'quaternionChanged'
        QtMocHelpers::SignalData<void(QQuaternion)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QQuaternion, 7 },
        }}),
        // Signal 'visibleDSOsChanged'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'locationChanged'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'gpsStatusChanged'
        QtMocHelpers::SignalData<void(bool)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 11 },
        }}),
        // Signal 'locationMetadataChanged'
        QtMocHelpers::SignalData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'locationStatusChanged'
        QtMocHelpers::SignalData<void(const QString &)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 14 },
        }}),
        // Signal 'rightAscensionChanged'
        QtMocHelpers::SignalData<void(double)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 16 },
        }}),
        // Signal 'declinationChanged'
        QtMocHelpers::SignalData<void(double)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 18 },
        }}),
        // Signal 'debugDataChanged'
        QtMocHelpers::SignalData<void()>(19, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onAzimuthChanged'
        QtMocHelpers::SlotData<void(double)>(20, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Double, 3 },
        }}),
        // Slot 'onAttitudeChanged'
        QtMocHelpers::SlotData<void(QQuaternion)>(21, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QQuaternion, 2 },
        }}),
        // Slot 'onRotationMatrixChanged'
        QtMocHelpers::SlotData<void(const RotationMatrix &)>(22, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 23, 24 },
        }}),
        // Slot 'onLocationChanged'
        QtMocHelpers::SlotData<void(GeoCoordinate)>(25, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 26, 27 },
        }}),
        // Slot 'onLocationError'
        QtMocHelpers::SlotData<void(const QString &)>(28, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 29 },
        }}),
        // Slot 'onLocationAuthorizationChanged'
        QtMocHelpers::SlotData<void(bool)>(30, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 31 },
        }}),
        // Slot 'onLocationMetadataChanged'
        QtMocHelpers::SlotData<void()>(32, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'updateVisibleDSOs'
        QtMocHelpers::SlotData<void()>(33, 2, QMC::AccessPrivate, QMetaType::Void),
        // Method 'addCustomDSO'
        QtMocHelpers::MethodData<void(const QString &, double, double, const QUrl &, double, int, int, double)>(34, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 35 }, { QMetaType::Double, 16 }, { QMetaType::Double, 18 }, { QMetaType::QUrl, 36 },
            { QMetaType::Double, 37 }, { QMetaType::Int, 38 }, { QMetaType::Int, 39 }, { QMetaType::Double, 40 },
        }}),
        // Method 'loadDefaultDSOs'
        QtMocHelpers::MethodData<void()>(41, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'startSensors'
        QtMocHelpers::MethodData<void()>(42, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'stopSensors'
        QtMocHelpers::MethodData<void()>(43, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'setGPSAccuracy'
        QtMocHelpers::MethodData<void(int)>(44, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 45 },
        }}),
        // Method 'useManualLocation'
        QtMocHelpers::MethodData<void(bool)>(46, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 47 },
        }}),
        // Method 'requestLocationPermission'
        QtMocHelpers::MethodData<void()>(48, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'quaternion'
        QtMocHelpers::PropertyData<QQuaternion>(7, QMetaType::QQuaternion, QMC::DefaultPropertyFlags, 2),
        // property 'quaternionX'
        QtMocHelpers::PropertyData<double>(49, QMetaType::Double, QMC::DefaultPropertyFlags, 2),
        // property 'quaternionY'
        QtMocHelpers::PropertyData<double>(50, QMetaType::Double, QMC::DefaultPropertyFlags, 2),
        // property 'quaternionZ'
        QtMocHelpers::PropertyData<double>(51, QMetaType::Double, QMC::DefaultPropertyFlags, 2),
        // property 'quaternionW'
        QtMocHelpers::PropertyData<double>(52, QMetaType::Double, QMC::DefaultPropertyFlags, 2),
        // property 'm11'
        QtMocHelpers::PropertyData<double>(53, QMetaType::Double, QMC::DefaultPropertyFlags, 10),
        // property 'm12'
        QtMocHelpers::PropertyData<double>(54, QMetaType::Double, QMC::DefaultPropertyFlags, 10),
        // property 'm13'
        QtMocHelpers::PropertyData<double>(55, QMetaType::Double, QMC::DefaultPropertyFlags, 10),
        // property 'm21'
        QtMocHelpers::PropertyData<double>(56, QMetaType::Double, QMC::DefaultPropertyFlags, 10),
        // property 'm22'
        QtMocHelpers::PropertyData<double>(57, QMetaType::Double, QMC::DefaultPropertyFlags, 10),
        // property 'm23'
        QtMocHelpers::PropertyData<double>(58, QMetaType::Double, QMC::DefaultPropertyFlags, 10),
        // property 'm31'
        QtMocHelpers::PropertyData<double>(59, QMetaType::Double, QMC::DefaultPropertyFlags, 10),
        // property 'm32'
        QtMocHelpers::PropertyData<double>(60, QMetaType::Double, QMC::DefaultPropertyFlags, 10),
        // property 'm33'
        QtMocHelpers::PropertyData<double>(61, QMetaType::Double, QMC::DefaultPropertyFlags, 10),
        // property 'azimuth'
        QtMocHelpers::PropertyData<double>(3, QMetaType::Double, QMC::DefaultPropertyFlags, 0),
        // property 'altitude'
        QtMocHelpers::PropertyData<double>(5, QMetaType::Double, QMC::DefaultPropertyFlags, 1),
        // property 'visibleDSOs'
        QtMocHelpers::PropertyData<QVariantList>(62, 0x80000000 | 63, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 3),
        // property 'location'
        QtMocHelpers::PropertyData<GeoCoordinate>(27, 0x80000000 | 26, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet, 4),
        // property 'isGPSEnabled'
        QtMocHelpers::PropertyData<bool>(64, QMetaType::Bool, QMC::DefaultPropertyFlags, 5),
        // property 'locationAccuracy'
        QtMocHelpers::PropertyData<double>(65, QMetaType::Double, QMC::DefaultPropertyFlags, 6),
        // property 'locationStatus'
        QtMocHelpers::PropertyData<QString>(66, QMetaType::QString, QMC::DefaultPropertyFlags, 7),
        // property 'rightAscension'
        QtMocHelpers::PropertyData<double>(67, QMetaType::Double, QMC::DefaultPropertyFlags, 8),
        // property 'declination'
        QtMocHelpers::PropertyData<double>(68, QMetaType::Double, QMC::DefaultPropertyFlags, 9),
        // property 'formattedRA'
        QtMocHelpers::PropertyData<QString>(69, QMetaType::QString, QMC::DefaultPropertyFlags, 8),
        // property 'formattedDEC'
        QtMocHelpers::PropertyData<QString>(70, QMetaType::QString, QMC::DefaultPropertyFlags, 9),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<SkyViewController, qt_meta_tag_ZN17SkyViewControllerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject SkyViewController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17SkyViewControllerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17SkyViewControllerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN17SkyViewControllerE_t>.metaTypes,
    nullptr
} };

void SkyViewController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SkyViewController *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->azimuthChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 1: _t->altitudeChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 2: _t->quaternionChanged((*reinterpret_cast< std::add_pointer_t<QQuaternion>>(_a[1]))); break;
        case 3: _t->visibleDSOsChanged(); break;
        case 4: _t->locationChanged(); break;
        case 5: _t->gpsStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 6: _t->locationMetadataChanged(); break;
        case 7: _t->locationStatusChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->rightAscensionChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 9: _t->declinationChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 10: _t->debugDataChanged(); break;
        case 11: _t->onAzimuthChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 12: _t->onAttitudeChanged((*reinterpret_cast< std::add_pointer_t<QQuaternion>>(_a[1]))); break;
        case 13: _t->onRotationMatrixChanged((*reinterpret_cast< std::add_pointer_t<RotationMatrix>>(_a[1]))); break;
        case 14: _t->onLocationChanged((*reinterpret_cast< std::add_pointer_t<GeoCoordinate>>(_a[1]))); break;
        case 15: _t->onLocationError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 16: _t->onLocationAuthorizationChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 17: _t->onLocationMetadataChanged(); break;
        case 18: _t->updateVisibleDSOs(); break;
        case 19: _t->addCustomDSO((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QUrl>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[7])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[8]))); break;
        case 20: _t->loadDefaultDSOs(); break;
        case 21: _t->startSensors(); break;
        case 22: _t->stopSensors(); break;
        case 23: _t->setGPSAccuracy((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 24: _t->useManualLocation((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 25: _t->requestLocationPermission(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< GeoCoordinate >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (SkyViewController::*)(double )>(_a, &SkyViewController::azimuthChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (SkyViewController::*)(double )>(_a, &SkyViewController::altitudeChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (SkyViewController::*)(QQuaternion )>(_a, &SkyViewController::quaternionChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (SkyViewController::*)()>(_a, &SkyViewController::visibleDSOsChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (SkyViewController::*)()>(_a, &SkyViewController::locationChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (SkyViewController::*)(bool )>(_a, &SkyViewController::gpsStatusChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (SkyViewController::*)()>(_a, &SkyViewController::locationMetadataChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (SkyViewController::*)(const QString & )>(_a, &SkyViewController::locationStatusChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (SkyViewController::*)(double )>(_a, &SkyViewController::rightAscensionChanged, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (SkyViewController::*)(double )>(_a, &SkyViewController::declinationChanged, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (SkyViewController::*)()>(_a, &SkyViewController::debugDataChanged, 10))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 17:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< GeoCoordinate >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QQuaternion*>(_v) = _t->quaternion(); break;
        case 1: *reinterpret_cast<double*>(_v) = _t->quaternionX(); break;
        case 2: *reinterpret_cast<double*>(_v) = _t->quaternionY(); break;
        case 3: *reinterpret_cast<double*>(_v) = _t->quaternionZ(); break;
        case 4: *reinterpret_cast<double*>(_v) = _t->quaternionW(); break;
        case 5: *reinterpret_cast<double*>(_v) = _t->m11(); break;
        case 6: *reinterpret_cast<double*>(_v) = _t->m12(); break;
        case 7: *reinterpret_cast<double*>(_v) = _t->m13(); break;
        case 8: *reinterpret_cast<double*>(_v) = _t->m21(); break;
        case 9: *reinterpret_cast<double*>(_v) = _t->m22(); break;
        case 10: *reinterpret_cast<double*>(_v) = _t->m23(); break;
        case 11: *reinterpret_cast<double*>(_v) = _t->m31(); break;
        case 12: *reinterpret_cast<double*>(_v) = _t->m32(); break;
        case 13: *reinterpret_cast<double*>(_v) = _t->m33(); break;
        case 14: *reinterpret_cast<double*>(_v) = _t->azimuth(); break;
        case 15: *reinterpret_cast<double*>(_v) = _t->altitude(); break;
        case 16: *reinterpret_cast<QVariantList*>(_v) = _t->visibleDSOs(); break;
        case 17: *reinterpret_cast<GeoCoordinate*>(_v) = _t->location(); break;
        case 18: *reinterpret_cast<bool*>(_v) = _t->isGPSEnabled(); break;
        case 19: *reinterpret_cast<double*>(_v) = _t->locationAccuracy(); break;
        case 20: *reinterpret_cast<QString*>(_v) = _t->locationStatus(); break;
        case 21: *reinterpret_cast<double*>(_v) = _t->rightAscension(); break;
        case 22: *reinterpret_cast<double*>(_v) = _t->declination(); break;
        case 23: *reinterpret_cast<QString*>(_v) = _t->formattedRA(); break;
        case 24: *reinterpret_cast<QString*>(_v) = _t->formattedDEC(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 17: _t->setLocation(*reinterpret_cast<GeoCoordinate*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *SkyViewController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SkyViewController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17SkyViewControllerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SkyViewController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }
    return _id;
}

// SIGNAL 0
void SkyViewController::azimuthChanged(double _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void SkyViewController::altitudeChanged(double _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void SkyViewController::quaternionChanged(QQuaternion _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void SkyViewController::visibleDSOsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void SkyViewController::locationChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void SkyViewController::gpsStatusChanged(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void SkyViewController::locationMetadataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void SkyViewController::locationStatusChanged(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1);
}

// SIGNAL 8
void SkyViewController::rightAscensionChanged(double _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1);
}

// SIGNAL 9
void SkyViewController::declinationChanged(double _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 9, nullptr, _t1);
}

// SIGNAL 10
void SkyViewController::debugDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}
QT_WARNING_POP
