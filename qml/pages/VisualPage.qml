/*
 * Copyright © 2017 Andrew Penkrat
 *
 * Distributed under the terms of MIT License.
 *
 * You should have received a copy of the MIT License along with the application.
 * If not, see <http://opensource.org/licenses/MIT>.
 */

import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    onStatusChanged: {
        if(status == PageStatus.Active)
            pageStack.pushAttached(Qt.resolvedUrl("PlotPage.qml"))
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: page.height

        PullDownMenu {
            MenuItem {
                text: qsTr("Setup")
                onClicked: {
                    dataSource.pause()
                    pageStack.push(Qt.resolvedUrl("SettingsPage.qml"))
                }
            }
        }

        Row {
            id: toolBar
            y: Theme.paddingLarge
            width: parent.width
            spacing: Theme.paddingLarge

            IconButton {
                icon.source: "image://theme/icon-m-refresh?" + (down
                                 ? Theme.highlightColor
                                 : Theme.primaryColor)
                onClicked: dataSource.reset()
            }
            IconButton {
                icon.source: "image://theme/icon-m-" +
                             (dataSource.isRunning ? "pause" : "play") + "?" + (down
                                 ? Theme.highlightColor
                                 : Theme.primaryColor)
                onClicked: {
                    if(dataSource.isRunning)
                        dataSource.pause()
                    else
                        dataSource.start()
                }
            }
        }

        Rectangle {
            color: "transparent"
            border.color: Theme.primaryColor
            anchors {
                left: parent.left
                leftMargin: Theme.horizontalPageMargin
                right: parent.right
                rightMargin: Theme.horizontalPageMargin
                top: toolBar.bottom
                topMargin: Theme.paddingSmall
                bottom: parent.bottom
                bottomMargin: Theme.paddingLarge
            }

            Item {
                id: visualisation
                property point rotationCenter: Qt.point(width / 2, height * 2/3)

                width: parent.width
                height: parent.height

                transform: Rotation {
                    origin.x: visualisation.rotationCenter.x
                    origin.y: visualisation.rotationCenter.y
                    angle: -dataSource.rotation * 180.0 / Math.PI
                }

                Rectangle {
                    id: base

                    color: Theme.primaryColor
                    x: visualisation.rotationCenter.x - height / 2
                    y: visualisation.rotationCenter.y - height / 2
                    width: 500
                    height: 10
                }
                Rectangle {
                    id: bar

                    color: Theme.primaryColor
                    x: base.x + base.width
                    y: base.y + base.height / 2 - (dataSource.shift * height)
                    width: 10
                    height: 500
                }

                Rectangle {
                    id: weight1
                    radius: width / 2
                    width: 30
                    height: 30
                    x: bar.x - (width - bar.width) / 2
                    y: bar.y - height
                }

                Rectangle {
                    id: weight2
                    radius: width / 2
                    width: 30
                    height: 30
                    x: bar.x - (width - bar.width) / 2
                    y: bar.y + bar.height
                }
            }
        }
    }
}

