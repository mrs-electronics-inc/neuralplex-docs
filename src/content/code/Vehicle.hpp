#pragma once

#include <QObject>
#include <QtMath>
#include <QSharedPointer>
#include <QDebug>
#include "CanBus.hpp"
#include "CanEncodeDecode.h"

class Vehicle : public QObject
{
    Q_OBJECT

    Q_PROPERTY(float speedometer READ speedometer WRITE setSpeedometer NOTIFY speedometerChanged)
    Q_PROPERTY(float fuelLevel READ fuelLevel WRITE setFuelLevel NOTIFY fuelLevelChanged)
    Q_PROPERTY(int ignition READ ignition WRITE setIgnition NOTIFY ignitionChanged)
    Q_PROPERTY(float sensor1 READ sensor1 WRITE setSensor1 NOTIFY sensor1Changed)
    Q_PROPERTY(float sensor2 READ sensor2 WRITE setSensor2 NOTIFY sensor2Changed)
    Q_PROPERTY(float sensor3 READ sensor3 WRITE setSensor3 NOTIFY sensor3Changed)
    Q_PROPERTY(float sensor4 READ sensor4 WRITE setSensor4 NOTIFY sensor4Changed)

public:
    explicit Vehicle(QSharedPointer<CanBus> canBus, QObject *parent = nullptr);

    // Returns a shared pointer to the can bus object.
    QSharedPointer<CanBus> canBus() const;

    float speedometer() const;
    float fuelLevel() const;
    float sensor1() const;
    float sensor2() const;
    float sensor3() const;
    float sensor4() const;
    int ignition() const;

public slots:
    void processMessage(const QCanBusFrame &frame);

    void setSpeedometer(float speedometer);
    void setFuelLevel(float fuelLevel);
    void setSensor1(float sensor1);
    void setSensor2(float sensor2);
    void setSensor3(float sensor3);
    void setSensor4(float sensor4);
    void setIgnition(int ignition);

signals:
    void speedometerChanged(float speedometer);
    void fuelLevelChanged(float fuelLevel);
    void sensor1Changed(float sensor1);
    void sensor2Changed(float sensor2);
    void sensor3Changed(float sensor3);
    void sensor4Changed(float sensor4);
    void ignitionChanged(int ignition);

private:
    QSharedPointer<CanBus> m_canBus;
    float m_speedometer;
    float m_fuelLevel;
    float m_sensor1;
    float m_sensor2;
    float m_sensor3;
    float m_sensor4;
    int m_ignition;
};

// Define the Vehicle CAN IDs
#define DD1 0x18FEFC00 // Dash Display 1
#define CCVS1 0x18FEF100 // Vehicle speed 1
#define SENSOR 0x18FF0000 // Sensor Deviation
