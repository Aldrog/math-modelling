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


Dialog {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    onAccepted: {
        dataSource.startingPhi = phiSetter.value * Math.PI
        dataSource.startingX = xSetter.value
        dataSource.startingDotPhi = dotPhiSetter.value * Math.PI
        dataSource.startingDotX = dotXSetter.value
        dataSource.reset()
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: header.height + settingsContainer.height + Theme.paddingLarge // for bottom margin

        DialogHeader {
            id: header
            title: qsTr("Model settings")
            dialog: page
        }

        Column {
            id: settingsContainer

            anchors {
                top: header.bottom
                left: parent.left
                right: parent.right
            }

            Label {
                text: "&phi;"
                textFormat: Text.RichText
                x: Theme.horizontalPageMargin
            }

            Slider {
                id: phiSetter
                width: parent.width
                minimumValue: -1
                maximumValue: 1
                stepSize: 0.01
                value: dataSource.startingPhi / Math.PI
                valueText: value + "π"
            }

            Label {
                text: "&lambda;"
                textFormat: Text.RichText
                x: Theme.horizontalPageMargin
            }

            Slider {
                id: xSetter
                width: parent.width
                minimumValue: 0
                maximumValue: 1
                stepSize: 0.01
                value: dataSource.startingX
                valueText: value
            }

            Label {
                text: "&phi;&#x307;"
                textFormat: Text.RichText
                x: Theme.horizontalPageMargin
            }

            Slider {
                id: dotPhiSetter
                width: parent.width
                minimumValue: -1
                maximumValue: 1
                stepSize: 0.01
                value: dataSource.startingDotPhi / Math.PI
                valueText: value + "π"
            }

            Label {
                text: "&lambda;&#x307;"
                textFormat: Text.RichText
                x: Theme.horizontalPageMargin
            }

            Slider {
                id: dotXSetter
                width: parent.width
                minimumValue: -1
                maximumValue: 1
                stepSize: 0.01
                value: dataSource.startingDotX
                valueText: value
            }
        }
        VerticalScrollDecorator {}
    }
}
