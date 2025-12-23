#include "Vehicle.hpp"

Vehicle::Vehicle(QSharedPointer<CanBus> canBus, QObject *parent)
    : QObject(parent)
    , m_canBus(canBus)
    , m_speedometer(0)
    , m_fuelLevel(0)
    , m_sensor1(0)
    , m_sensor2(0)
    , m_sensor3(0)
    , m_sensor4(0)
{
    m_canBus->setVehicleIds({ DD1, CCVS1, SENSOR });
    connect(m_canBus.data(), &CanBus::vehicleFrameArrived, this, &Vehicle::processMessage);
}

void Vehicle::processMessage(const QCanBusFrame &frame)
{
    const auto frameId = frame.frameId();
    const auto *payload = (uint8_t*)(frame.payload().constData());

    // Begin the switch statement for processing each CAN frame
    switch (frameId)
    {
    case DD1: {
        setFuelLevel(decode(payload, 8, 8, false, false, 0.4, 0));
        break;
    }
    case CCVS1: {
        setSpeedometer(decode(payload, 8, 16, false, false, 0.00390625, 0));
        break;
    }
    case SENSOR: {
        setSensor1(decode(payload, 0, 8, false, true, 0.4, 0));
        setSensor2(decode(payload, 8, 8, false, true, 0.4, 0));
        setSensor3(decode(payload, 16, 8, false, true, 0.4, 0));
        setSensor4(decode(payload, 24, 8, false, true, 0.4, 0));
        break;
    }
    default:
        break;
    }
}

float Vehicle::speedometer() const
{
    return m_speedometer;
}

float Vehicle::fuelLevel() const
{
    return m_fuelLevel;
}

float Vehicle::sensor1() const
{
    return m_sensor1;
}

float Vehicle::sensor2() const
{
    return m_sensor2;
}

float Vehicle::sensor3() const
{
    return m_sensor3;
}

float Vehicle::sensor4() const
{
    return m_sensor4;
}

int Vehicle::ignition() const
{
    return m_ignition;
}

void Vehicle::setSpeedometer(float speedometer)
{
    if (m_speedometer == speedometer)
        return;

    m_speedometer = speedometer;
    emit speedometerChanged(m_speedometer);
}

void Vehicle::setFuelLevel(float fuelLevel)
{
    if (m_fuelLevel == fuelLevel)
        return;

    m_fuelLevel = fuelLevel;
    emit fuelLevelChanged(m_fuelLevel);
}

void Vehicle::setSensor1(float sensor1)
{
    if (m_sensor1 == sensor1)
        return;

    m_sensor1 = sensor1;
    emit sensor1Changed(m_sensor1);
}

void Vehicle::setSensor2(float sensor2)
{
    if (m_sensor2 == sensor2)
        return;

    m_sensor2 = sensor2;
    emit sensor2Changed(m_sensor2);
}

void Vehicle::setSensor3(float sensor3)
{
    if (m_sensor3 == sensor3)
        return;

    m_sensor3 = sensor3;
    emit sensor3Changed(m_sensor3);
}

void Vehicle::setSensor4(float sensor4)
{
    if (m_sensor4 == sensor4)
        return;

    m_sensor4 = sensor4;
    emit sensor4Changed(m_sensor4);
}

void Vehicle::setIgnition(int ignition)
{
    if (m_ignition == ignition)
        return;

    m_ignition = ignition;
    emit ignitionChanged(m_ignition);
}
