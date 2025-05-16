#pragma once

#include <QObject>
#include <QCanBus>
#include <QTimer>

// This class establishes a connection to a CAN bus & is used to send/receive
// CAN frames.
// To watch for CAN frames, connect to the frameArrived signal.
// To send CAN frames, connect a signal to the writeFrame() slot.
class CanBus : public QObject
{
    Q_OBJECT

public:
    explicit CanBus(QString busInterface, QObject *parent = nullptr);
    ~CanBus();

    // Connect to the given bus, return true if the connection is successful.
    bool connectBus();

    // Write a CAN frame.
    bool writeFrame(quint32 id, char payload[], int payloadLengthBytes, bool extFrame=true, QCanBusFrame::FrameType type=QCanBusFrame::FrameType::DataFrame);
    bool writeFrame(QCanBusFrame frame);

    // Update the list of CAN ids that are used for notifying the vehicle.
    void setVehicleIds(QVector<int> vehicleIds);

signals:
    // Sent out when a CAN frame has arrived on the canbus.
    void frameArrived(const QCanBusFrame& frame);

    // Send out when a CAN frame has arrived on the canbus, that should be sent
    // to the vehicle
    void vehicleFrameArrived(const QCanBusFrame& frame);

    // Sent out when the CAN bus activity stops or starts.
    void isActiveChanged(bool);

private:
    // Dequeues the latest CAN frames from the canbus device and sends them out through signals.
    void onFramesReceived();

    // Check for activity on the CAN bus.
    void checkCanActivity();

    // CAN Bus interface
    QString m_busInterface;

    // Pointer to the CAN bus device to notify when frames arrive.
    QCanBusDevice* m_canbus;

    // 1 second timer that checks if the CAN has had activity in the timeout
    // period.
    QTimer m_activityTimer;

    // Timeout period (in seconds) in which the CAN bus is considered dead.
    int m_activityTimeout;

    // Indicates if the last write to the bus was successful.
    int m_hadWriteSuccess;

    // The CAN ids to send to vehicle.
    QVector<int> m_vehicleIds;

    // Counts up every second that there is no CAN activity.
    int m_timeoutCounter;

    // Track if the CAN bus is active.
    bool m_isActive;
};



