#include "CanBus.hpp"
#include <QDebug>

CanBus::CanBus(QString busInterface, QObject *parent)
    : QObject(parent)
    , m_busInterface(busInterface)
    , m_canbus(nullptr)
    , m_activityTimeout(120)
    , m_hadWriteSuccess(true)
    , m_timeoutCounter(0)
    , m_isActive(true)
{
    connectBus();
}

CanBus::~CanBus()
{
    if (m_canbus)
    {
        m_canbus->disconnectDevice();
    }
}

bool CanBus::connectBus()
{
    if (m_canbus != nullptr)
    {
        return false;
    }

    // Connect to the CAN interfaces.
    m_canbus = QCanBus::instance()->createDevice("socketcan", m_busInterface);

    // If we can access the given interface, try to connect.
    if (m_canbus != nullptr)
    {
        // Listen for new CAN frames.
        connect(m_canbus, &QCanBusDevice::framesReceived, this, &CanBus::onFramesReceived);

        // Connect the device.
        bool success = m_canbus->connectDevice();
        if (success)
        {
            // Start the timer to monitor CAN messages
            if (m_activityTimeout > 0)
            {
                // Check for CAN activity
                connect(&m_activityTimer, &QTimer::timeout, this, &CanBus::checkCanActivity);
                m_activityTimer.start(1000);
            }
        }
        qDebug() << "Connect to CAN interface" << m_busInterface << "-" << (success ? "success" : "error");
        return success;
    }
    else
    {
        qDebug() << "Could not connect to CAN interface" << m_busInterface;
        return false;
    }
}

bool CanBus::writeFrame(quint32 id, char payload[], int payloadLengthBytes, bool extFrame, QCanBusFrame::FrameType type)
{
    QByteArray data(payload, payloadLengthBytes);

    // Setup CAN frame.
    QCanBusFrame frame(id, data);
    frame.setExtendedFrameFormat(extFrame);
    frame.setFrameType(type);

    return writeFrame(frame);
}

bool CanBus::writeFrame(QCanBusFrame frame)
{
    bool success = false;

    // If device is valid, write the frame to the canbus.
    if (m_canbus != nullptr)
    {
        success = m_canbus->writeFrame(frame);
    }

    // If there was an error writing the frame this time, and there was no
    // error before, log error message.
    if (!success && m_hadWriteSuccess)
    {
        qDebug() << "CAN write frame failed :" << m_canbus->errorString() << frame.toString();
    }
    m_hadWriteSuccess = success;

    return success;
}

void CanBus::setVehicleIds(QVector<int> vehicleIds)
{
    m_vehicleIds.clear();
    m_vehicleIds = vehicleIds;
}

void CanBus::onFramesReceived()
{
    // Reset the counter.
    m_timeoutCounter = 0;

    // Read the CAN frames.
    quint64 numFrames = m_canbus->framesAvailable();
    while (numFrames-- > 0)
    {
        QCanBusFrame frame = m_canbus->readFrame();

        // Notify others about the new frame.
        emit frameArrived(frame);

        if (m_vehicleIds.contains(frame.frameId()))
        {
            emit vehicleFrameArrived(frame);
        }
    }
}

void CanBus::checkCanActivity()
{
    m_timeoutCounter++;

    if (!m_isActive && m_timeoutCounter < m_activityTimeout)
    {
        m_isActive = true;
        emit isActiveChanged(m_isActive);
    }
    else if (m_isActive && m_timeoutCounter >= m_activityTimeout)
    {
        m_isActive = false;
        emit isActiveChanged(m_isActive);
    }
}
