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
        "onAzimuthChanged",
        "onPitchChanged",
        "pitch",
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
        "loadDefaultDSOs",
        "startSensors",
        "stopSensors",
        "setGPSAccuracy",
        "accuracy",
        "useManualLocation",
        "manual",
        "requestLocationPermission",
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
        // Signal 'visibleDSOsChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'locationChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'gpsStatusChanged'
        QtMocHelpers::SignalData<void(bool)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 9 },
        }}),
        // Signal 'locationMetadataChanged'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'locationStatusChanged'
        QtMocHelpers::SignalData<void(const QString &)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 12 },
        }}),
        // Signal 'rightAscensionChanged'
        QtMocHelpers::SignalData<void(double)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 14 },
        }}),
        // Signal 'declinationChanged'
        QtMocHelpers::SignalData<void(double)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Double, 16 },
        }}),
        // Slot 'onAzimuthChanged'
        QtMocHelpers::SlotData<void(double)>(17, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Double, 3 },
        }}),
        // Slot 'onPitchChanged'
        QtMocHelpers::SlotData<void(double)>(18, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Double, 19 },
        }}),
        // Slot 'onLocationChanged'
        QtMocHelpers::SlotData<void(GeoCoordinate)>(20, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 21, 22 },
        }}),
        // Slot 'onLocationError'
        QtMocHelpers::SlotData<void(const QString &)>(23, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 24 },
        }}),
        // Slot 'onLocationAuthorizationChanged'
        QtMocHelpers::SlotData<void(bool)>(25, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 26 },
        }}),
        // Slot 'onLocationMetadataChanged'
        QtMocHelpers::SlotData<void()>(27, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'updateVisibleDSOs'
        QtMocHelpers::SlotData<void()>(28, 2, QMC::AccessPrivate, QMetaType::Void),
        // Method 'addCustomDSO'
        QtMocHelpers::MethodData<void(const QString &, double, double, const QUrl &)>(29, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 30 }, { QMetaType::Double, 14 }, { QMetaType::Double, 16 }, { QMetaType::QUrl, 31 },
        }}),
        // Method 'loadDefaultDSOs'
        QtMocHelpers::MethodData<void()>(32, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'startSensors'
        QtMocHelpers::MethodData<void()>(33, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'stopSensors'
        QtMocHelpers::MethodData<void()>(34, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'setGPSAccuracy'
        QtMocHelpers::MethodData<void(int)>(35, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 36 },
        }}),
        // Method 'useManualLocation'
        QtMocHelpers::MethodData<void(bool)>(37, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 38 },
        }}),
        // Method 'requestLocationPermission'
        QtMocHelpers::MethodData<void()>(39, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'azimuth'
        QtMocHelpers::PropertyData<double>(3, QMetaType::Double, QMC::DefaultPropertyFlags, 0),
        // property 'altitude'
        QtMocHelpers::PropertyData<double>(5, QMetaType::Double, QMC::DefaultPropertyFlags, 1),
        // property 'visibleDSOs'
        QtMocHelpers::PropertyData<QVariantList>(40, 0x80000000 | 41, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 2),
        // property 'location'
        QtMocHelpers::PropertyData<GeoCoordinate>(22, 0x80000000 | 21, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet, 3),
        // property 'isGPSEnabled'
        QtMocHelpers::PropertyData<bool>(42, QMetaType::Bool, QMC::DefaultPropertyFlags, 4),
        // property 'locationAccuracy'
        QtMocHelpers::PropertyData<double>(43, QMetaType::Double, QMC::DefaultPropertyFlags, 5),
        // property 'locationStatus'
        QtMocHelpers::PropertyData<QString>(44, QMetaType::QString, QMC::DefaultPropertyFlags, 6),
        // property 'rightAscension'
        QtMocHelpers::PropertyData<double>(45, QMetaType::Double, QMC::DefaultPropertyFlags, 7),
        // property 'declination'
        QtMocHelpers::PropertyData<double>(46, QMetaType::Double, QMC::DefaultPropertyFlags, 8),
        // property 'formattedRA'
        QtMocHelpers::PropertyData<QString>(47, QMetaType::QString, QMC::DefaultPropertyFlags, 7),
        // property 'formattedDEC'
        QtMocHelpers::PropertyData<QString>(48, QMetaType::QString, QMC::DefaultPropertyFlags, 8),
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
        case 2: _t->visibleDSOsChanged(); break;
        case 3: _t->locationChanged(); break;
        case 4: _t->gpsStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 5: _t->locationMetadataChanged(); break;
        case 6: _t->locationStatusChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->rightAscensionChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 8: _t->declinationChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 9: _t->onAzimuthChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 10: _t->onPitchChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 11: _t->onLocationChanged((*reinterpret_cast< std::add_pointer_t<GeoCoordinate>>(_a[1]))); break;
        case 12: _t->onLocationError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 13: _t->onLocationAuthorizationChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 14: _t->onLocationMetadataChanged(); break;
        case 15: _t->updateVisibleDSOs(); break;
        case 16: _t->addCustomDSO((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QUrl>>(_a[4]))); break;
        case 17: _t->loadDefaultDSOs(); break;
        case 18: _t->startSensors(); break;
        case 19: _t->stopSensors(); break;
        case 20: _t->setGPSAccuracy((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 21: _t->useManualLocation((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 22: _t->requestLocationPermission(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 11:
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
        if (QtMocHelpers::indexOfMethod<void (SkyViewController::*)()>(_a, &SkyViewController::visibleDSOsChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (SkyViewController::*)()>(_a, &SkyViewController::locationChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (SkyViewController::*)(bool )>(_a, &SkyViewController::gpsStatusChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (SkyViewController::*)()>(_a, &SkyViewController::locationMetadataChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (SkyViewController::*)(const QString & )>(_a, &SkyViewController::locationStatusChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (SkyViewController::*)(double )>(_a, &SkyViewController::rightAscensionChanged, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (SkyViewController::*)(double )>(_a, &SkyViewController::declinationChanged, 8))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< GeoCoordinate >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<double*>(_v) = _t->azimuth(); break;
        case 1: *reinterpret_cast<double*>(_v) = _t->altitude(); break;
        case 2: *reinterpret_cast<QVariantList*>(_v) = _t->visibleDSOs(); break;
        case 3: *reinterpret_cast<GeoCoordinate*>(_v) = _t->location(); break;
        case 4: *reinterpret_cast<bool*>(_v) = _t->isGPSEnabled(); break;
        case 5: *reinterpret_cast<double*>(_v) = _t->locationAccuracy(); break;
        case 6: *reinterpret_cast<QString*>(_v) = _t->locationStatus(); break;
        case 7: *reinterpret_cast<double*>(_v) = _t->rightAscension(); break;
        case 8: *reinterpret_cast<double*>(_v) = _t->declination(); break;
        case 9: *reinterpret_cast<QString*>(_v) = _t->formattedRA(); break;
        case 10: *reinterpret_cast<QString*>(_v) = _t->formattedDEC(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 3: _t->setLocation(*reinterpret_cast<GeoCoordinate*>(_v)); break;
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
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
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
void SkyViewController::visibleDSOsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SkyViewController::locationChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void SkyViewController::gpsStatusChanged(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void SkyViewController::locationMetadataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void SkyViewController::locationStatusChanged(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void SkyViewController::rightAscensionChanged(double _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1);
}

// SIGNAL 8
void SkyViewController::declinationChanged(double _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1);
}
QT_WARNING_POP
