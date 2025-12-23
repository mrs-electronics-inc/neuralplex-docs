import QtQuick
import QtQuick.Layouts

Window {
    id: window
    width: 1920
    height: 720
    visible: true
    title: Qt.application.name
    flags: isDesktop ? Qt.Window : Qt.FramelessWindowHint
    color: colors.get("Background")
    property alias nav: nav

    Image {
        id: background
        source: "qrc:/AppImages/background.png"
        anchors.centerIn: parent
    }

    Image {
        id: navbar
        source: "qrc:/AppImages/navbar.png"
        anchors.bottom: background.bottom
        anchors.left: background.left
    }

    ListView {
        id: rootList
        anchors.fill: parent
        model: list
        orientation: ListView.Horizontal
        flickableDirection: Flickable.HorizontalFlick
        snapMode: ListView.SnapOneItem
        highlightRangeMode: ListView.StrictlyEnforceRange
        focus: true
        onCurrentIndexChanged: nav.index = currentIndex
        highlightMoveDuration: 500
        highlightMoveVelocity: -1
    }

    NavMenu {
        id: nav
        height: 100
        anchors.bottom: parent.bottom
        width: parent.width
        index: 0
        onNavigationChanged: (itemState) => {
            switch (itemState) {
            case "g+":
                rootList.currentIndex = 0
                break;
            case "gsi":
                rootList.currentIndex = 1
                break;
            case "vibs":
                rootList.currentIndex = 2
                break;
            case "acc":
                rootList.currentIndex = 3
                break;
            case "test":
                rootList.currentIndex = 4
                break;
            }
        }
    }

    ObjectModel {
        id: list
        Sensors {}
        GSI {}
        Vibs {}
        ACC {}
        Test {}
    }

    FuelGauge {
        id: fuelGauge
        anchors {
            top: parent.top
            topMargin: 20
            left: parent.left
            leftMargin: 20
        }

        gaugeHeight: 30
        gaugeWidth: 260
        fuelMin: 0
        fuelMax: 100
        fuelLevel: vehicle.fuelLevel
        gaugeName: MaterialIcons.mdiGasStation
        fillColor: colors.get("InsideRange")
    }

    SpeedGauge {
        id: speedGauge
        anchors {
            top: parent.top
            topMargin: 20
            right: parent.right
            rightMargin: 20
        }

        speed: vehicle.speedometer.toFixed(1)
        unit: "ft/min"
        pointSize: 32
        gaugeHeight: 30
        gaugeWidth: 260
    }

    Image {
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 20
        }

        source: "qrc:/AppImages/mrs-logo.png"
        height: 50
        fillMode: Image.PreserveAspectFit
    }
}
