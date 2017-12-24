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

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: page.height

        PullDownMenu {
            MenuItem {
                text: qsTr("Setup")
                onClicked: pageStack.push(Qt.resolvedUrl("SettingsPage.qml"))
            }
        }
    }
}
